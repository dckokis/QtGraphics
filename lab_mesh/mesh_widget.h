#pragma once
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QApplication>
#include <QElapsedTimer>
#include <QLabel>
#include <QPainter>
#include "light_source.h"
#include "camera.h"

class MeshWidget final : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
public slots:
	auto moveCamera(const int position) -> void;

	auto setAmbientCoef(const int value) -> void;

	auto setDiffuseCoef(int value) -> void;

	auto setSpecularCoef(int value) -> void;

	auto switchDirectedLight() -> void;

	auto setDirectedLightX(double x) -> void;

	auto setDirectedLightY(double y) -> void;

	auto setDirectedLightZ(double z) -> void;

public:
	[[nodiscard]] auto getDirectedStartPos() const -> QVector3D { return m_directedStartPos; }

private:
	LightSource m_directedLight;

	QVector3D m_directedStartPos = {-20.f, 0.f, 1.f};

	virtual auto initializeGL() -> void override;

	virtual auto paintGL() -> void override;

	auto initShaders() -> void;

	auto initLights() -> void;

	Camera m_camera;

	QOpenGLShaderProgram m_objectProgram, m_lightProgram;

	std::vector<Object*> m_objects;

	GLfloat m_ka = .2f, m_kd = .2f, m_ks = 1.f;

	size_t m_rotationFactor = 0;
};
