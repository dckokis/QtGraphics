#pragma once
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QApplication>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QElapsedTimer>
#include <QLabel>
#include <QPainter>
#include "light_source.h"
#include "color_widget.h"
#include "camera.h"


struct AmbientLight
{
	QColor color { 255, 255, 255 };
    bool is_enabled = true;
};


class CubeWidget final : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public slots:
    void setCubeColor(const QColor& color);
    void setGrid(const int value);
    void setNumberOfCubes(int value);

    void moveCamera(const int position);

    void setAmbientCoef(int value);
    void setDiffuseCoef(int value);
    void setSpecularCoef(int value);

    void switchAmbient();
    void switchPointLight();
    void switchDirectedLight();
    void switchProjector();

    void setAmbientColor(const QColor& color);
    void setPointLightColor(const QColor& color);
    void setDirectedLightColor(const QColor& color);
    void setProjectorColor(const QColor& color);

    
    void setPointLightX(double x);
    void setPointLightY(double y);
    void setPointLightZ(double z);

    void setDirectedLightX(double x);
    void setDirectedLightY(double y);
    void setDirectedLightZ(double z);

    void setProjectorLightX(double x);
    void setProjectorLightY(double y);
    void setProjectorLightZ(double z);
    void setProjectorDirX(double x);
    void setProjectorDirY(double y);
    void setProjectorDirZ(double z);


private slots:
	void callColorDialog();

    void closeColorDialog() const;

public:
    [[nodiscard]] QVector3D getPointStartPos() const
    {
	    return m_pointStartPos;
    }

    [[nodiscard]] QVector3D getDirectedStartPos() const
    {
	    return m_directedStartPos;
    }

    [[nodiscard]] QVector3D getProjectorStartPos() const
    {
	    return m_projectorStartPos;
    }

    [[nodiscard]] QVector3D getProjectorDirection() const
    {
	    return m_projectorDirection;
    }
private:
    ColorWidget* m_colorWidget = nullptr;

    LightSource m_directedLight, m_pointLight, m_projectorLight;

    QVector3D m_pointStartPos = { 15.f, 15.f, 1.f },
	m_directedStartPos = { -20.f, 0.f, 1.f },
	m_projectorStartPos = { 0.0f, 0.0f, 20.f },
    m_projectorDirection = QVector3D(0, 0, -1).normalized();

    void initializeGL() override;

    void paintGL() override;

    void initShaders();
    void initLights();
    void initCubes();
    Camera m_camera;

    QOpenGLShaderProgram m_objectProgram, m_lightProgram;

     std::vector<std::unique_ptr<Cube>> m_cubes;
    unsigned m_cubesAmount = 10;

    AmbientLight m_ambientLight;

    QColor m_cubeColor {255, 255, 255};

    float m_cubeEdgeLen = 4.f;

    int m_gridStep = 20;

    GLfloat m_ka = .2f, m_kd = .2f, m_ks = 1.f;

    size_t m_rotationFactor = 0;
    QLabel m_fpsLabel;
    QElapsedTimer m_timer;
    size_t m_frames = 0;
    QString m_fps = "FPS:    ";
};