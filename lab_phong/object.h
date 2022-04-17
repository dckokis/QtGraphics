#pragma once
#include <QOpenGLFunctions>
#include <QColor>
#include <QOpenGLShaderProgram>


class BasicObject : protected QOpenGLFunctions {
public:
	BasicObject() = default;

	virtual auto initialize() -> void = 0;

	virtual auto render(QOpenGLShaderProgram& program) -> void = 0;

	virtual auto setColor(const QColor& color) -> void = 0;

	virtual ~BasicObject() = default;
};
