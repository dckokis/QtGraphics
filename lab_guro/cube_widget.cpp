#include "cube_widget.h"

auto CubeWidget::switchShaderType() -> void {
	m_shType = m_shType == shader_type::PIXEL ? shader_type::VERTEX : shader_type::PIXEL;
	m_shTypeChanged = true;
}

auto CubeWidget::setCubeColor(const QColor& color) -> void { m_cubeColor = color; }

auto CubeWidget::setNumberOfCubes(const int value) -> void { m_cubesAmount = value != 1 ? value ^ 2 : 1; }

auto CubeWidget::callColorDialog() -> void {
	m_colorWidget = new ColorWidget();
	connect(m_colorWidget->getColorDialog(), &QColorDialog::currentColorChanged, this, &CubeWidget::setCubeColor);
	connect(m_colorWidget->getColorDialog(), &QColorDialog::colorSelected, this, &CubeWidget::closeColorDialog);
	m_colorWidget->move(950, 100);
	m_colorWidget->show();
}

auto CubeWidget::closeColorDialog() const -> void { m_colorWidget->hide(); }

auto CubeWidget::initShaders() -> void {
	m_objectProgram.removeAllShaders();
	switch (m_shType) {
	case shader_type::PIXEL:
		if (!m_objectProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
		                                             R"(guro_vertex.vsh)")) { close(); }
		if (!m_objectProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
		                                             R"(guro_fragment.fsh)")) { close(); }
		break;
	case shader_type::VERTEX:
		if (!m_objectProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
		                                             R"(vertex.vsh)")) { close(); }
		if (!m_objectProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
		                                             R"(fragment.fsh)")) { close(); }
	}
	if (!m_objectProgram.link()) { close(); }
	if (!m_objectProgram.bind()) { close(); }
}

auto CubeWidget::initLights() -> void {
	if (!m_lightProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
	                                            R"(light.vsh)")) { close(); }
	if (!m_lightProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
	                                            R"(light.fsh)")) { close(); }
	if (!m_lightProgram.link()) { close(); }
	if (!m_lightProgram.bind()) { close(); }
	m_pointLight.setPos(m_pointStartPos);
	m_pointLight.setColor({255, 0, 255});
	m_pointLight.initialize();
	m_directedLight.setPos(m_directedStartPos);
	m_directedLight.setColor({255, 255, 0});
	m_directedLight.initialize();
	m_projectorLight.setPos(m_projectorStartPos);
	m_projectorLight.setColor({255, 255, 0});
	m_projectorLight.initialize();
}

auto CubeWidget::initializeGL() -> void {
	initLights();
	initializeOpenGLFunctions();
	initShaders();
	m_cube = new Cube(m_cubeEdgeLen, m_gridStep);
	m_cube->initialize();
	m_timer.start();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

auto CubeWidget::paintGL() -> void {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.f, 1.f, 1.f, 1000);

	if (m_shTypeChanged) {
		initShaders();
		m_shTypeChanged = false;
	}

	m_frames++;
	m_fpsLabel.setParent(this);
	m_fpsLabel.setText(m_fps);
	m_fpsLabel.setStyleSheet("QLabel { background-color : black; color : red; }");
	m_fpsLabel.move(100, 0);
	if (m_timer.elapsed() > 1000) {
		const int sec = m_timer.elapsed() / 1000;
		m_fps = "FPS:" + QString::number(m_frames / sec);
		m_frames = 0;
		m_timer.restart();
	}

	const auto* color_button = new QPushButton("Color", this);
	connect(color_button, &QAbstractButton::clicked, this, &CubeWidget::callColorDialog);

	m_objectProgram.bind();
	m_objectProgram.setUniformValue("ka", m_ka);
	m_objectProgram.setUniformValue("kd", m_kd);
	m_objectProgram.setUniformValue("ks", m_ks);

	m_objectProgram.setUniformValue("ambientColor", m_ambientLight.color);
	m_objectProgram.setUniformValue("isAmbient", m_ambientLight.is_enabled);

	m_objectProgram.setUniformValue("pointColor", m_pointLight.getColor());
	m_objectProgram.setUniformValue("pointPos", m_pointLight.getPos());
	m_objectProgram.setUniformValue("isPoint", m_pointLight.isEnabled());

	m_objectProgram.setUniformValue("directedColor", m_directedLight.getColor());
	m_objectProgram.setUniformValue("directedPos", m_directedLight.getPos());
	m_objectProgram.setUniformValue("isDirected", m_directedLight.isEnabled());

	m_objectProgram.setUniformValue("projectorColor", m_projectorLight.getColor());
	m_objectProgram.setUniformValue("projectorPos", m_projectorLight.getPos());
	m_objectProgram.setUniformValue("isProjector", m_projectorLight.isEnabled());
	m_objectProgram.setUniformValue("projDir", QVector3D(-m_projectorLight.getPos()).normalized());

	m_objectProgram.setUniformValue("view", m_camera.getViewMatrix());
	m_objectProgram.setUniformValue("viewPos", m_camera.getPos());

	QMatrix4x4 projection;
	projection.perspective(90.0f, 4.0f / 3.0f, 0.1f, 1000000.0f);
	m_objectProgram.setUniformValue("projection", projection);

	const auto rows = static_cast<int>(m_cubesAmount / std::sqrt(m_cubesAmount));
	const auto cols = static_cast<int>(m_cubesAmount / rows);

	for (auto i = 0; i < cols; ++i) {
		for (auto j = 0; j < rows; ++j) {
			QMatrix4x4 model;
			model.translate(-1.5f * m_cubeEdgeLen * rows / 2 + i * 2.f * m_cubeEdgeLen, 0,
			                - 12.5f - j * 2.f * m_cubeEdgeLen);
			model.rotate(0.5f * m_rotationFactor, 0, 1, 0);
			m_objectProgram.setUniformValue("model", model);
			m_cube->render(m_objectProgram);
		}
	}

	m_lightProgram.bind();
	if (m_pointLight.isEnabled()) {
		QMatrix4x4 point_matrix;
		point_matrix.translate(m_pointLight.getPos());
		m_lightProgram.setUniformValue("matrix", projection * m_camera.getViewMatrix() * point_matrix);
		m_pointLight.render(m_lightProgram);
	}

	if (m_directedLight.isEnabled()) {
		QMatrix4x4 directed_matrix;
		directed_matrix.translate(m_directedLight.getPos());
		m_lightProgram.setUniformValue("matrix", projection * m_camera.getViewMatrix() * directed_matrix);
		m_directedLight.render(m_lightProgram);
	}

	if (m_projectorLight.isEnabled()) {
		QMatrix4x4 projector_matrix;
		projector_matrix.translate(m_projectorLight.getPos());
		m_lightProgram.setUniformValue("matrix", projection * m_camera.getViewMatrix() * projector_matrix);
		m_projectorLight.render(m_lightProgram);
	}

	m_rotationFactor++;
	update();
}

auto CubeWidget::setGrid(const GLint value) -> void {
	m_cube = new Cube(m_cubeEdgeLen, value);
	m_cube->initialize();
}

auto CubeWidget::moveCamera(const int position) -> void { m_camera.setPosZ(static_cast<float>(position)); }


auto CubeWidget::setAmbientCoef(const int value) -> void { m_ka = static_cast<float>(value) / 20; }


auto CubeWidget::setDiffuseCoef(const int value) -> void { m_kd = static_cast<float>(value) / 20; }


auto CubeWidget::setSpecularCoef(const int value) -> void { m_ks = static_cast<float>(value) / 20; }

auto CubeWidget::switchAmbient() -> void { m_ambientLight.is_enabled = !m_ambientLight.is_enabled; }

auto CubeWidget::switchPointLight() -> void { m_pointLight.Switch(); }

auto CubeWidget::switchDirectedLight() -> void { m_directedLight.Switch(); }

auto CubeWidget::switchProjector() -> void { m_projectorLight.Switch(); }

auto CubeWidget::setAmbientColor(const QColor& color) -> void { m_ambientLight.color = color; }


auto CubeWidget::setPointLightColor(const QColor& color) -> void { m_pointLight.setColor(color); }


auto CubeWidget::setDirectedLightColor(const QColor& color) -> void { m_directedLight.setColor(color); }


auto CubeWidget::setProjectorColor(const QColor& color) -> void { m_projectorLight.setColor(color); }

auto CubeWidget::setPointLightX(const double x) -> void {
	m_pointLight.setPos({static_cast<float>(x), m_pointLight.getPos().y(), m_pointLight.getPos().z()});
}


auto CubeWidget::setPointLightY(const double y) -> void {
	m_pointLight.setPos({m_pointLight.getPos().x(), static_cast<float>(y), m_pointLight.getPos().z()});
}


auto CubeWidget::setPointLightZ(const double z) -> void {
	m_pointLight.setPos({m_pointLight.getPos().x(), m_pointLight.getPos().y(), static_cast<float>(z)});
}


auto CubeWidget::setDirectedLightX(const double x) -> void {
	m_directedLight.setPos({static_cast<float>(x), m_directedLight.getPos().y(), m_directedLight.getPos().z()});
}


auto CubeWidget::setDirectedLightY(const double y) -> void {
	m_directedLight.setPos({m_directedLight.getPos().x(), static_cast<float>(y), m_directedLight.getPos().z()});
}


auto CubeWidget::setDirectedLightZ(const double z) -> void {
	m_directedLight.setPos({m_directedLight.getPos().x(), m_directedLight.getPos().y(), static_cast<float>(z)});
}


auto CubeWidget::setProjectorLightX(const double x) -> void {
	m_projectorLight.setPos({static_cast<float>(x), m_projectorLight.getPos().y(), m_projectorLight.getPos().z()});
}


auto CubeWidget::setProjectorLightY(const double y) -> void {
	m_projectorLight.setPos({m_projectorLight.getPos().x(), static_cast<float>(y), m_projectorLight.getPos().z()});
}


auto CubeWidget::setProjectorLightZ(const double z) -> void {
	m_projectorLight.setPos({m_projectorLight.getPos().x(), m_projectorLight.getPos().y(), static_cast<float>(z)});
}

auto CubeWidget::setProjectorDirX(const double x) -> void { m_projectorDirection.setX(static_cast<float>(x)); }

auto CubeWidget::setProjectorDirY(const double y) -> void { m_projectorDirection.setY(static_cast<float>(y)); }

auto CubeWidget::setProjectorDirZ(const double z) -> void { m_projectorDirection.setZ(static_cast<float>(z)); }
