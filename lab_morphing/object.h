#pragma once
#include <QOpenGLFunctions>
#include <QColor>
#include <QOpenGLShaderProgram>


class BasicObject: protected QOpenGLFunctions
{
public:
    BasicObject() = default;
    virtual void initialize() = 0;
    virtual void render(QOpenGLShaderProgram& program) = 0;
    virtual void setColor(const QColor& color) = 0;
    virtual ~BasicObject() = default;
};

