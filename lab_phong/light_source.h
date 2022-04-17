#pragma once

#include "cube.h"

class LightSource final: public Cube{
public:
    explicit LightSource(const GLfloat edgeLen = 1) : Cube(edgeLen, 1) {}

    void setPos(const QVector3D& pos) {
	     m_pos = pos;
    }

    [[nodiscard]] QVector3D getPos() const {
	    return m_pos;
    }

	void Switch() {
		m_isEnabled = !m_isEnabled;
	}

    [[nodiscard]] bool isEnabled() const
    {
	    return m_isEnabled;
    }

private:
    bool m_isEnabled = true;
    QVector3D m_pos{};
};

