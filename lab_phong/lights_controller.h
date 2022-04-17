#pragma once
#include <QCheckBox>
#include <QDoubleSpinBox>
#include "cube_widget.h"

enum class lights_type {
	POINT = 0,
	DIRECTED = 1,
	PROJECTOR = 2,
	AMBIENT = 3
};

inline auto set_coordinates_selector(QGridLayout* layout, const lights_type lightType,
                                     const CubeWidget* cubeWidget) -> void {

	auto* x_coordinate_selector = new QDoubleSpinBox;
	auto* y_coordinate_selector = new QDoubleSpinBox;
	auto* z_coordinate_selector = new QDoubleSpinBox;
	QVector3D start_position;
	switch (lightType) {
	case lights_type::POINT:
		QObject::connect(x_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget, &CubeWidget::setPointLightX);
		QObject::connect(y_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget, &CubeWidget::setPointLightY);
		QObject::connect(z_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget, &CubeWidget::setPointLightZ);
		start_position = cubeWidget->getPointStartPos();
		break;

	case lights_type::DIRECTED:
		QObject::connect(x_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget,
		                 &CubeWidget::setDirectedLightX);
		QObject::connect(y_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget,
		                 &CubeWidget::setDirectedLightY);
		QObject::connect(z_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget,
		                 &CubeWidget::setDirectedLightZ);
		start_position = cubeWidget->getDirectedStartPos();
		break;

	case lights_type::PROJECTOR:
		QObject::connect(x_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget,
		                 &CubeWidget::setProjectorLightX);
		QObject::connect(y_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget,
		                 &CubeWidget::setProjectorLightY);
		QObject::connect(z_coordinate_selector, &QDoubleSpinBox::valueChanged, cubeWidget,
		                 &CubeWidget::setProjectorLightZ);
		start_position = cubeWidget->getProjectorStartPos();
		break;
	case lights_type::AMBIENT:
	default: break;
	}

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


inline auto set_switch(QCheckBox* switcher, const lights_type light, const CubeWidget* cubeWidget) -> void {
	switcher->setCheckState(Qt::Checked);
	switch (light) {
	case lights_type::POINT:
		switcher->setText("Point Light");
		QObject::connect(switcher, &QCheckBox::stateChanged, cubeWidget, &CubeWidget::switchPointLight);
		break;
	case lights_type::DIRECTED:
		switcher->setText("Directed Light");
		QObject::connect(switcher, &QCheckBox::stateChanged, cubeWidget, &CubeWidget::switchDirectedLight);
		break;
	case lights_type::PROJECTOR:
		switcher->setText("Projector Light");
		QObject::connect(switcher, &QCheckBox::stateChanged, cubeWidget, &CubeWidget::switchProjector);
		break;
	case lights_type::AMBIENT:
		switcher->setText("Ambient Light");
		QObject::connect(switcher, &QCheckBox::stateChanged, cubeWidget, &CubeWidget::switchAmbient);
		break;
	}
}

inline auto set_up_controller(const CubeWidget* cubeWidget, const QPalette& palette) -> QWidget* {
	/*
	 * lights control widget
	 */
	auto* lights_controller = new QWidget;
	/*
	 * colors
	 */
	const auto ambient_color_dialog = new QColorDialog;
	ambient_color_dialog->setWindowTitle("Ambient Color");
	ambient_color_dialog->move(950, 100);
	const auto ambient_color_button = new QPushButton("Ambient Color");
	QObject::connect(ambient_color_button, &QAbstractButton::clicked, ambient_color_dialog, &QColorDialog::show);
	QObject::connect(ambient_color_dialog, &QColorDialog::currentColorChanged, cubeWidget,
	                 &CubeWidget::setAmbientColor);

	const auto directed_color_dialog = new QColorDialog;
	directed_color_dialog->setWindowTitle("Directed Color");
	directed_color_dialog->move(950, 100);
	const auto directed_color_button = new QPushButton("Directed Color");
	QObject::connect(directed_color_button, &QAbstractButton::clicked, directed_color_dialog, &QColorDialog::show);
	QObject::connect(directed_color_dialog, &QColorDialog::currentColorChanged, cubeWidget,
	                 &CubeWidget::setDirectedLightColor);

	const auto point_color_dialog = new QColorDialog;
	point_color_dialog->setWindowTitle("Point Color");
	point_color_dialog->move(950, 100);
	const auto point_color_button = new QPushButton("Point Color");
	QObject::connect(point_color_button, &QAbstractButton::clicked, point_color_dialog, &QColorDialog::show);
	QObject::connect(point_color_dialog, &QColorDialog::currentColorChanged, cubeWidget,
	                 &CubeWidget::setPointLightColor);

	const auto projector_color_dialog = new QColorDialog;
	projector_color_dialog->setWindowTitle("Projector Color");
	projector_color_dialog->move(950, 100);
	const auto projector_color_button = new QPushButton("Projector Color");
	QObject::connect(projector_color_button, &QAbstractButton::clicked, projector_color_dialog, &QColorDialog::show);
	QObject::connect(projector_color_dialog, &QColorDialog::currentColorChanged, cubeWidget,
	                 &CubeWidget::setProjectorColor);
	/*
	 * point light
	 */
	auto* point_controller = new QWidget;
	const auto point_layout = new QGridLayout;
	auto* point_switch = new QCheckBox;
	set_switch(point_switch, lights_type::POINT, cubeWidget);
	set_coordinates_selector(point_layout, lights_type::POINT, cubeWidget);
	point_controller->setLayout(point_layout);
	/*
	 * directed light
	 */
	auto* directed_controller = new QWidget;
	const auto directed_layout = new QGridLayout;
	auto* directed_switch = new QCheckBox;
	set_switch(directed_switch, lights_type::DIRECTED, cubeWidget);
	set_coordinates_selector(directed_layout, lights_type::DIRECTED, cubeWidget);
	directed_controller->setLayout(directed_layout);
	/*
	 * projector light
	 */
	auto* projector_controller = new QWidget;
	const auto projector_layout = new QGridLayout;
	auto* projector_switch = new QCheckBox;
	set_switch(projector_switch, lights_type::PROJECTOR, cubeWidget);
	set_coordinates_selector(projector_layout, lights_type::PROJECTOR, cubeWidget);
	projector_controller->setLayout(projector_layout);
	/*
	 * ambient light
	 */
	auto* ambient_controller = new QWidget;
	auto ambient_layout = std::make_unique<QGridLayout>();
	auto* ambient_switch = new QCheckBox;
	set_switch(ambient_switch, lights_type::AMBIENT, cubeWidget);
	ambient_layout->addWidget(ambient_switch, 0, 0);
	ambient_controller->setLayout(ambient_layout.release());

	auto lights_source_layout = std::make_unique<QGridLayout>();

	lights_source_layout->addWidget(point_switch, 0, static_cast<int>(lights_type::POINT));
	lights_source_layout->addWidget(point_controller, 1, static_cast<int>(lights_type::POINT));
	lights_source_layout->addWidget(point_color_button, 2, static_cast<int>(lights_type::POINT));

	lights_source_layout->addWidget(directed_switch, 0, static_cast<int>(lights_type::DIRECTED));
	lights_source_layout->addWidget(directed_controller, 1, static_cast<int>(lights_type::DIRECTED));
	lights_source_layout->addWidget(directed_color_button, 2, static_cast<int>(lights_type::DIRECTED));

	lights_source_layout->addWidget(projector_switch, 0, static_cast<int>(lights_type::PROJECTOR));
	lights_source_layout->addWidget(projector_controller, 1, static_cast<int>(lights_type::PROJECTOR));
	lights_source_layout->addWidget(projector_color_button, 2, static_cast<int>(lights_type::PROJECTOR));

	lights_source_layout->addWidget(ambient_switch, 0, static_cast<int>(lights_type::AMBIENT));
	lights_source_layout->addWidget(ambient_color_button, 2, static_cast<int>(lights_type::AMBIENT));

	const QIcon settings_icon(R"(C:\ComputerGraphics\lab_phong\settings.ico)");
	lights_controller->setWindowIcon(settings_icon);
	lights_controller->setPalette(palette);
	lights_controller->setWindowTitle("Lights Position Controller");
	lights_controller->setLayout(lights_source_layout.release());
	lights_controller->move(50, 100);
	return lights_controller;
}
