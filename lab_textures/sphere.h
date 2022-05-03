#pragma once
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

struct Vertex {
	QVector3D pos, normal;
	QVector2D texCoord;
};

class Sphere : protected QOpenGLFunctions {
public:
	explicit Sphere(GLfloat radius, GLuint lats, GLuint longs);

	auto initialize() -> void;

	auto render(QOpenGLShaderProgram& program) -> void;

	~Sphere();

private:
	auto initVertices() -> void;

	auto initIndices() -> void;

	GLfloat m_radius;
	GLuint m_lats, m_longs;
	QOpenGLBuffer m_vertexBuf, m_indexBuf;
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
};
