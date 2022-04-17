#pragma once

#include "object.h"
#include <QOpenGLBuffer>


class SquareSurface final : public BasicObject {
public:
	explicit SquareSurface(const GLfloat edgeLen, const size_t gridStep): m_edgeLen(edgeLen), m_borderThick(1.0f),
	                                                                      m_gridStep(gridStep),
	                                                                      m_vertexBuf(QOpenGLBuffer::VertexBuffer),
	                                                                      m_indexBuf(QOpenGLBuffer::IndexBuffer) { }

	auto initialize() -> void override;

	auto render(QOpenGLShaderProgram& program) -> void override;

	auto setColor(const QColor& color) -> void override;

	auto transform(const QMatrix4x4& matrix) -> void;

	virtual ~SquareSurface() override {
		m_vertexBuf.destroy();
		m_indexBuf.destroy();
	}

private:
	const GLfloat m_edgeLen, m_borderThick;
	size_t m_gridStep = 0;
	std::vector<QVector3D> m_vertices;
	std::vector<GLint> m_indices;

	QOpenGLBuffer m_vertexBuf, m_indexBuf;

	QColor m_color;

	auto setVertices() -> void;

	auto setIndices() -> void;
};
