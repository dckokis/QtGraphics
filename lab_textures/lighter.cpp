#include "lighter.h"


Lighter::Lighter() : Sphere(1.f, 20, 20) {}


auto Lighter::setColor(const LightColor& col) -> void { m_col = col; }


auto Lighter::getPos() const -> QVector3D { return m_pos; }


auto Lighter::getColor() const -> LightColor { return m_col; }
