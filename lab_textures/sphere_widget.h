#pragma once

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLTexture>
#include "sphere.h"
#include "lighter.h"
#include "camera.h"

class SphereWidget final : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
public:
	explicit SphereWidget(QWidget* parent = nullptr);

protected:
	virtual auto initializeGL() -> void override;

	virtual auto paintGL() -> void override;

	virtual auto wheelEvent(QWheelEvent* event) -> void override;

private:
	auto initShaders() -> void;

	auto initTextures() -> void;

	QOpenGLShaderProgram m_sphereProgram, m_lighterProgram;

	Sphere m_earth{0.4f, 500, 500};
	QVector3D m_earthPos{0.f, 0.f, -4.f};

	Lighter m_lighter;
	Camera m_camera;
	std::unique_ptr<QOpenGLTexture> m_earthTexture, m_earthNormalMap, m_sunTexture;

	unsigned m_frame = 0;
};
