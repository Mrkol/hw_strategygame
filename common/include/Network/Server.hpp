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

namespace Common { namespace Network
{	
	class Server
	{
	public:
		Server(const std::vector<std::string>& IpList, uint16_t Port,
			std::weak_ptr<EntityInstanceStorageType> list);

		bool SynchronizeClients(Serialization::IEntityInstanceSerializer& serializer);

		void StopClient(unsigned int Number);

	private:
		std::vector<std::unique_ptr<rpc::client>> clients_;
		
		uint64_t short_timeout;
		uint64_t timeout;
		
		std::weak_ptr<EntityInstanceStorageType> entityinstanceList_;
	};

	class EventSynchServerArgs : public EventArgs
	{
		
	public:
		std::weak_ptr<Common::Network::Server> server;
		const std::vector<std::string>& IpList;
		uint16_t Port;
		std::weak_ptr<EntityInstanceStorageType> list;
	};

	void EventFriendlySynchronizeClients(const Common::EventArgs& args);
} }


#endif // COMMON_NETWORK_SERVER_HPP_
