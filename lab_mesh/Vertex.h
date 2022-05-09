#pragma once
#include <vector>
#include <QVector3D>
#include <QVector2D>

struct Vertex {
	QVector3D m_position;
	QVector3D m_normal;
	QVector2D m_textureCoordinate;
};

using Vertices = std::vector<Vertex>;
using Indices = std::vector<unsigned>;
