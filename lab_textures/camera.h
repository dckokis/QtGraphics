#pragma once
#include <QVector3D>
#include <QMatrix4x4>

class Camera {
public:
	auto setPos(const QVector3D& pos) -> void;

	auto setFront(const QVector3D& front) -> void;

	auto setUp(const QVector3D& up) -> void;

	[[nodiscard]] auto getViewMatrix() const -> QMatrix4x4;

	[[nodiscard]] auto getPos() const -> QVector3D;

	[[nodiscard]] auto getFront() const -> QVector3D;

	[[nodiscard]] auto getUp() const -> QVector3D;

private:
	QVector3D m_pos{0.f, 0.f, 0.f},
	          m_front{0.f, 0.f, -1.f},
	          m_up{0.f, 1.f, 0.f};
};
