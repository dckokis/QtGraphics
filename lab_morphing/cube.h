#pragma once
#include "square_surface.h"


class Cube final : public BasicObject {
public:
    explicit Cube(GLfloat edgeLen, unsigned gridStep);

    void initialize() override;

    void render(QOpenGLShaderProgram& program) override;

    void setColor(const QColor& color) override;

private:
    std::vector<SquareSurface> m_faces;
};

