#include "Network/Server.hpp"
#include <future>
#include <iostream>
#include "CommonHelper.hpp"
#include <sstream>

namespace Common{ namespace Network
{
	void Server::StopClient(unsigned int Number)
	{
		if (Number < clients_.size())
		{
			clients_[Number]->call("Stop");
		}
			
	}

	Server::Server(
		const std::vector<std::string>& IpList, uint16_t Port,
		std::weak_ptr<EntityInstanceStorageType> list)
		: 
		clients_(IpList.size()), short_timeout(50), timeout(5000),
		entityinstanceList_(list)
	{
		for (int i = 0; i < clients_.size(); ++i)
		{
			clients_[i] = std::unique_ptr<rpc::client>(new rpc::client(IpList[i], Port));
		}
		//ServerSynchEvent.Subscribe(SynchronizeClients)
	}

	bool Server::SynchronizeClients(
		Serialization::IEntityInstanceSerializer& serializer)
	{
		std::cout << "srv: Synchronizing...\n";

		// Collect information to Synchronize
		NetworkMessageType client_message;
		for (auto inst : *(entityinstanceList_.lock()))
		{
			std::cout << "1\n";
			if (inst.second != nullptr && inst.second->toSynch && inst.second->IsEmitting())
			{
				std::cout << "2\n";
				std::stringstream stream;
				serializer.Serialize(inst.second, stream);
				std::string tmp;
				client_message.push_back({ inst.first, std::string(stream.str()) });
				inst.second->toSynch = false;
			}
		}
		if (client_message.empty())
		{
			std::cout << "Nothing to synch\n";
			return true;
		}

		for (int i = 0; i < clients_.size(); ++i)
		{
			std::cout << "srv: client num " << i << std::endl;
			clients_[i]->call("Synchronize", client_message);
				
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
} }
