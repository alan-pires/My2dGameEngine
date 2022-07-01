#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL2/SDL.h>
#include "../AssetManager/AssetManager.h"

class RenderSystem : public System
{
	public:
		RenderSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<SpriteComponent>();
		}

		void Update(SDL_Renderer *renderer, std::unique_ptr<AssetManager>& assetManager)
		{
			for (auto entity: GetSystemEntities())
			{
				const auto transform = entity.GetComponent<TransformComponent>();
				const auto sprite = entity.GetComponent<SpriteComponent>();
		
				//Set the source rectangle of our original sprite textures
				SDL_Rect srcRect = sprite.srcRect;
				// Set the destination rectangle with the x, y position to be rendered
				SDL_Rect dstRect = {
					static_cast<int>(transform.position.x),
					static_cast<int>(transform.position.y),
					static_cast<int>(sprite.width * transform.scale.x),
					static_cast<int>(sprite.height * transform.scale.y)
				};

				SDL_RenderCopyEx(
					renderer,
					assetManager->GetTexture(sprite.assetId),
					&srcRect,
					&dstRect,
					transform.rotation,
					NULL,
					SDL_FLIP_NONE
				);
			}
		}
};

#endif