#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem : public System
{
	public:
		MovementSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<RigidBodyComponent>();
		}
		~MovementSystem() = default;

		void Update(double deltaT)
		{
			for (auto entity : GetSystemEntities())
			{
				auto& transform = entity.GetComponent<TransformComponent>();
				const auto rigidbody = entity.GetComponent<RigidBodyComponent>();
				transform.position.x += rigidbody.velocity.x * deltaT;
				transform.position.y += rigidbody.velocity.y * deltaT;
			}
		}
};

#endif