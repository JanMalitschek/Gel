#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Core.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <soil/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Camera.h"
#include "System.h"
#include "Transform.h"

namespace Gel {

	class GEL_API Model
	{
	public:
		/*  Functions   */
		// Constructor, expects a filepath to a 3D model.
		Model();
		Model(GLchar* path);
		Model(string name, GLchar* path);
		Model(string name, GLchar* path, vector<Material*> materials);
		void SetMaterials(vector<Material*> materials);
		void SetMaterial(int index, Material* material);
		void AddMaterial(Material* material);

		void AddMesh(Gel::Mesh mesh);
		void SetMesh(int index, Gel::Mesh mesh);

		void Draw(Transform transform);

		string name;

		vector<Mesh> meshes;

	private:
		/*  Model Data  */
		vector<Material*> materials;
		string directory;
		bool isSetup;

		/*  Functions   */
		// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		void loadModel(string path);

		// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		void processNode(aiNode* node, const aiScene* scene);

		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	};
}
