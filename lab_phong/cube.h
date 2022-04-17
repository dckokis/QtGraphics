#pragma once
#include "object.h"
#include <QOpenGLBuffer>


struct Vertex {
	QVector3D position;
	QVector3D normal;

	Vertex(const QVector3D& vertex, const QVector3D& normal) : position(vertex), normal(normal) {}
};

class Cube : public BasicObject {
public:
	explicit Cube(GLfloat edgeLen, GLint gridStep);

	auto initialize() -> void override;

	auto render(QOpenGLShaderProgram& program) -> void override;

	auto setColor(const QColor& color) -> void override;

	[[nodiscard]] auto getColor() const -> QColor;

	virtual ~Cube() override;

private:
	const GLfloat m_edgeLen;
	GLint m_gridStep;
	std::vector<Vertex> m_vertices;
	std::vector<GLint> m_indices;
	QColor m_color{255, 255, 255};
	QOpenGLBuffer m_vertexBuf, m_indexBuf;

	auto setFace(const QMatrix4x4& matrix) -> void;

};
