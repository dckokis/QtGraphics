#pragma once
#include <vector>
#include <QVector2D>
#include <QOpenGLFunctions>

struct Vertex {
	QVector3D m_position;
	QVector3D m_normal;
	QVector2D m_textureCoordinate;
};

using vertices = std::vector<Vertex>;
using indices = std::vector<GLint>;
