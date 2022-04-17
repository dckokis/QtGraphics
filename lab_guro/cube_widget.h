#pragma once
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QApplication>
#include <QColorDialog>
#include <QPushButton>
#include <QElapsedTimer>
#include <QLabel>
#include <QPainter>
#include "light_source.h"
#include "color_widget.h"
#include "camera.h"


struct AmbientLight {
	QColor color{255, 255, 255};
	bool is_enabled = true;
};


enum class shader_type {
	PIXEL = 0,
	VERTEX = 1
};

class CubeWidget final : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
public slots:
	auto switchShaderType() -> void;

	auto setCubeColor(const QColor& color) -> void;

	auto setGrid(const int value) -> void;

	auto setNumberOfCubes(int value) -> void;

	auto moveCamera(const int position) -> void;

	auto setAmbientCoef(int value) -> void;

	auto setDiffuseCoef(int value) -> void;

	auto setSpecularCoef(int value) -> void;

	auto switchAmbient() -> void;

	auto switchPointLight() -> void;

	auto switchDirectedLight() -> void;

	auto switchProjector() -> void;

	auto setAmbientColor(const QColor& color) -> void;

	auto setPointLightColor(const QColor& color) -> void;

	auto setDirectedLightColor(const QColor& color) -> void;

	auto setProjectorColor(const QColor& color) -> void;

	auto setPointLightX(double x) -> void;

	auto setPointLightY(double y) -> void;

	auto setPointLightZ(double z) -> void;

	auto setDirectedLightX(double x) -> void;

	auto setDirectedLightY(double y) -> void;

	auto setDirectedLightZ(double z) -> void;

	auto setProjectorLightX(double x) -> void;

	auto setProjectorLightY(double y) -> void;

	auto setProjectorLightZ(double z) -> void;

	auto setProjectorDirX(double x) -> void;

	auto setProjectorDirY(double y) -> void;

	auto setProjectorDirZ(double z) -> void;


private slots:
	auto callColorDialog() -> void;

	auto closeColorDialog() const -> void;

public:
	[[nodiscard]] auto getPointStartPos() const -> QVector3D { return m_pointStartPos; }

	[[nodiscard]] auto getDirectedStartPos() const -> QVector3D { return m_directedStartPos; }

	[[nodiscard]] auto getProjectorStartPos() const -> QVector3D { return m_projectorStartPos; }

	[[nodiscard]] auto getProjectorDirection() const -> QVector3D { return m_projectorDirection; }

private:
	ColorWidget* m_colorWidget = nullptr;

	LightSource m_directedLight, m_pointLight, m_projectorLight;

	QVector3D m_pointStartPos = {15.f, 15.f, 1.f},
	          m_directedStartPos = {-20.f, 0.f, 1.f},
	          m_projectorStartPos = {0.0f, 0.0f, 20.f},
	          m_projectorDirection = QVector3D(0, 0, -1).normalized();

	auto initializeGL() -> void override;

	auto paintGL() -> void override;

	auto initShaders() -> void;

	auto initLights() -> void;

	auto initCubes() -> void;

	Camera m_camera;

	QOpenGLShaderProgram m_objectProgram, m_lightProgram;

	Cube* m_cube = nullptr;
	unsigned m_cubesAmount = 10;

	AmbientLight m_ambientLight;

	QColor m_cubeColor{255, 255, 255};

	float m_cubeEdgeLen = 6.f;

	int m_gridStep = 20;

	GLfloat m_ka = .2f, m_kd = .2f, m_ks = 1.f;

	size_t m_rotationFactor = 0;
	QLabel m_fpsLabel;
	QElapsedTimer m_timer;
	size_t m_frames = 0;
	QString m_fps = "FPS:    ";
	bool m_shTypeChanged = false;
	shader_type m_shType = shader_type::VERTEX;
};
