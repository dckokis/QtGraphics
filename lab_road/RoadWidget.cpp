#include "RoadWidget.h"

#include <QMouseEvent>

void RoadWidget::initUniforms() {
	Q_ASSERT(m_program != nullptr);
	m_lightPosUniform = m_program->uniformLocation("lightPos");
	Q_ASSERT(m_lightPosUniform != -1);
	m_ambientIntensityUniform = m_program->uniformLocation("ambientIntensity");
	Q_ASSERT(m_ambientIntensityUniform != -1);
	m_ambientColorUniform = m_program->uniformLocation("ambientColor");
	Q_ASSERT(m_ambientColorUniform != -1);
	m_lightColorUniform = m_program->uniformLocation("lightColor");
	Q_ASSERT(m_lightColorUniform != -1);
	m_diffuseIntensityUniform = m_program->uniformLocation("diffuseIntensity");
	Q_ASSERT(m_diffuseIntensityUniform != -1);
	m_specularIntensityUniform = m_program->uniformLocation("specularIntensity");
	Q_ASSERT(m_diffuseIntensityUniform != -1);
	m_viewPosUniform = m_program->uniformLocation("viewPos");
	Q_ASSERT(m_viewPosUniform != -1);
	m_mixParameterUniform = m_program->uniformLocation("mixParameter");
	Q_ASSERT(m_mixParameterUniform != -1);
}

void RoadWidget::setUniforms() const {
	m_program->setUniformValue(m_lightPosUniform, m_lightPos);
	m_program->setUniformValue(m_lightColorUniform, m_lightColor);
	m_program->setUniformValue(m_ambientIntensityUniform, 1.0f);
	m_program->setUniformValue(m_diffuseIntensityUniform, m_diffuseIntensity);
	m_program->setUniformValue(m_ambientColorUniform, m_ambientColor);
	m_program->setUniformValue(m_specularIntensityUniform, m_specularIntensity);
	m_program->setUniformValue(m_viewPosUniform, m_viewPos);
	m_program->setUniformValue(m_mixParameterUniform, m_mixParameter);
}

void RoadWidget::setLightPos(const QVector3D pos) { m_lightPos = pos; }

void RoadWidget::setLightColor(const QColor color) { m_lightColor = {color.redF(), color.greenF(), color.blueF()}; }

void RoadWidget::setAmbientColor(const QColor color) { m_ambientColor = {color.redF(), color.greenF(), color.blueF()}; }

void RoadWidget::changeRoadFiltering(int filt) const {
	m_road->changeFilterType(ROAD, static_cast<FilteringType>(filt));
}

void RoadWidget::changeRockFiltering(int filt) const {
	m_road->changeFilterType(ROCK, static_cast<FilteringType>(filt));
}

void RoadWidget::changeCracksFiltering(int filt) const {
	m_road->changeFilterType(CRACKS, static_cast<FilteringType>(filt));
}

void RoadWidget::changeMixParameter(const int value) { m_mixParameter = static_cast<float>(value) / 100; }

RoadWidget::RoadWidget(QWidget* parent) : QOpenGLWidget(parent) {
	setAmbientColor({255, 255, 255});
	setLightColor({255, 255, 255});
	setLightPos({2, 2, 1});
	m_road = std::make_shared<Road>();
}

void RoadWidget::initializeGL() {

	m_program = new QOpenGLShaderProgram(this);

	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/vertexShader.vsh");
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/fragmentShader.fsh");

	m_program->link();

	initUniforms();

	m_road->initialize(m_program);

	QOpenGLWidget::initializeGL();
	glClearColor(m_backColor.red(), m_backColor.green(), m_backColor.blue(), 1);
	glEnable(GL_DEPTH_TEST);
}

void RoadWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	const auto retina_scale = devicePixelRatio();
	glViewport(0, 0, width() * retina_scale, height() * retina_scale);

	QMatrix4x4 matrix;
	matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	matrix.translate(m_viewPos.x(), m_viewPos.y(), m_viewPos.z());

	m_program->bind();

	setUniforms();

	m_road->setTotalMatrix(matrix);
	m_road->render();

	glClearColor(m_backColor.redF(), m_backColor.greenF(), m_backColor.blueF(), 1);
	m_program->release();
	update();
}

void RoadWidget::resizeGL(const int w, const int h) { glViewport(0, 0, w, h); }

void RoadWidget::wheelEvent(QWheelEvent* event) {
	constexpr float scale = 1.0 / 60.0;
	const auto num_degrees = event->angleDelta().y();
	const auto new_z = m_moveScale *scale * num_degrees + m_viewPos.z();
	m_viewPos.setZ( new_z);
	constexpr float optim_z = -7;
	//m_moveScale = 0.1 * abs((m_viewPos.z() / optim_z));

}
