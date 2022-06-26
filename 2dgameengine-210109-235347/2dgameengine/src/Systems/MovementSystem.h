#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

class MovementSystem
{

public:
	MovementSystem()
	{
		// RequireComponent<TransformComponent>()
		// RequireComponent<Component>()
	}
	~MovementSystem();

	void Update()
	{
		// for (auto entity : GetEntities())
		// {
		// Update entity position based on its velocity every frame of the game loop
		// }
	}
};

#endif