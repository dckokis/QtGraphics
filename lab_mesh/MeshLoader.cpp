#include "MeshLoader.h"
#include <QFile>

#include <iostream>

auto MeshLoader::load(const std::string& path, vertices& vertices, indices& indices) -> MlResult {
	QFile in(path.data());

	if (!in.open(QFile::ReadOnly | QFile::Text)) { std::cerr << "FAIL TO OPEN FILE"; }

	char buf[256];
	std::vector<std::string> lines;
	while (!in.atEnd()) {
		in.readLine(buf, 256);
		lines.emplace_back(buf);
	}
	std::vector<QVector3D> positions;
	std::vector<QVector3D> normals;
	std::vector<QVector2D> textures;
	const auto lines_amount = lines.size();
	for (size_t i = 0; i < lines_amount; ++i) {
		if (lines[i][0] != '#') {
			if (lines[i][0] == 'v' && lines[i][1] == ' ') {
				float tmpx, tmpy, tmpz;
				sscanf(lines[i].c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
				QVector3D position = {
					tmpx,
					tmpy,
					tmpz
				};
				positions.push_back(position);
			}
			else if (lines[i][0] == 'v' && lines[i][1] == 'n') {
				float tmpx, tmpy, tmpz;
				sscanf(lines[i].c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
				QVector3D normal = {tmpx, tmpy, tmpz};
				normals.push_back(normal);
			}
			else if (lines[i][0] == 'v' && lines[i][1] == 't') {
				float tmpx, tmpy;
				sscanf(lines[i].c_str(), "vt %f %f", &tmpx, &tmpy);
				QVector2D tex = {tmpx, tmpy};
				textures.push_back(tex);
			}
			else if (lines[i][0] == 'f') {
				int v1, v1n, v1t, v2, v2n, v2t, v3, v3n, v3t;
				sscanf(lines[i].c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i", &v1, &v1t, &v1n, &v2, &v2t,
				       &v2n, &v3, &v3t, &v3n);
				indices.push_back(v1 - 1);
				indices.push_back(v2 - 1);
				indices.push_back(v3 - 1);
			}
		}
	}
	auto i = 0;
	for (const auto& position : positions) {
		Vertex vertex{};
		vertex.m_position = position;
		vertex.m_normal = normals[i];
		vertex.m_textureCoordinate = textures[i];
		vertices.push_back(vertex);
		i++;
	}
	/*Assimp::Importer import;
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
		for (unsigned int j = 0; j < face.mNumIndices; j++) { indices.push_back(face.mIndices[j] - 1); }
	}*/
	return MlResult::ML_OK;
}
