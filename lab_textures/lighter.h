#pragma once
#include <QColor>
#include "sphere.h"

struct LightColor {
	QColor ambient, diffuse, specular;
};

class Lighter final : public Sphere {
public:
	Lighter();

	[[nodiscard]] auto getPos() const -> QVector3D;

	[[nodiscard]] auto getColor() const -> LightColor;

private:
	QVector3D m_pos{-5.f, 0.5f, 5.f};
	LightColor m_col{{0, 0, 255}, {255, 255, 100}, {255, 255, 255}};
};
