#pragma once
#include <QMatrix4x4>

class Camera {
public:
	[[nodiscard]] auto getViewMatrix() const -> QMatrix4x4 {
		QMatrix4x4 matrix;
		matrix.lookAt(m_pos, m_pos + m_front, m_up);
		return matrix;
	}

	[[nodiscard]] auto getPos() const -> QVector3D { return m_pos; }

	auto setPosZ(const float z) -> void {
		const auto x = m_pos.x();
		const auto y = m_pos.y();
		m_pos = QVector3D{x, y, z};
	}

private:
	QVector3D m_pos{0.f, 0.f, 7.f},
	          m_front{0.f, 0., -1.f},
	          m_up{0.f, 1.f, 0.f};
};
