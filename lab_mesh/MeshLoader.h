#pragma once

#include <string>
#include "Vertex.h"

enum class MlResult {
	ML_OK = 1,
	ML_FAIL = 0
};

class MeshLoader final {
public:
	static auto load(const std::string& path, vertices& vertices, indices& indices) -> MlResult;
};
