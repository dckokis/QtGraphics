#include "Object.h"

Object::Object(std::string name) : m_name(std::move(name)) {}


auto Object::initialize() -> void {
	initializeOpenGLFunctions();
	m_vertexBuf.create();
	m_indexBuf.create();

	if (MeshLoader::load(std::string("Materials/" + m_name + ".obj"),
		m_vertices, m_indices) == MlResult::ML_FAIL) {
		return;
	}

	m_vertexBuf.bind();
	m_vertexBuf.allocate(m_vertices.data(), m_vertices.size() * sizeof(Vertex));

	m_indexBuf.bind();
	m_indexBuf.allocate(m_indices.data(), m_indices.size() * sizeof(unsigned));
}

auto Object::render(QOpenGLShaderProgram& program) -> void {
	m_vertexBuf.bind();
	m_indexBuf.bind();
	program.enableAttributeArray("posAttr");
	program.setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, sizeof(Vertex));

	program.enableAttributeArray("normAttr");
	program.setAttributeBuffer("normAttr", GL_FLOAT, offsetof(Vertex, m_normal), 3, sizeof(Vertex));

	program.setUniformValue("objectColor", m_color);

	glPolygonMode(GL_FRONT, GL_FILL);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}

Object::~Object() {
	m_vertexBuf.destroy();
	m_indexBuf.destroy();
}

auto Object::getName() const -> std::string { return m_name; }

auto Object::setName(const std::string& name) -> void { m_name = name; }

auto Object::getColor() const -> QColor { return m_color; }

auto Object::setColor(const QColor& color) -> void { m_color = color; }
