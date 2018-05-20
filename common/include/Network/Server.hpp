#pragma once

#ifndef COMMON_NETWORK_SERVER_HPP_
#define COMMON_NETWORK_SERVER_HPP_

#include <vector>
#include <string>
#include "rpc/client.h"
#include <memory>
#include "MatchManager.hpp"
#include <map>
#include "CommonHelper.hpp"

namespace Common{ namespace Network
{
	enum class EClientAnswer
	{
		successful, unsuccessful, aborted
	};

	class CServerSynchroEventArgs : public Events::EventArgs
	{
	public:

	private:
		Common::MatchManager manager;
	};

	
	class CGameServer
	{
		Event synchro_;// - Placement is important becouse of
					   // order of initialization
	public:
		CGameServer(const std::vector<std::string>& IpList, uint16_t Port,
			std::weak_ptr<EntityInstanceStorageType> list);
		bool SynchronizeClients(Serialization::IEntityInstanceSerializer& serializer);
		void StopClient(unsigned int Number);
		EventAccessProxy ServerSynchEvent;
	private:
		std::vector<std::unique_ptr<rpc::client> > clients_;
		uint64_t short_timeout;
		uint64_t timeout;
		std::weak_ptr<EntityInstanceStorageType> entityinstanceList_;
	};
}
}


#endif // COMMON_NETWORK_SERVER_HPP_
