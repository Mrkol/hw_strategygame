#include "Network\Client.hpp"
#include "Serialization\ProtobufEntityInstanceSerializer.hpp"

namespace Common { namespace Network
{
	bool CGameClient::Synchronize(NetworkMessageType server_message)
	{
		Serialization::ProtobufEntityInstanceSerializer serializer;
		for (auto inst : server_message)
		{
			std::cout << "client: got this: " << inst.second << std::endl;
			manager_.lock()->UpdateInstance(inst.first, inst.second, serializer);
		}
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

	CGameClient::CGameClient(uint16_t Port, std::weak_ptr<MatchManager> manager)
		: clientServer_(Port), amountOfThreads_(2), 
		clientServerStatus_(EServerStatus::initializing)
	{
		manager_ = manager;
		clientServer_.bind("Synchronize", &Synchronize);
		//clientServer_.bind("Stop", &Stop);
	}
	std::weak_ptr<MatchManager> CGameClient::manager_(std::shared_ptr<MatchManager>(nullptr));

}
}
