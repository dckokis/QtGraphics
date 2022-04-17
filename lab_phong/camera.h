#pragma once
#include <QMatrix4x4>

class Camera {
	public:
	[[nodiscard]] QMatrix4x4 getViewMatrix() const {
		QMatrix4x4 matrix;
	    matrix.lookAt(m_pos, m_pos + m_front, m_up);
	    return matrix;
	}

	[[nodiscard]] QVector3D getPos() const {
		return m_pos;
	}

	void setPosZ(const float z)
	{
		auto x = m_pos.x();
		auto y = m_pos.y();
		m_pos = QVector3D {x, y, z};
	}

private:
    QVector3D m_pos  { 0.f,  1.5f,  7.f },
              m_front{ 0.f,  -0.5f, -1.3f },
              m_up   { 0.f,  1.f,  0.f };
};

