#include "cube.h"

Cube::Cube(GLfloat edgeLen, unsigned gridStep) {
	for (auto i = 0; i < 6; ++ i) { m_faces.emplace_back(edgeLen, gridStep); }
}


auto Cube::initialize() -> void {
	initializeOpenGLFunctions();
	for (auto& face : m_faces) { face.initialize(); }
	QMatrix4x4 matrix;
	matrix.rotate(90.f, 0.f, 1.f);
	m_faces[1].transform(matrix);
	matrix.rotate(90.f, 0.f, 1.f);
	m_faces[2].transform(matrix);
	matrix.rotate(90.f, 0.f, 1.f);
	m_faces[3].transform(matrix);
	matrix.rotate(90.f, 0.f, 1.f);
	matrix.rotate(90.f, 1.f, 0.f);
	m_faces[4].transform(matrix);
	matrix.rotate(180.f, 1.f, 0.f);
	m_faces[5].transform(matrix);
}

auto Cube::render(QOpenGLShaderProgram& program) -> void { for (auto& face : m_faces) { face.render(program); } }

auto Cube::setColor(const QColor& color) -> void { for (auto& face : m_faces) { face.setColor(color); } }
