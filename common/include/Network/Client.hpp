#pragma once
#pragma once

#ifndef COMMON_NETWORK_CLIENT_HPP_
#define COMMON_NETWORK_CLIENT_HPP_

#include "rpc/server.h"
#include "../MatchManager.hpp"

namespace Common { namespace Network
{
	enum class ServerStatus
	{
		Initializing, Alive, Stopped
	};

	class Client
	{
		friend bool Synchronize(NetworkMessageType server_message, Client* server);
	public:
		Client(uint16_t Port, std::weak_ptr<MatchManager> manager);
		//void Stop();
		void Start();
		bool SetAmountOfThreads(uint16_t);
		ServerStatus GetStatus();

	private:
		static bool Synchronize(NetworkMessageType server_message);
		rpc::server clientServer_;
		uint16_t amountOfThreads_;
		ServerStatus clientServerStatus_;
		static std::weak_ptr<MatchManager> manager_;
	};
} }

#endif // COMMON_NETWORK_CLIENT_HPP_
