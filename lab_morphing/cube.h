#pragma once
#include "square_surface.h"


class Cube final : public BasicObject {
public:
	explicit Cube(GLfloat edgeLen, unsigned gridStep);

	auto initialize() -> void override;

	auto render(QOpenGLShaderProgram& program) -> void override;

	auto setColor(const QColor& color) -> void override;

private:
	std::vector<SquareSurface> m_faces;
};
