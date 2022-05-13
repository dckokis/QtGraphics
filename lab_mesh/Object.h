#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QColor>
#include <QOpenGLShaderProgram>
#include "MeshLoader.h"

class Object : protected QOpenGLFunctions {
public:
	explicit Object(std::string name);

	auto initialize() -> void;

	auto render(QOpenGLShaderProgram& program) -> void;

	virtual ~Object();

	[[nodiscard]] auto getName() const -> std::string;

	auto setName(const std::string& name) -> void;

	[[nodiscard]] auto getColor() const -> QColor;

	auto setColor(const QColor& color) -> void;
public:
	std::string m_name;
	vertices m_vertices;
	indices m_indices;
	QColor m_color{255, 255, 255};
	QOpenGLBuffer m_vertexBuf, m_indexBuf;
};
