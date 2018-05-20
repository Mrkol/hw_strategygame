#include "MatchManager.hpp"
#include "Events/event.hpp"
#include "Events/EventAccessProxy.hpp"
#include <iostream>
#include <chrono>
#include "entity.pb.h"
#include "Serialization\ProtobufEntityInstanceSerializer.hpp"
#include <sstream>
#include "Components/position.hpp"

namespace Common
{
	MatchManager::MatchManager()
		: gameTick_(),
		GameTickEvent(gameTick_),
		currentMatchState_(MatchState::Initialization),
		tickRate_(TimeIntervalType(5)),

		nextInstanceId_(0),
		isRemote_(false),

		entityTypeRegistry_(new EntityTypeRegistry),
		entityTypeBuilder_(new EntityTypeBuilder(*entityTypeRegistry_)),
		instanceList_(new EntityInstanceStorageType)
	{

	}

	void MatchManager::Start(bool remote)
	{
		(*instanceList_)[0] = (*entityTypeRegistry_)["mage"]->Instantiate();
		(*instanceList_)[1] = (*entityTypeRegistry_)["warrior"]->Instantiate();

		Components::PositionComponent::Access((*entityTypeRegistry_)["mage"])
			->Set((*instanceList_)[0], {200, 0});


		if (currentMatchState_ == MatchState::Ended)
		{
			return;
		}
		isRemote_ = remote;
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

	std::shared_ptr<EntityTypeBuilder> MatchManager::GetBuilder()
	{
		return entityTypeBuilder_;
	}

	std::shared_ptr<EntityTypeRegistry> MatchManager::GetRegistry()
	{
		return entityTypeRegistry_;
	}

	std::shared_ptr<EntityInstanceStorageType> MatchManager::GetInstanceStorage()
	{
		return instanceList_;
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
		if (instanceList_->find(id) == instanceList_->end())
		{
			//Create one
			(*instanceList_)[id] = serializer.Deserialize(*entityTypeRegistry_,
				stream);
			if ((*instanceList_)[id] == nullptr)
			{
				return false;
			}
		}
		else
		{
			//Update one
			if (!serializer.EmplaceDeserialize(*entityTypeRegistry_,
				stream, (*instanceList_)[id]))
			{
				return false;
			}
		}
		return true;
	}
}
