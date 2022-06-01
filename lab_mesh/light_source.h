#pragma once

#include "Object.h"

class LightSource final : public Object {
public:
	explicit LightSource() : Object("MeshSphere") {}

	auto setPos(const QVector3D& pos) -> void { m_pos = pos; }

	[[nodiscard]] auto getPos() const -> QVector3D { return m_pos; }

	auto Switch() -> void { m_isEnabled = !m_isEnabled; }

	[[nodiscard]] auto isEnabled() const -> bool { return m_isEnabled; }

private:
	bool m_isEnabled = true;
	QVector3D m_pos{};
};
