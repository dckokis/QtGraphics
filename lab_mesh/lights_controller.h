#pragma once
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGridLayout>

#include "mesh_widget.h"

enum class LightsType {
	POINT = 0,
	DIRECTED = 1,
	PROJECTOR = 2,
	AMBIENT = 3
};

inline auto set_coordinates_selector(QGridLayout* layout,
                                     const MeshWidget* cubeWidget) -> void {
	auto* x_coordinate_selector = new QDoubleSpinBox;
	auto* y_coordinate_selector = new QDoubleSpinBox;
	auto* z_coordinate_selector = new QDoubleSpinBox;
	QObject::connect(x_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget,
	                 &MeshWidget::setDirectedLightX);
	QObject::connect(y_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget,
	                 &MeshWidget::setDirectedLightY);
	QObject::connect(z_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget,
	                 &MeshWidget::setDirectedLightZ);
	const auto start_position = cubeWidget->getDirectedStartPos();

	x_coordinate_selector->setRange(-20.f, 20.f);
	x_coordinate_selector->setValue(start_position.x());
	x_coordinate_selector->setSingleStep(.5f);

	y_coordinate_selector->setRange(-20.f, 20.f);
	y_coordinate_selector->setValue(start_position.y());
	y_coordinate_selector->setSingleStep(.5f);

	z_coordinate_selector->setRange(-20.f, 20.f);
	z_coordinate_selector->setValue(start_position.z());
	z_coordinate_selector->setSingleStep(.5f);
	auto* x_label = new QLabel("X");
	auto* y_label = new QLabel("Y");
	auto* z_label = new QLabel("Z");
	layout->addWidget(x_label, 0, 0);
	layout->addWidget(x_coordinate_selector, 1, 0);
	layout->addWidget(y_label, 2, 0);
	layout->addWidget(y_coordinate_selector, 3, 0);
	layout->addWidget(z_label, 4, 0);
	layout->addWidget(z_coordinate_selector, 5, 0);
}

inline auto set_switch(QCheckBox* switcher, const MeshWidget* cubeWidget) -> void {
	switcher->setCheckState(Qt::Checked);
	switcher->setText("Directed Light");
	QObject::connect(switcher, &QCheckBox::stateChanged, cubeWidget, &MeshWidget::switchDirectedLight);
}

inline auto set_up_controller(const MeshWidget* cubeWidget, const QPalette& palette) -> QWidget* {
	/*
	 * lights control widget
	 */
	auto* lights_controller = new QWidget;
	/*
	 * directed light
	 */
	auto* directed_controller = new QWidget;
	const auto directed_layout = new QGridLayout;
	auto* directed_switch = new QCheckBox;
	set_switch(directed_switch, cubeWidget);
	set_coordinates_selector(directed_layout, cubeWidget);
	directed_controller->setLayout(directed_layout);

	auto lights_source_layout = std::make_unique<QGridLayout>();

	lights_source_layout->addWidget(directed_switch, 0, static_cast<int>(LightsType::DIRECTED));
	lights_source_layout->addWidget(directed_controller, 1, static_cast<int>(LightsType::DIRECTED));

	const QIcon settings_icon(R"(settings.ico)");
	lights_controller->setWindowIcon(settings_icon);
	lights_controller->setPalette(palette);
	lights_controller->setWindowTitle("Lights Position Controller");
	lights_controller->setLayout(lights_source_layout.release());
	lights_controller->move(50, 100);
	return lights_controller;
}
