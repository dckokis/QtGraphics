#include "camera.h"

auto Camera::setPos(const QVector3D& pos) -> void { m_pos = pos; }

auto Camera::setFront(const QVector3D& front) -> void { m_front = front; }

auto Camera::setUp(const QVector3D& up) -> void { m_up = up; }

auto Camera::getViewMatrix() const -> QMatrix4x4 {
	QMatrix4x4 matrix;
	matrix.lookAt(m_pos, m_pos + m_front, m_up);
	return matrix;
}

auto Camera::getPos() const -> QVector3D { return m_pos; }

auto Camera::getFront() const -> QVector3D { return m_front; }

auto Camera::getUp() const -> QVector3D { return m_up; }
