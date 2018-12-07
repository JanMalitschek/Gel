#pragma once

#include "Core.h"

#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "EngineHandler.h"
#include <fstream>
#include <vector>
#include <string>

#include "TextureContainer.h"
#include "ModelContainer.h"
#include "ShaderContainer.h"

namespace Gel {

	enum ResourceLoadingMode {
		Load_Textures,
		Load_Models,
		Load_Shaders,
		Load_Audio,
		Load_Sprite_Sheets
	};

	static class GEL_API ResourceManager {
	public:
		static void UnpackResources(const char* resourceFilePath);
	private:
		static std::vector<std::string> resourceData;
		static ResourceLoadingMode loadingMode;
		static unsigned long wrapMode;
		static unsigned long filterMode;

		/*static SpriteSheet* tempSheet;
		static int numTextures;
		static int numAnimations;
		static std::string::size_type sz;*/
	};

	//SpriteSheet* ResourceManager::tempSheet = new SpriteSheet();
	//int ResourceManager::numTextures = 0;
	//int ResourceManager::numAnimations = 0;
	//std::string::size_type ResourceManager::sz;
}