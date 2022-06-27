#include "ECS.h"

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
