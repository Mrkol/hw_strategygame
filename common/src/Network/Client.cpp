#include "Network\Client.hpp"

namespace Common
{
	namespace Network
	{
		bool Synchronize(/*Stuff*/)
		{
			std::cout << "Synchronization complete!" << std::endl;
			return true;
		}

		EServerStatus CGameClient::GetStatus()
		{
			return clientServerStatus_;
		}

		/*void CGameClient::Stop()
		{
			if (clientServerStatus_ == EServerStatus::alive)
			{
				std::cout << "I stopped!" << std::endl;
				clientServer_.stop();
				clientServerStatus_ = EServerStatus::stopped;
			}
		}*/

		void CGameClient::Start()
		{
			if (clientServerStatus_ != EServerStatus::alive)
			{
				clientServer_.run();
				//clientServer_.async_run(amountOfThreads_);
				clientServerStatus_ = EServerStatus::alive;
			}

		}

		CGameClient::CGameClient(uint16_t Port)
			: clientServer_(Port), amountOfThreads_(2), 
			clientServerStatus_(EServerStatus::initializing)
		{
			clientServer_.bind("Synchronize", &Synchronize);
			//clientServer_.bind("Stop", &Stop);
		}
	}
}
