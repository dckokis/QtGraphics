#include "cubewindow.h"

void CubeWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:\\Qt\\Examples\\Qt-6.2.3\\opengl\\openglwindow\\vertexShaderSource.vsh");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:\\Qt\\Examples\\Qt-6.2.3\\opengl\\openglwindow\\fragmentShaderSource.fsh");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = m_program->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

void CubeWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, -1.5, -4);
    matrix.rotate(50.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, cube.get_stripes());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, cube.get_colors());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 18);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    ++m_frame;
}
