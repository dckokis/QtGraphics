#pragma once
#include <QColorDialog>
#include <QHBoxLayout>

class ColorWidget final : public QWidget {
public:
	ColorWidget();

	[[nodiscard]] auto getColorDialog() const -> QColorDialog*;

private:
	QColorDialog* m_colorDialog = nullptr;

	auto setUpColorDialog() const -> void;
};

