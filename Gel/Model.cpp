#include "Model.h"

namespace Gel {

	Model::Model() {

	};
	Model::Model(GLchar* path)
	{
		this->loadModel(path);
		for (int i = 0; i < this->meshes.size(); i++) {
			this->materials.push_back(new Material());
		}
	}
	Model::Model(string name, GLchar* path)
	{
		this->name = name;
		this->loadModel(path);
		for (int i = 0; i < this->meshes.size(); i++) {
			this->materials.push_back(new Material());
		}
	}
	Model::Model(string name, GLchar* path, vector<Material*> materials)
	{
		isSetup = false;
		this->name = name;
		this->loadModel(path);
		this->materials = materials;
		if (materials.size() == meshes.size()) {
			isSetup = true;
		}
		else {
			isSetup = false;
			std::cout << "The Model \"" << name << "\" does not have the same number of materials as it has submeshes! Thus is won't be drawn." << std::endl;
		}
	}
	void Model::SetMaterials(vector<Material*> materials) {
		this->materials = materials;
		if (materials.size() == meshes.size()) {
			isSetup = true;
		}
		else {
			isSetup = false;
			std::cout << "The Model \"" << name << "\" does not have the same number of materials as it has submeshes! Thus is won't be drawn." << std::endl;
		}
	}
	void Model::SetMaterial(int index, Material* material) {
		if (index >= 0 && index < this->materials.size()) {
			if (material != nullptr) {
				this->materials[index] = material;
			}
			else {
				this->materials[index] = new Material();
			}
		}
	}
	void Model::Draw(Transform transform)
	{
		if (isSetup) {
			//Loop through all submeshes
			for (GLuint i = 0; i < this->meshes.size(); i++) {
				//use current shader for this submesh
				GLuint activeProgram = materials[i]->GetProgram();
				glUseProgram(activeProgram);
				//Get Uniform locations for the matrices
				GLint modelLoc = glGetUniformLocation(activeProgram, "model");
				GLint viewLoc = glGetUniformLocation(activeProgram, "view");
				GLint projLoc = glGetUniformLocation(activeProgram, "projection");
				//Set View Matrix
				glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(Camera::GetUpdatedView()));
				//Set Projection Matrix
				// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
				glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(Camera::GetProjection()));
				//Set Model Matrix
				glm::mat4 modelMatrix = glm::mat4();
				modelMatrix = glm::translate(modelMatrix, transform.position);
				glm::quat completeRotation = transform.globalRotation * transform.localRotation;
				glm::vec3 eulerAngles = glm::eulerAngles(completeRotation);
				modelMatrix = glm::rotate(modelMatrix, eulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
				modelMatrix = glm::rotate(modelMatrix, eulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
				modelMatrix = glm::rotate(modelMatrix, eulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
				modelMatrix = glm::scale(modelMatrix, transform.scale);
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
				//Pass Material Values
				materials[i]->PassValues();
				//Draw the submesh
				this->meshes[i].Draw();
			}
		}
	}

	void Model::loadModel(string path)
	{
		// Read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		// Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			return;
		}
		// Retrieve the directory path of the filepath
		this->directory = path.substr(0, path.find_last_of('/'));

		// Process ASSIMP's root node recursively
		this->processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		// Process each mesh located at the current node
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			// The node object only contains indices to index the actual objects in the scene. 
			// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(this->processMesh(mesh, scene));
		}
		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		// Data to fill
		vector<Vertex> vertices;
		vector<GLuint> indices;

		// Walk through each of the mesh's vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
							  // Positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			// Normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
			// Texture Coordinates
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			vertices.push_back(vertex);
		}
		// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// Retrieve all indices of the face and store them in the indices vector
			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		// Process materials
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		}

		// Return a mesh object created from the extracted mesh data
		return Mesh(vertices, indices);
	}
}