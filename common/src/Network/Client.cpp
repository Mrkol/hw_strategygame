#include "Network\Client.hpp"
#include "Serialization\ProtobufEntityInstanceSerializer.hpp"

namespace Common { namespace Network
{
	bool Client::Synchronize(NetworkMessageType server_message)
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

	ServerStatus Client::GetStatus()
	{
		return clientServerStatus_;
	}

	void Client::Start()
	{
		if (clientServerStatus_ != ServerStatus::Alive)
		{
			clientServer_.run();
			//clientServer_.async_run(amountOfThreads_);
			clientServerStatus_ = ServerStatus::Alive;
		}

	}

	Client::Client(uint16_t Port, std::weak_ptr<MatchManager> manager)
		: clientServer_(Port), amountOfThreads_(2), 
		clientServerStatus_(ServerStatus::Initializing)
	{
		manager_ = manager;
		clientServer_.bind("Synchronize", &Synchronize);
		//clientServer_.bind("Stop", &Stop);
	}
	std::weak_ptr<MatchManager> Client::manager_(std::shared_ptr<MatchManager>(nullptr));
} }
