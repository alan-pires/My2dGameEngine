#include "ECS.h"
#include "../Logger/Logger.h"

int IComponent::nextId = 0;

int Entity::GetId() const
{
	return id;
}

void System::AddEntityToSystem(Entity entity)
{
	// System::GetSystemEntities().push_back(entity);
	entities.push_back(entity);
}

void System::RemoveEntityToSystem(Entity entity)
{
	entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other){
		 return entity == other;
	 }), entities.end());
}

std::vector<Entity> System::GetSystemEntities() const
{
	return entities;
}

const Signature& System::GetComponetSignature() const
{
	return componentSignature;
}

Entity Registry::CreateEntity()
{
	int entityId = numEntities++;
	Entity entity(entityId);
	entity.registry = this;
	entitiesToBeAdded.insert(entity);
	if (entityId >= entityComponentSignatures.size())
		entityComponentSignatures.resize(entityId + 1);
	// Logger::Log("Entity created whit id " + std::to_string(entityId));
	return entity;
}

void Registry::AddEntityToSystems(Entity entity)
{
	const auto entityId = entity.GetId();
	const auto& entityComponentSignature = entityComponentSignatures[entityId];
	for (auto& system: systems)
	{
		const auto& systemComponentSignature = system.second->GetComponetSignature();
		bool isInterested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;

		if (isInterested)
			system.second->AddEntityToSystem(entity);
	}
}

void Registry::Update()
{
	// Add the entities that are waiting to be created to the active systems
	for (auto entity: entitiesToBeAdded)
	{
		AddEntityToSystems(entity);
	}
	entitiesToBeAdded.clear();
}