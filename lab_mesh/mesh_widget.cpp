#include "mesh_widget.h"

auto MeshWidget::initShaders() -> void {
	m_objectProgram.removeAllShaders();
	if (!m_objectProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
	                                             R"(Shaders/guro_vertex.vsh)")) { close(); }
	if (!m_objectProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
	                                             R"(Shaders/guro_fragment.fsh)")) { close(); }
	if (!m_objectProgram.link()) { close(); }
	if (!m_objectProgram.bind()) { close(); }
}

auto MeshWidget::initLights() -> void {
	if (!m_lightProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
	                                            R"(Shaders/light.vsh)")) { close(); }
	if (!m_lightProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
	                                            R"(Shaders/light.fsh)")) { close(); }
	if (!m_lightProgram.link()) { close(); }
	if (!m_lightProgram.bind()) { close(); }
	m_directedLight.setPos(m_directedStartPos);
	m_directedLight.initialize();
}

auto MeshWidget::initializeGL() -> void {
	initializeOpenGLFunctions();
	initShaders();
	initLights();
	m_objects.emplace_back(new Object("MeshCube"));
	m_objects.emplace_back(new Object("MeshSphere"));
	m_objects.emplace_back(new Object("MeshHouse"));
	for (const auto& object : m_objects) { object->initialize(); }
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

auto MeshWidget::paintGL() -> void {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_objectProgram.bind();
	m_objectProgram.setUniformValue("ka", m_ka);
	m_objectProgram.setUniformValue("kd", m_kd);
	m_objectProgram.setUniformValue("ks", m_ks);

	m_objectProgram.setUniformValue("directedColor", m_directedLight.getColor());
	m_objectProgram.setUniformValue("directedPos", m_directedLight.getPos());
	m_objectProgram.setUniformValue("isDirected", m_directedLight.isEnabled());

	m_objectProgram.setUniformValue("view", m_camera.getViewMatrix());
	m_objectProgram.setUniformValue("viewPos", m_camera.getPos());

	QMatrix4x4 projection;
	projection.perspective(90.0f, 4.0f / 3.0f, 0.1f, 1000000.0f);
	m_objectProgram.setUniformValue("projection", projection);

	auto model_num = 0;
	for (const auto& object : m_objects) {
		QMatrix4x4 model;
		int a;
		if (model_num % 2 == 0) { a = 1; }
		else { a = -1; }
		model.translate(a * 5.f * model_num, 0, 0);
		model.rotate(0.5f * m_rotationFactor, 0, 1, 0);
		m_objectProgram.setUniformValue("model", model);
		object->render(m_objectProgram);
		model_num++;
	}

	m_lightProgram.bind();

	if (m_directedLight.isEnabled()) {
		QMatrix4x4 directed_matrix;
		directed_matrix.translate(m_directedLight.getPos());
		m_lightProgram.setUniformValue("matrix", projection * m_camera.getViewMatrix() * directed_matrix);
		m_directedLight.render(m_lightProgram);
	}

	m_rotationFactor++;
	update();
}

auto MeshWidget::moveCamera(const int position) -> void { m_camera.setPosZ(static_cast<float>(position)); }

auto MeshWidget::setAmbientCoef(const int value) -> void { m_ka = static_cast<float>(value) / 20; }

auto MeshWidget::setDiffuseCoef(const int value) -> void { m_kd = static_cast<float>(value) / 20; }

auto MeshWidget::setSpecularCoef(const int value) -> void { m_ks = static_cast<float>(value) / 20; }

auto MeshWidget::switchDirectedLight() -> void { m_directedLight.Switch(); }

auto MeshWidget::setDirectedLightX(const double x) -> void {
	m_directedLight.setPos({static_cast<float>(x), m_directedLight.getPos().y(), m_directedLight.getPos().z()});
}

auto MeshWidget::setDirectedLightY(const double y) -> void {
	m_directedLight.setPos({m_directedLight.getPos().x(), static_cast<float>(y), m_directedLight.getPos().z()});
}

auto MeshWidget::setDirectedLightZ(const double z) -> void {
	m_directedLight.setPos({m_directedLight.getPos().x(), m_directedLight.getPos().y(), static_cast<float>(z)});
}
