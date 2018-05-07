#pragma once
#pragma once

#ifndef COMMON_NETWORK_CLIENT_HPP_
#define COMMON_NETWORK_CLIENT_HPP_

#include "rpc/server.h"
#include "../MatchManager.hpp"

namespace Common
{
	namespace Network
	{
		enum class EServerStatus
		{
			initializing, alive, stopped
		};

		class CGameClient
		{
		public:
			CGameClient(uint16_t Port);
			//bool Synchronize();
			//void Stop();
			void Start();
			bool SetAmountOfThreads(uint16_t);
			EServerStatus GetStatus();

		private:
			rpc::server clientServer_;
			uint16_t amountOfThreads_;
			EServerStatus clientServerStatus_;

		};
	}
}

#endif // COMMON_NETWORK_CLIENT_HPP_
