#include "ResourceManager.h"

namespace Gel {

	std::vector<std::string> ResourceManager::resourceData = std::vector<std::string>();
	ResourceLoadingMode ResourceManager::loadingMode = ResourceLoadingMode::Load_Textures;
	unsigned long ResourceManager::wrapMode = 0;
	unsigned long ResourceManager::filterMode = 0;

	void ResourceManager::UnpackResources(const char* resourceFilePath) {
		std::cout << "Unpacking Resources..." << std::endl;

		std::ifstream file = std::ifstream(resourceFilePath);
		std::string line;
		if (file.is_open()) {
			while (std::getline(file, line)) {
				resourceData.push_back(line);
			}
			file.close();
		}
		else
		{
			std::cout << "Resource File could not be loaded!" << std::endl;
			file.close();
			return;
		}
		for (int i = 0; i < resourceData.size(); i++) {
			if (resourceData[i] == "#Tex") {
				loadingMode = ResourceLoadingMode::Load_Textures;
				continue;
			}
			else if (resourceData[i] == "#Mod") {
				loadingMode = ResourceLoadingMode::Load_Models;
				continue;
			}
			else if (resourceData[i] == "#Sha") {
				loadingMode = ResourceLoadingMode::Load_Shaders;
				continue;
			}
			else if (resourceData[i] == "#Aud") {
				loadingMode = ResourceLoadingMode::Load_Audio;
				continue;
			}
			else if (resourceData[i] == "#SprAnim") {
				loadingMode = ResourceLoadingMode::Load_Sprite_Sheets;
				continue;
			}
			else {
				switch (loadingMode)
				{
				case Load_Textures:
					if (resourceData[i + 2] == "_Clamp")
						wrapMode = GL_CLAMP;
					else if (resourceData[i + 2] == "_Repeat")
						wrapMode = GL_REPEAT;
					else
						wrapMode = GL_REPEAT;
					if (resourceData[i + 3] == "_Nearest")
						filterMode = GL_NEAREST;
					else if (resourceData[i + 3] == "_Linear")
						filterMode = GL_LINEAR;
					else
						filterMode = GL_LINEAR;

					TextureContainer::LoadTexture(resourceData[i].c_str(), resourceData[i + 1], wrapMode, wrapMode, filterMode, filterMode);
					i += 3;
					break;
				case Load_Models:
					ModelContainer::LoadModel(resourceData[i + 1], (GLchar*)resourceData[i].c_str());
					i += 1;
					break;
				case Load_Shaders:
					ShaderContainer::LoadShader(new Shader(resourceData[i], resourceData[i + 1].c_str(), resourceData[i + 2].c_str()));
					i += 2;
					break;
				case Load_Audio:
					//AudioClipContainer::AddAudioClip(AudioClip(resourceData[i], resourceData[i + 1].c_str()));
					i += 1;
					break;
				case Load_Sprite_Sheets:
					/*numAnimations = std::stoi(resourceData[i + 2], &sz);
					numTextures = std::stoi(resourceData[i + 3], &sz);
					std::cout << "Num Frames: " << numTextures << std::endl;
					if (resourceData[i + 1] == "_Single") {
						tempSheet = new SpriteSheet(SpriteSheetType::Single, numAnimations, numTextures, resourceData[i]);
						tempSheet->SetSprite(TextureContainer::GetTexture(resourceData[i + 4]));
						i += 3 + numAnimations;
					}
					else if (resourceData[i + 1] == "_Separate") {
						tempSheet = new SpriteSheet(SpriteSheetType::Separate, numAnimations, numTextures, resourceData[i]);
						for (int n = 0; n < numAnimations; n++) {
							for (int m = 0; m < numTextures; m++) {
								std::cout << resourceData[i + 4 + m + numTextures * n] << std::endl;
								tempSheet->AddTexture(TextureContainer::GetTexture(resourceData[i + 4 + m + numTextures * n]));
							}
						}
						i += 3 + numTextures * numAnimations;
					}
					else {
						std::cout << "ResourceManager::Error: \"" << resourceData[i + 1] << "\" is not a valid SpriteSheetType!" << std::endl;
						break;
					}
					SpriteSheetContainer::AddSpriteSheet(*tempSheet);*/
					break;
				default:
					break;
				}
				continue;
			}
		}
		System::ResetDeltaTime();
	}

}
