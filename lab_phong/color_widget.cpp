#include "color_widget.h"

ColorWidget::ColorWidget() : m_colorDialog(new QColorDialog) {
	setUpColorDialog();
    auto color_layout = std::make_unique<QHBoxLayout>();
    color_layout->addWidget(m_colorDialog);
	this->setLayout(color_layout.release());
    this->setWindowTitle("Color Chose");
}


QColorDialog* ColorWidget::getColorDialog() const {
    return m_colorDialog;
}


void ColorWidget::setUpColorDialog() const {
	QPalette color_dialog_pal;
    color_dialog_pal.setColor(QPalette::Button, QColor(53, 53, 53));
    m_colorDialog->setPalette(color_dialog_pal);
}
