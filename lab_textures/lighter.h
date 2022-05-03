#pragma once
#include <QColor>
#include "sphere.h"

struct LightColor {
	QColor ambient, diffuse, specular;
};

class Lighter final : public Sphere {
public:
	Lighter();

	auto setColor(const LightColor& col) -> void;

	[[nodiscard]] auto getPos() const -> QVector3D;

	[[nodiscard]] auto getColor() const -> LightColor;

private:
	QVector3D m_pos{-10.f, 0.5f, 5.f};
	LightColor m_col{{0, 0, 255}, {255, 255, 100}, {255, 255, 255}};
};
