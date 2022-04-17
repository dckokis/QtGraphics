#ifndef CUBE_H
#define CUBE_H

#include "C:\\Qt\\Examples\\Qt-6.2.3\\opengl\\openglwindow\\openglwindow.h"
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QScreen>
#include <QtMath>
#include <QOpenGLShaderProgram>

class Cube
{
public:
    Cube() = default;
    const GLfloat* get_stripes(){
        return stripes;
    }
    const GLfloat* get_colors(){
        return colors;
    }
private:
    const GLfloat stripes[54] = {
        -1.f, 1.f, 1.f,
        1.f, 1.f, 1.f,
        -1.f, -1.f, 1.f,
        1.f, -1.f, 1.f,
        1.f, -1.f, -1.f,
        1.f, 1.f, 1.f,
        1.f, 1.f, -1.f,
        -1.f, 1.f, 1.f,
        -1.f, 1.f, -1.f,
        -1.f, -1.f, 1.f,
        -1.f, -1.f, -1.f,
        1.f, -1.f, -1.f,
        -1.f, 1.f, -1.f,
        1.f, 1.f, -1.f

    };

   const GLfloat colors[54] = {
       0.583f,  0.771f,  0.014f,
       0.609f,  0.115f,  0.436f,
       0.327f,  0.483f,  0.844f,
       0.822f,  0.569f,  0.201f,
       0.435f,  0.602f,  0.223f,
       0.310f,  0.747f,  0.185f,
       0.597f,  0.770f,  0.761f,
       0.559f,  0.436f,  0.730f,
       0.359f,  0.583f,  0.152f,
       0.483f,  0.596f,  0.789f,
       0.559f,  0.861f,  0.639f,
       0.195f,  0.548f,  0.859f,
       0.014f,  0.184f,  0.576f,
       0.771f,  0.328f,  0.970f,
       0.406f,  0.615f,  0.116f,
       0.676f,  0.977f,  0.133f,
       0.971f,  0.572f,  0.833f,
       0.140f,  0.616f,  0.489f
    };
};

#endif // CUBE_H

