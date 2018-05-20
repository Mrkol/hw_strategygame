#include "MatchManager.hpp"
#include "Events/event.hpp"
#include "Events/EventAccessProxy.hpp"
#include <iostream>
#include <chrono>
#include "entity.pb.h"
#include "Serialization\ProtobufEntityInstanceSerializer.hpp"
#include <sstream>

namespace Common
{
	MatchManager::MatchManager()
		: gameTick_(),
		GameTickEvent(gameTick_),
		currentMatchState_(MatchState::Initialization),
		tickRate_(TimeIntervalType(5)),
		clientType_(ClientType::Server), 
		nextInstanceId(0)
	{
		
	}

	MatchManager::MatchManager(ClientType type, const std::vector<std::string>& adresses)
		: gameTick_(),
		GameTickEvent(gameTick_),
		currentMatchState_(MatchState::Initialization),
		tickRate_(TimeIntervalType(5)),
		clientType_(type)
	{
		if (clientType_ == ClientType::Client)
		{
			//subscribe client functions to tick
		}
		else
		{
			//subscribe server functions to tick
		}
	}

	ClientType MatchManager::GetClientType()
	{
		return clientType_;
	}

	void MatchManager::Start()
	{
		if (currentMatchState_ == MatchState::Ended)
		{
			return;
		}
		currentMatchState_ = MatchState::InProgress;
	}

	void MatchManager::Pause()
	{
		if (currentMatchState_ == MatchState::Ended)
		{
			return;
		}
		currentMatchState_ = MatchState::Paused;
	}

	void MatchManager::Stop()
	{
		currentMatchState_ = MatchState::Ended;
	}

	bool MatchManager::GenerateTick()
	{
		if (currentMatchState_ != MatchState::InProgress)
		{
			return false;
		}
		
		if (lastTick_ + tickRate_ < std::chrono::system_clock::now())
		{
			lastTick_ = std::chrono::system_clock::now();
			EventArgs args;
			gameTick_.Trigger(args);
			return true;
		}

		return false;
	}

	MatchState MatchManager::GetCurrentState()
	{
		return currentMatchState_;
	}

	bool MatchManager::UpdateInstance(EntityInstanceIdType id,
		const std::string& data, Serialization::IEntityInstanceSerializer& serializer)
	{
		std::stringstream stream;
		stream << data;
		if (instanceList.find(id) == instanceList.end())
		{
			//Create one
			instanceList[id] = serializer.Deserialize(entityTypeRegistry_,
				stream);
			if (instanceList[id] == nullptr)
			{
				return false;
			}
		}
		else
		{
			//Update one
			if (!serializer.EmplaceDeserialize(entityTypeRegistry_,
				stream, instanceList[id]))
			{
				return false;
			}
		}
		return true;
	}
}
