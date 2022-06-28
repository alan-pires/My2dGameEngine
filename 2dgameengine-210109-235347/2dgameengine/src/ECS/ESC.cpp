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
	entities.erase(std::remove_if(entities.begin(), entities.end(),
	 [&entity](Entity other){
		 return entity.GetId() == other.GetId();
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
	entitiesToBeAdded.insert(entity);
	Logger::Log("Entity created whit id " + std::to_string(entityId));
	return entity;
}

void Registry::Update()
{

}