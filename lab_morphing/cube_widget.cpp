#include "cube_widget.h"


void CubeWidget::setCubeColor(const QColor& color) {
    m_cubeColor = color;
}

void CubeWidget::setGrid(const int value) {
    m_cube.reset(new Cube(m_cubeEdgeLen, value));
    m_cube->initialize();
}

void CubeWidget::setMorph(const int value) {
    m_morphRate = value / 10.0f;
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
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           R"(C:\ComputerGraphics\lab_morphing\morphing\vertex.vsh)")) {
        close();
    }
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           R"(C:\ComputerGraphics\lab_morphing\morphing\fragment.fsh)")) {
        close();
    }
    if (!m_program.link()) {
        close();
    }
    if (!m_program.bind()) {
        close();
    }
}

void CubeWidget::initializeGL() {
    initializeOpenGLFunctions();
    initShaders();

    m_cube.reset(new Cube(m_cubeEdgeLen, 1));
    m_cube->initialize();

    glClearColor(0.3f, 0.3f, 0.3f, 1000.0f);
    glEnable(GL_CULL_FACE);
}

void CubeWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

	const auto* colorButton = new QPushButton("Color", this);
    connect(colorButton, &QAbstractButton::clicked, this, &CubeWidget::callColorDialog);

    QMatrix4x4 matrix;
    matrix.perspective(90.0f, 4.0f / 3.0f, 0.1f, 50.0f);
    matrix.translate(0, -1.5, -4.1);

    m_program.setUniformValue("matrix", matrix);
    m_program.setUniformValue("morphRate", m_morphRate);

    m_cube->setColor(m_cubeColor);
    m_cube->render(m_program);
    update();
}
