#include "MeshLoader.h"

#include <C:/QtGraphics/lab_mesh/LibAssimp/assimp/Importer.hpp>
#include <C:/QtGraphics/lab_mesh/LibAssimp/assimp/postprocess.h>
#include <C:/QtGraphics/lab_mesh/LibAssimp/assimp/scene.h>

auto MeshLoader::load(const std::string& path, Vertices& vertices, Indices& indices) -> MlResult {
	Assimp::Importer import;
	const auto* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) { return MlResult::ML_FAIL; }

	const auto* mesh = scene->mMeshes[0];

	vertices.clear();
	indices.clear();

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex{};
		vertex.m_position = {
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		};

		vertex.m_normal = {
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		};

		if (mesh->mTextureCoords[0]) {
			vertex.m_textureCoordinate = {
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			};
		}
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const auto& face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) { indices.push_back(face.mIndices[j]); }
	}
	return MlResult::ML_OK;
}