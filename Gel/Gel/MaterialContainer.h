#pragma once
#include "Material.h"

namespace Gel {
	static class GEL_API MaterialContainer
	{
	public:
		static void AddMaterial(Gel::Material* material);
		static Gel::Material* GetMaterial(int index);
		static Gel::Material* GetMaterial(std::string name);
	private:
		static std::vector<Gel::Material*> materials;
	};
}