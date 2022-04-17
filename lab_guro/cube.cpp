#include "cube.h"

Cube::Cube(const GLfloat edgeLen, const GLint gridStep) : m_edgeLen(edgeLen), m_gridStep(gridStep),
                                                          m_vertexBuf(QOpenGLBuffer::VertexBuffer),
                                                          m_indexBuf(QOpenGLBuffer::IndexBuffer) {}


auto Cube::initialize() -> void {
	initializeOpenGLFunctions();
	m_vertexBuf.create();
	m_indexBuf.create();

	QMatrix4x4 matrix;
	setFace(matrix);

	matrix.rotate(90.f, 0.f, 1.f);
	setFace(matrix);

	matrix.setToIdentity();
	matrix.rotate(180.f, 0.f, 1.f);
	setFace(matrix);

	matrix.setToIdentity();
	matrix.rotate(270.f, 0.f, 1.f);
	setFace(matrix);

	matrix.setToIdentity();
	matrix.rotate(90.f, 1.f, 0.f);
	setFace(matrix);

	matrix.setToIdentity();
	matrix.rotate(-90.f, 1.f, 0.f);
	setFace(matrix);

	m_vertexBuf.bind();
	m_vertexBuf.allocate(m_vertices.data(), m_vertices.size() * sizeof(Vertex));

	m_indexBuf.bind();
	m_indexBuf.allocate(m_indices.data(), m_indices.size() * sizeof(unsigned));
}

auto Cube::render(QOpenGLShaderProgram& program) -> void {
	m_vertexBuf.bind();
	m_indexBuf.bind();
	program.enableAttributeArray("posAttr");
	program.setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, sizeof(Vertex));

	program.enableAttributeArray("normAttr");
	program.setAttributeBuffer("normAttr", GL_FLOAT, offsetof(Vertex, normal), 3, sizeof(Vertex));

	program.setUniformValue("objectColor", m_color);

	glPolygonMode(GL_FRONT, GL_FILL);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

auto Cube::setColor(const QColor& color) -> void { m_color = color; }

auto Cube::getColor() const -> QColor { return m_color; }

auto Cube::setFace(const QMatrix4x4& matrix) -> void {
	const auto step = m_edgeLen / m_gridStep;
	auto a = m_edgeLen / 2;
	const auto prev_size = m_vertices.size();

	for (size_t j = 0; j <= m_gridStep; ++j) {
		for (size_t i = 0; i <= m_gridStep; ++i) {
			m_vertices.push_back({{-a + step * i, -a + step * j, a}, {0.f, 0.f, 1.f}});
		}
	}


	for (auto& vertex : m_vertices) {
		vertex = {matrix.map(vertex.position), matrix.inverted().transposed().map(vertex.normal)};
	}

	for (size_t i = 0; i < m_gridStep; ++i) {
		for (size_t j = 0; j < m_gridStep; ++j) {
			const auto first = prev_size + i + (j + 1) * (m_gridStep + 1);;
			const auto second = prev_size + i + j * (m_gridStep + 1);

			m_indices.push_back(first);
			m_indices.push_back(second);
			m_indices.push_back(second + 1);
			m_indices.push_back(second + 1);
			m_indices.push_back(first + 1);
			m_indices.push_back(first);
		}
	}
}

Cube::~Cube() {
	m_vertexBuf.destroy();
	m_indexBuf.destroy();
}
