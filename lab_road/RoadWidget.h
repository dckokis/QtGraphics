#pragma once

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QColorDialog>
#include <thread>
#include <chrono>
#include "road.h"

class RoadWidget final : public QOpenGLWidget {
	Q_OBJECT
public slots:
	void changeRoadFiltering(int filt) const;

	void changeRockFiltering(int filt) const;

	void changeCracksFiltering(int filt) const;

	void changeMixParameter(int value);

private:
	std::shared_ptr<Road> m_road;

	QColor m_backColor = {0, 0, 0};

	GLint m_lightPosUniform = -1;
	GLint m_ambientIntensityUniform = -1;
	GLint m_diffuseIntensityUniform = -1;
	GLint m_ambientColorUniform = -1;
	GLint m_lightColorUniform = -1;
	GLint m_specularIntensityUniform = -1;
	GLint m_viewPosUniform = -1;
	GLint m_mixParameterUniform = -1;
	QOpenGLShaderProgram* m_program = nullptr;

	QVector3D m_lightPos;
	QVector3D m_lightColor;
	QVector3D m_ambientColor;

	QVector3D m_viewPos = {4, 1.5f, -2};

	float m_ambientIntensity{};
	float m_specularIntensity{};
	float m_diffuseIntensity{};
	float m_mixParameter{};
	float m_moveScale = 0.003f;

	void initUniforms();

	void setUniforms() const;

	void setLightPos(QVector3D pos);

	void setLightColor(QColor color);

	void setAmbientColor(QColor color);

public:
	explicit RoadWidget(QWidget* parent);

	virtual void initializeGL() override;

	virtual void paintGL() override;

	virtual void resizeGL(int w, int h) override;

private:
	virtual void wheelEvent(QWheelEvent* event) override;
};
