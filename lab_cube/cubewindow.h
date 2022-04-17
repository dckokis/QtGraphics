#ifndef CUBEWINDOW_H
#define CUBEWINDOW_H


#include "C:\\Qt\\Examples\\Qt-6.2.3\\opengl\\openglwindow\\openglwindow.h"
#include "cube.h"
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QScreen>
#include <QtMath>

class CubeWindow : public OpenGLWindow
{
public:
    using OpenGLWindow::OpenGLWindow;

    void initialize() override;
    void render() override;
//    void draw(int m_posAttr, int m_colAttr) {

//        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//        glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, NULL);

//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LESS);

//        glDrawArrays(GL_TRIANGLE_STRIP, 0, 18);
//    }
private:
    Cube cube;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    QOpenGLShaderProgram *m_program = nullptr;
    int m_frame = 0;
};

#endif // CUBEWINDOW_H
