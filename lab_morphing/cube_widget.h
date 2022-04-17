#pragma once
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QApplication>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "cube.h"
#include "color_widget.h"

class CubeWidget final : public QOpenGLWidget, protected QOpenGLFunctions {
public slots:
    void setCubeColor(const QColor& color);

    void setGrid(int value);

    void setMorph(int value);
private slots:
	void callColorDialog();

    void closeColorDialog() const;
private:
    ColorWidget* m_colorWidget = nullptr;

    void initializeGL() override;

    void paintGL() override;

    void initShaders();

    QOpenGLShaderProgram m_program;

    std::unique_ptr<Cube> m_cube;

    QColor m_cubeColor {200, 255, 100};

    float m_cubeEdgeLen = 2.0f;

    float m_morphRate = 0;
};