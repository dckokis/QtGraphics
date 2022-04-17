#include "cube_widget.h"

#include <iostream>

void CubeWidget::setCubeColor(const QColor& color) {
    m_cubeColor = color;
}

void CubeWidget::setNumberOfCubes(const int value)
{
    m_cubesAmount = value != 1 ? 2 * value : 1;
    initCubes();
}

void CubeWidget::callColorDialog() {
    m_colorWidget = new ColorWidget();
    connect(m_colorWidget->getColorDialog(), &QColorDialog::currentColorChanged, this, &CubeWidget::setCubeColor);
    connect(m_colorWidget->getColorDialog(), &QColorDialog::colorSelected, this, &CubeWidget::closeColorDialog);
    m_colorWidget->move(950, 100);
    m_colorWidget->show();
}

void CubeWidget::closeColorDialog() const {
    m_colorWidget->hide();
}

void CubeWidget::initShaders() {
    if (!m_lightProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           R"(C:\ComputerGraphics\lab_phong\light.vsh)")) {
        close();
    }
    if (!m_lightProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           R"(C:\ComputerGraphics\lab_phong\light.fsh)")) {
        close();
    }
    if (!m_lightProgram.link()) {
        close();
    }
    if (!m_lightProgram.bind()) {
        close();
    }

    if (!m_objectProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           R"(C:\ComputerGraphics\lab_phong\vertex.vsh)")) {
        close();
    }
    if (!m_objectProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           R"(C:\ComputerGraphics\lab_phong\fragment.fsh)")) {
        close();
    }
    if (!m_objectProgram.link()) {
        close();
    }
    if (!m_objectProgram.bind()) {
        close();
    }
}

void CubeWidget::initCubes()
{
	const auto prev_size = m_cubes.size();
    m_cubes.resize(m_cubesAmount);
    if (prev_size >= m_cubesAmount){
        return;
    }
    std::for_each(m_cubes.begin() + prev_size, m_cubes.end(), [&](std::unique_ptr<Cube>& cube){
        cube.reset(new Cube(m_cubeEdgeLen, m_gridStep));
        cube->initialize();
    });
}



void CubeWidget::initLights() {
    m_pointLight.setPos(m_pointStartPos);
    m_pointLight.setColor( { 255, 0, 255 } );
    m_pointLight.initialize();
	m_directedLight.setPos(m_directedStartPos);
    m_directedLight.setColor({255, 255, 0});
    m_directedLight.initialize();
    m_projectorLight.setPos(m_projectorStartPos);
    m_projectorLight.setColor( { 255, 255,  0} );
    m_projectorLight.initialize();
}

void CubeWidget::initializeGL() {
    initLights();
    initializeOpenGLFunctions();
    initShaders();
    initCubes();
    m_timer.start();
	glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void CubeWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(m_ambientLight.color.red()/255, m_ambientLight.color.green()/255, m_ambientLight.color.blue()/255, 1000);
    m_frames++;
    m_fpsLabel.setParent(this);
    m_fpsLabel.setText(m_fps);
    m_fpsLabel.setStyleSheet("QLabel { background-color : black; color : red; }");
    m_fpsLabel.move(100, 0);
    if (m_timer.elapsed() > 1000)
    {
	    const int sec = m_timer.elapsed()/1000;
	    m_fps = "FPS:" + QString::number(m_frames/sec);
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

    const auto rows = static_cast<int>(m_cubes.size() / std::sqrt(m_cubes.size()));
    const auto cols = static_cast<int>(m_cubes.size() / rows);

    for (auto i = 0; i < cols; ++i){
        for (auto j = 0; j < rows; ++j){
            QMatrix4x4 model;
            model.translate(- 1.5f * m_cubeEdgeLen * rows / 2 + i * 2.f * m_cubeEdgeLen, 0, - 12.5f - j * 2.f * m_cubeEdgeLen);
            model.rotate(0.5f * m_rotationFactor, 0, 1, 0);
            m_objectProgram.setUniformValue("model", model);
            m_cubes[i * rows + j]->render(m_objectProgram);
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


void CubeWidget::setGrid(const GLint value) {
     std::for_each(m_cubes.begin(), m_cubes.end(), [&](std::unique_ptr<Cube>& cube){
        cube.reset(new Cube(m_cubeEdgeLen, value));
        cube->initialize();
    });
}

void CubeWidget::moveCamera(const int position)
{
    m_camera.setPosZ(static_cast<float>(position));
}


void CubeWidget::setAmbientCoef(const int value)
{
    m_ka = static_cast<float>(value) / 20;
}


void CubeWidget::setDiffuseCoef(const int value)
{
    m_kd = static_cast<float>(value) / 20;
}


void CubeWidget::setSpecularCoef(const int value)
{
    m_ks = static_cast<float>(value) / 20;
}

void CubeWidget::switchAmbient()
{
    m_ambientLight.is_enabled = !m_ambientLight.is_enabled;
}

void CubeWidget::switchPointLight()
{
    m_pointLight.Switch();
}

void CubeWidget::switchDirectedLight()
{
    m_directedLight.Switch();
}

void CubeWidget::switchProjector()
{
    m_projectorLight.Switch();
}

void CubeWidget::setAmbientColor(const QColor& color)
{
    m_ambientLight.color = color;
}


void CubeWidget::setPointLightColor(const QColor& color)
{
    m_pointLight.setColor(color);
}


void CubeWidget::setDirectedLightColor(const QColor& color)
{
    m_directedLight.setColor(color);
}


void CubeWidget::setProjectorColor(const QColor& color)
{
    m_projectorLight.setColor(color);
}

void CubeWidget::setPointLightX(const double x)
{
    m_pointLight.setPos( { static_cast<float>(x), m_pointLight.getPos().y(), m_pointLight.getPos().z() } );
}


void CubeWidget::setPointLightY(const double y)
{
    m_pointLight.setPos( { m_pointLight.getPos().x(), static_cast<float>(y), m_pointLight.getPos().z() } );
}


void CubeWidget::setPointLightZ(const double z)
{
    m_pointLight.setPos( { m_pointLight.getPos().x(), m_pointLight.getPos().y(), static_cast<float>(z) } );
}


void CubeWidget::setDirectedLightX(const double x)
{
    m_directedLight.setPos( { static_cast<float>(x), m_directedLight.getPos().y(), m_directedLight.getPos().z() } );
}


void CubeWidget::setDirectedLightY(const double y)
{
    m_directedLight.setPos( { m_directedLight.getPos().x(), static_cast<float>(y), m_directedLight.getPos().z() } );
}


void CubeWidget::setDirectedLightZ(const double z)
{
    m_directedLight.setPos( { m_directedLight.getPos().x(), m_directedLight.getPos().y(), static_cast<float>(z) } );
}


void CubeWidget::setProjectorLightX(const double x)
{
    m_projectorLight.setPos( { static_cast<float>(x), m_projectorLight.getPos().y(), m_projectorLight.getPos().z() } );
}


void CubeWidget::setProjectorLightY(const double y)
{
    m_projectorLight.setPos( { m_projectorLight.getPos().x(), static_cast<float>(y), m_projectorLight.getPos().z() } );
}


void CubeWidget::setProjectorLightZ(const double z)
{
    m_projectorLight.setPos( { m_projectorLight.getPos().x(), m_projectorLight.getPos().y(), static_cast<float>(z) } );
}

void CubeWidget::setProjectorDirX(const double x)
{
    m_projectorDirection.setX(static_cast<float>(x));
}

void CubeWidget::setProjectorDirY(const double y)
{
    m_projectorDirection.setY(static_cast<float>(y));
}

void CubeWidget::setProjectorDirZ(const double z)
{
    m_projectorDirection.setZ(static_cast<float>(z));
}
