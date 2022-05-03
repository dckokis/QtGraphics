#define _USE_MATH_DEFINES
#include <cmath>
#include <QColor>
#include "sphere.h"


Sphere::Sphere(const GLfloat radius, const GLuint lats, const GLuint longs)
	: m_radius(radius), m_lats(lats), m_longs(longs),
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
	const auto lat_step = 2 * M_PI / static_cast<float>(m_lats);
	const auto long_step = M_PI / static_cast<float>(m_longs);

	for (auto i = 0u; i <= m_longs; ++i) {
		const auto stack_angle = M_PI / 2 - static_cast<float>(i) * long_step;
		const auto xy = m_radius * cos(stack_angle);
		GLfloat z = m_radius * sin(stack_angle);

		for (auto j = 0u; j <= m_lats; ++j) {
			Vertex vertex;
			const GLfloat sector_angle = static_cast<float>(j) * lat_step;

			GLfloat x = xy * cos(sector_angle);
			GLfloat y = xy * sin(sector_angle);
			vertex.pos = {x, y, z};
			vertex.normal = {x / m_radius, y / m_radius, z / m_radius};

			vertex.texCoord = {static_cast<float>(j) / m_lats, static_cast<float>(i) / m_longs};

			m_vertices.push_back(vertex);
		}
	}
}


auto Sphere::initIndices() -> void {
	for (auto i = 0u; i < m_lats; ++i) {
		auto k1 = i * (m_longs + 1);
		auto k2 = k1 + m_longs + 1;

		for (auto j = 0u; j < m_longs; ++j, ++k1, ++k2) {
			if (i != 0) {
				m_indices.push_back(k1);
				m_indices.push_back(k2);
				m_indices.push_back(k1 + 1u);
			}

			if (i != (m_lats - 1)) {
				m_indices.push_back(k1 + 1u);
				m_indices.push_back(k2);
				m_indices.push_back(k2 + 1u);
			}
		}
	}
}
