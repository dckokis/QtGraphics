#pragma once
#include "object.h"
#include <QOpenGLBuffer>


struct Vertex{
    QVector3D position;
    QVector3D normal;
    Vertex(const QVector3D& vertex, const QVector3D& normal) : position(vertex), normal(normal) {}
};

class Cube : public BasicObject {
public:
    explicit Cube(GLfloat edgeLen, GLint gridStep);

    void initialize() override;

    void render(QOpenGLShaderProgram& program) override;

    void setColor(const QColor& color) override;

    [[nodiscard]] QColor getColor() const;

	~Cube() override;
private:
    const GLfloat m_edgeLen;
    GLint m_gridStep;
    std::vector<Vertex> m_vertices;
    std::vector<GLint> m_indices;
    QColor m_color {255, 255, 255};
    QOpenGLBuffer m_vertexBuf, m_indexBuf;

	void setFace(const QMatrix4x4& matrix);
    
};

