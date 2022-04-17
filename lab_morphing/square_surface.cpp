#include "square_surface.h"

void SquareSurface::initialize() {
    initializeOpenGLFunctions();
    m_vertexBuf.create();
    m_indexBuf.create();
    setVertices();
    setIndices();
    m_vertexBuf.bind();
    m_vertexBuf.allocate(m_vertices.data(), m_vertices.size() * sizeof (QVector3D));
    m_indexBuf.bind();
    m_indexBuf.allocate(m_indices.data(), m_indices.size() * sizeof (size_t));
}

void SquareSurface::render(QOpenGLShaderProgram &program) {
    m_vertexBuf.bind();
    m_indexBuf.bind();
    const auto pos_attr = program.attributeLocation("posAttr");
    program.enableAttributeArray(pos_attr);
    program.setAttributeBuffer(pos_attr, GL_FLOAT, 0, 3);
    // cube drawing
    program.setUniformValue("col", m_color);
    program.setUniformValue("lightColor", QColor{250, 10, 5});
    glPolygonMode(GL_FRONT, GL_FILL);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    // edges drawing
    const QColor lines_col  {0, 0, 0};
    program.setUniformValue("col", lines_col);
    glPolygonMode(GL_FRONT, GL_LINE);
    glLineWidth(m_borderThick);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

void SquareSurface::setVertices() {
	const auto step = m_edgeLen / m_gridStep;
    for (unsigned j = 0; j <= m_gridStep; ++j) {
        for (unsigned i = 0; i <= m_gridStep; ++i) {
            m_vertices.emplace_back(- m_edgeLen / 2 + step * i, - m_edgeLen / 2 + step * j, m_edgeLen / 2);
        }
    }
}

void SquareSurface::setIndices() {
    for (size_t i = 0; i < m_gridStep; ++i) {
           for (size_t j = 0; j < m_gridStep; ++j) {
	           const auto first = i + (j + 1) * (m_gridStep + 1);
	           const auto second = i + j * (m_gridStep + 1);
               m_indices.push_back(first); m_indices.push_back(second); m_indices.push_back(second + 1); // first triangle
               m_indices.push_back(second + 1); m_indices.push_back(first + 1); m_indices.push_back(first); // second triangle
           }
       }
}


void SquareSurface::transform(const QMatrix4x4 &matrix) {
    for (auto& v : m_vertices){
            v = matrix.map(v);
    }
    m_vertexBuf.bind();
    m_vertexBuf.allocate(m_vertices.data(), m_vertices.size() * sizeof(QVector3D));
}

void SquareSurface::setColor(const QColor &color) { m_color = color; }
