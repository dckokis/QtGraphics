#include "road.h"

Road::Road() { m_textureNames = {"texRock", "texRoad", "texCracks"}; }

void Road::changeFilterType(const TextrureType texture, const FilteringType filt) {
	Q_ASSERT(filt >= 0 && filt < 3);
	m_textureFiltering[texture] = m_possibleFilters[filt];
}

void Road::updateTextures() {
	for (auto i = 0; i < m_textures.size(); ++i) {
		const auto& tex = m_textures[i];
		const auto filt = m_textureFiltering[i];
		tex->setMinMagFilters(filt, filt);
		auto& name = m_textureNames[i];
		m_program->setUniformValue(name.c_str(), i);
		glActiveTexture(GL_TEXTURE0 + i);
		tex->bind();
	}
}

void Road::initTextures() {
	m_textures.push_back(std::make_shared<QOpenGLTexture>(QImage{"Materials/road_2.jpg"}));
	m_textures[ROCK]->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
	m_textures[ROCK]->setMaximumAnisotropy(1.0f);
	m_textures.push_back(std::make_shared<QOpenGLTexture>(QImage("Materials/road_1.jpg")));
	m_textures[ROAD]->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
	m_textures.push_back(std::make_shared<QOpenGLTexture>(QImage("Materials/road_3.jpg")));
	m_textures[CRACKS]->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
}

void Road::setTotalMatrix(const QMatrix4x4& newTotalMatrix) { m_totalMatrix = newTotalMatrix; }

void Road::initialize(QOpenGLShaderProgram* prog) {
	initializeOpenGLFunctions();
	m_program = prog;
	initUniforms();
	initTextures();
	update();
}

void Road::render() {
	setUniforms();
	updateTextures();
	glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, m_vertices.data());
	glEnableVertexAttribArray(m_posAttr);
	glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_INT, m_indices.data());
	glDisableVertexAttribArray(m_posAttr);
}

void Road::initUniforms() {
	m_posAttr = m_program->attributeLocation("posAttr");
	Q_ASSERT(m_posAttr != -1);
	m_normalUniform = m_program->uniformLocation("normal");
	Q_ASSERT(m_normalUniform != -1);
	m_totalMatrixUniform = m_program->uniformLocation("totalMatrix");
	Q_ASSERT(m_totalMatrixUniform != -1);
	m_widhtUniform = m_program->uniformLocation("x_size");
	Q_ASSERT(m_widhtUniform != -1);
	m_heightUniform = m_program->uniformLocation("z_size");
	Q_ASSERT(m_heightUniform != -1);
}

void Road::setUniforms() const {
	m_program->setUniformValue(m_globalMatrixUniform, m_globalPosMatrix);
	m_program->setUniformValue(m_relativeMatrixUniform, m_relativePosMatrix);
	m_program->setUniformValue(m_normalUniform, m_normal);
	m_program->setUniformValue(m_totalMatrixUniform, m_totalMatrix);
	m_program->setUniformValue(m_widhtUniform, m_widht);
	m_program->setUniformValue(m_heightUniform, m_height);
}

void Road::update() {
	const auto base_point = QVector3D{-5, -2, 0};
	m_vertices[0] = base_point + QVector3D{0, 0, -m_height};
	m_vertices[1] = base_point + QVector3D{m_widht, 0, -m_height};
	m_vertices[2] = base_point + QVector3D{m_widht, 0, 0};
	m_vertices[3] = base_point;
}
