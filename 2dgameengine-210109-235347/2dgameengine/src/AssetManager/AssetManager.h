#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Logger/Logger.h"

class AssetManager
{
	private:
		std::map<std::string, SDL_Texture*> textures;
		// fonts
		// audios
	public:
		AssetManager();
		~AssetManager();

		void ClearAssets();
		void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);
		SDL_Texture* GetTexture(const std::string& assetId);
};

#endif