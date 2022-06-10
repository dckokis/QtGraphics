#pragma once

#include <vector>
#include <QtOpenGL>

enum TextrureType {
	ROCK,
	ROAD,
	CRACKS
};

enum FilteringType {
	NEAREST,
	LINEAR,
	LINEAR_MIP_MAP_LINEAR,
};

class Road final : public QOpenGLFunctions {

	QOpenGLShaderProgram* m_program = nullptr;
	const std::array<QOpenGLTexture::Filter, 3> m_possibleFilters = {
		QOpenGLTexture::Nearest, QOpenGLTexture::Linear, QOpenGLTexture::LinearMipMapLinear
	};
	std::vector<std::shared_ptr<QOpenGLTexture>> m_textures;
	std::vector<std::string> m_textureNames;
	std::vector<QOpenGLTexture::Filter> m_textureFiltering = {
		QOpenGLTexture::Nearest, QOpenGLTexture::Nearest, QOpenGLTexture::Nearest
	};

	QMatrix4x4 m_globalPosMatrix = {};
	QMatrix4x4 m_relativePosMatrix = {};
	QMatrix4x4 m_totalMatrix = {};

	std::vector<QVector3D> m_vertices = {{}, {}, {}, {}};
	std::vector<GLuint> m_indices = {0, 3, 1, 2};

	const QVector3D m_normal = {0, 1, 0};

	GLint m_posAttr = -1;
	GLint m_globalMatrixUniform = -1;
	GLint m_relativeMatrixUniform = -1;
	GLint m_normalUniform = -1;
	GLint m_totalMatrixUniform = -1;

	float m_widht = 1;
	GLint m_widhtUniform = -1;
	float m_height = 10000;
	GLint m_heightUniform = -1;

public:
	Road();

	void initialize(QOpenGLShaderProgram* prog);

	void render();

	void initUniforms();

	void setTotalMatrix(const QMatrix4x4& newTotalMatrix);

	void changeFilterType(TextrureType texture, FilteringType filt);

private:
	void updateTextures();
	void setUniforms() const;
	void initTextures();
	void update();
};
