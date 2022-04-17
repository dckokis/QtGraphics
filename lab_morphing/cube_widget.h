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
	auto setCubeColor(const QColor& color) -> void;

	auto setGrid(int value) -> void;

	auto setMorph(int value) -> void;

private slots:
	auto callColorDialog() -> void;

	auto closeColorDialog() const -> void;

private:
	ColorWidget* m_colorWidget = nullptr;

	auto initializeGL() -> void override;

	auto paintGL() -> void override;

	auto initShaders() -> void;

	QOpenGLShaderProgram m_program;

	std::unique_ptr<Cube> m_cube;

	QColor m_cubeColor{200, 255, 100};

	float m_cubeEdgeLen = 2.0f;

	float m_morphRate = 0;
};
