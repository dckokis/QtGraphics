#define _USE_MATH_DEFINES
#include <cmath>
#include <QColor>
#include "sphere.h"

Sphere::Sphere(const GLfloat radius, const GLuint resolution)
	: m_radius(radius), m_resolution(resolution),
	  m_vertexBuf(QOpenGLBuffer::VertexBuffer),
	  m_indexBuf(QOpenGLBuffer::IndexBuffer) {}

auto Sphere::initialize() -> void {
	initializeOpenGLFunctions();
	m_vertexBuf.create();
	m_indexBuf.create();

	initVertices();
	initIndices();

	m_vertexBuf.bind();
	m_vertexBuf.allocate(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
	m_indexBuf.bind();
	m_indexBuf.allocate(m_indices.data(), m_indices.size() * sizeof(GLuint));
}

auto Sphere::render(QOpenGLShaderProgram& program) -> void {
	program.enableAttributeArray("posAttr");
	program.setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, sizeof(Vertex));

	program.enableAttributeArray("normAttr");
	program.setAttributeBuffer("normAttr", GL_FLOAT, offsetof(Vertex, normal), 3, sizeof(Vertex));

	program.enableAttributeArray("texAttr");
	program.setAttributeBuffer("texAttr", GL_FLOAT, offsetof(Vertex, texCoord), 2, sizeof(Vertex));
	glPolygonMode(GL_FRONT, GL_FILL);
	glDrawElements(GL_TRIANGLES, m_indexBuf.size(), GL_UNSIGNED_INT, nullptr);
};

Sphere::~Sphere() {
	m_vertexBuf.destroy();
	m_indexBuf.destroy();
}

auto Sphere::initVertices() -> void {
	const GLfloat horiz_step = 2 * M_PI / static_cast<GLfloat>(m_resolution);
	const GLfloat vert_step = M_PI / static_cast<GLfloat>(m_resolution);

	for (auto i = 0; i <= m_resolution; ++i) {
		const auto stack_angle = M_PI / 2 - static_cast<GLfloat>(i) * vert_step;
		const auto xy = m_radius * cos(stack_angle);
		GLfloat z = m_radius * sin(stack_angle);

		for (auto j = 0; j <= m_resolution; ++j) {
			Vertex vertex;
			const GLfloat sector_angle = static_cast<GLfloat>(j) * horiz_step;

			GLfloat x = xy * cos(sector_angle);
			GLfloat y = xy * sin(sector_angle);
			vertex.pos = {x, y, z};
			vertex.normal = {x / m_radius, y / m_radius, z / m_radius};

			vertex.texCoord = {static_cast<GLfloat>(j) / m_resolution, static_cast<GLfloat>(i) / m_resolution};

			m_vertices.push_back(vertex);
		}
	}
}

auto Sphere::initIndices() -> void {
	for (auto i = 0; i < m_resolution; ++i) {
		auto k1 = i * (m_resolution + 1);
		auto k2 = k1 + m_resolution + 1;

		for (auto j = 0; j < m_resolution; ++j, ++k1, ++k2) {
			if (i != 0) {
				m_indices.push_back(k1);
				m_indices.push_back(k2);
				m_indices.push_back(k1 + 1);
			}

			if (i != (m_resolution - 1)) {
				m_indices.push_back(k1 + 1);
				m_indices.push_back(k2);
				m_indices.push_back(k2 + 1);
			}
		}
	}
}
