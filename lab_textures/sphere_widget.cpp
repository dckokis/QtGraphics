#include "sphere_widget.h"
#include <QKeyEvent>

SphereWidget::SphereWidget(QWidget* parent)
	: QOpenGLWidget(parent) {}

auto SphereWidget::initializeGL() -> void {
	initializeOpenGLFunctions();

	initShaders();
	initTextures();

	m_lighter.initialize();
	m_earth.initialize();

	setFocusPolicy(Qt::StrongFocus);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

auto SphereWidget::paintGL() -> void {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	QMatrix4x4 projection;
	projection.perspective(30.f, 1.7f, 0.1f, 100.0f);
	m_sphereProgram.bind();

	QMatrix4x4 s_model;
	s_model.translate(m_earthPos);
	s_model.rotate(0.25f * m_frame, 0, 1);
	s_model.rotate(-90.f, 1, 0, 0);

	m_sphereProgram.setUniformValue("model", s_model);
	m_sphereProgram.setUniformValue("view", m_camera.getViewMatrix());
	m_sphereProgram.setUniformValue("lightPos", m_lighter.getPos());
	m_sphereProgram.setUniformValue("viewPos", m_camera.getPos());
	m_sphereProgram.setUniformValue("projection", projection);

	m_sphereProgram.setUniformValue("texture", 0);
	glActiveTexture(GL_TEXTURE0);
	m_earthTexture->bind();

	m_sphereProgram.setUniformValue("normalMap", 1);
	glActiveTexture(GL_TEXTURE1);
	m_earthNormalMap->bind();

	m_sphereProgram.setUniformValue("ambCol", m_lighter.getColor().ambient);
	m_sphereProgram.setUniformValue("diffCol", m_lighter.getColor().diffuse);
	m_sphereProgram.setUniformValue("specCol", m_lighter.getColor().specular);

	m_earth.render(m_sphereProgram);
	m_lighterProgram.bind();

	QMatrix4x4 l_model;
	l_model.translate(m_lighter.getPos());
	l_model.rotate(m_frame / 2.f, 0, 1);
	l_model.rotate(-90.f, 1, 0, 0);

	m_lighterProgram.setUniformValue("matrix", projection * m_camera.getViewMatrix() * l_model);
	m_lighterProgram.setUniformValue("texture", 0);
	glActiveTexture(GL_TEXTURE0);
	m_sunTexture->bind();

	m_lighter.render(m_lighterProgram);

	update();
	++m_frame;
}

auto SphereWidget::initShaders() -> void {
	m_sphereProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/sphere.vsh");
	m_sphereProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "Shaders/sphere.fsh");
	m_sphereProgram.link();

	m_lighterProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "Shaders/lighter.vsh");
	m_lighterProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
	                                         "Shaders/lighter.fsh");
	m_lighterProgram.link();
}

auto SphereWidget::initTextures() -> void {
	m_earthTexture.reset(new QOpenGLTexture(QImage("Textures/8k_earth_daymap.jpg")));
	m_earthTexture->setMinificationFilter(QOpenGLTexture::Nearest);

	m_sunTexture.reset(new QOpenGLTexture(QImage("Textures/Sun.jpg")));
	m_sunTexture->setMinificationFilter(QOpenGLTexture::Nearest);

	m_earthNormalMap.reset(new QOpenGLTexture(QImage("Textures/8k_earth_normal_map.jpg")));
	m_sunTexture->setMinificationFilter(QOpenGLTexture::Nearest);
}

auto SphereWidget::wheelEvent(QWheelEvent* event) -> void {
	auto dr = 0.f;
	if (event->angleDelta().y() > 0) { dr = m_camera.getFront().z() / abs(m_camera.getFront().z()); }
	else if (event->angleDelta().y() < 0) { dr = -m_camera.getFront().z() / abs(m_camera.getFront().z()); }
	m_camera.setPos({
		m_camera.getPos().x() + dr * m_camera.getFront().x(),
		m_camera.getPos().y() + dr * m_camera.getFront().y(),
		m_camera.getPos().z() + dr * m_camera.getFront().z()
	});
}
