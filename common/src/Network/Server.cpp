#include "Network/Server.hpp"
#include <future>
#include <iostream>

namespace Common
{
	namespace Network
	{
		void CGameServer::StopClient(unsigned int Number)
		{
			if (Number < clients_.size())
			{
				clients_[Number]->call("Stop");
			}
			
		}

		CGameServer::CGameServer(
			const std::vector<std::string>& IpList, uint16_t Port)
			: clients_(IpList.size()), short_timeout(50), timeout(5000),
			synchro_(), ServerSynchEvent(synchro_)
		{
			for (int i = 0; i < clients_.size(); ++i)
			{
				clients_[i] = std::unique_ptr<rpc::client>(new rpc::client(IpList[i], Port));
			}
		}

		bool CGameServer::SynchronizeClients(
			Common::MatchManager* manager)
		{
			std::cout << "srv: Synchronizing...\n";
			// Collect information to Synchronize
			std::vector<std::future<clmdep_msgpack::v1::object_handle>> 
				answers(clients_.size());

			for (int i = 0; i < clients_.size(); ++i)
			{
				std::cout << "srv: client num " << i << std::endl;
				clients_[i]->call("Synchronize");
				//answers[i] = clients_[i]->async_call(
					//"Synchronize"/*, stuff to sinchronize*/);
				
			}
			for (int i = 0; i < clients_.size(); ++i)
			{
				std::cout << "srv: Waiting for client " << i << std::endl;
				clients_[i]->set_timeout(short_timeout);
				try
				{
					clients_[i]->wait_all_responses();
				}
				catch (...)
				{
					std::cout << "Too slow... gonna try to wait";
					clients_[i]->clear_timeout();
					
					clients_[i]->set_timeout(timeout);
					try
					{
						clients_[i]->wait_all_responses();
					}
					catch (...)
					{
						std::cout << "Aborting client number " << i << std::endl;
						clients_[i]->clear_timeout();
						// should do something
					}
				}

			}
			return true;

		}
		
	}
}
