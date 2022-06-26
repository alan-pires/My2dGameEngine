#include "ECS.h"

int Entity::GetId() const
{
	return id;
}

void System::AddEntityToSystem(Entity entity)
{

}

void System::RemoveEntityToSystem(Entity entity)
{

}

std::vector<Entity> System::GetSystemEntities() const
{
	return entities;
}

const Signature& System::GetComponetSignature() const
{
	return componentSignature;
}
