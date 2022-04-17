#pragma once
#include <QColorDialog>
#include <QHBoxLayout>

class ColorWidget final : public QWidget {
public:
	ColorWidget();
	[[nodiscard]] QColorDialog* getColorDialog() const;
private:
	QColorDialog* m_colorDialog = nullptr;
	void setUpColorDialog() const;
};

