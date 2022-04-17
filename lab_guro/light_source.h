#pragma once

#include "cube.h"

class LightSource final : public Cube {
public:
	explicit LightSource(const GLfloat edgeLen = 1) : Cube(edgeLen, 1) {}

	auto setPos(const QVector3D& pos) -> void { m_pos = pos; }

	[[nodiscard]] auto getPos() const -> QVector3D { return m_pos; }

	auto Switch() -> void { m_isEnabled = !m_isEnabled; }

	[[nodiscard]] auto isEnabled() const -> bool { return m_isEnabled; }

private:
	bool m_isEnabled = true;
	QVector3D m_pos{};
};

