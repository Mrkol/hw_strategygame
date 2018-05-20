#pragma once
#pragma once

#ifndef COMMON_NETWORK_CLIENT_HPP_
#define COMMON_NETWORK_CLIENT_HPP_

#include "rpc/server.h"
#include "../MatchManager.hpp"

namespace Common { namespace Network
{
	enum class EServerStatus
	{
		initializing, alive, stopped
	};

	class CGameClient
	{
		friend bool Synchronize(NetworkMessageType server_message, CGameClient* server);
	public:
		CGameClient(uint16_t Port, std::weak_ptr<MatchManager> manager);
		//void Stop();
		void Start();
		bool SetAmountOfThreads(uint16_t);
		EServerStatus GetStatus();

	private:
		static bool Synchronize(NetworkMessageType server_message);
		rpc::server clientServer_;
		uint16_t amountOfThreads_;
		EServerStatus clientServerStatus_;
		static std::weak_ptr<MatchManager> manager_;
	};
}
}

#endif // COMMON_NETWORK_CLIENT_HPP_
