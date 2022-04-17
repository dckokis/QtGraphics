#include "cube_widget.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>


auto main(int argc, char* argv[]) -> int {
	QApplication app(argc, argv);
	const auto cube_widget = new CubeWidget();

	auto* grid_label = new QLabel("Grid");
	auto* morph_label = new QLabel("Morph");

	auto* grid_slider = new QSlider(Qt::Horizontal);
	grid_slider->setRange(1, 10);
	QObject::connect(grid_slider, &QSlider::valueChanged, cube_widget, &CubeWidget::setGrid);

	auto* morph_slider = new QSlider(Qt::Horizontal);
	morph_slider->setRange(0, 10);
	QObject::connect(morph_slider, &QSlider::valueChanged, cube_widget, &CubeWidget::setMorph);

	auto layout = std::make_unique<QGridLayout>();
	layout->addWidget(grid_label, 1, 0);
	layout->addWidget(morph_label, 2, 0);
	layout->addWidget(cube_widget, 0, 1);
	layout->addWidget(grid_slider, 1, 1);
	layout->addWidget(morph_slider, 2, 1);
	auto* main_window = new QWidget;

	QPalette dark_theme_pal;
	dark_theme_pal.setColor(QPalette::Window, QColor(53, 53, 53));

	main_window->setPalette(dark_theme_pal);
	main_window->setFixedSize(800, 600);
	main_window->setLayout(layout.release());
	main_window->setWindowTitle("Cube Morphing Application");
	main_window->show();

	const auto hints = new QWidget;
	auto* hint_label = new QLabel(
		"You can change grid step with Grid slider\nYou can morph cube into sphere with Morph slider\nYou can change cube color with Color button");
	auto hint_layout = std::make_unique<QHBoxLayout>();
	hint_layout->addWidget(hint_label);
	hints->setLayout(hint_layout.release());
	hints->setWindowTitle("Hints");
	hints->setMaximumSize(290, 70);
	hints->move(100, 100);
	hints->show();

	return QApplication::exec();
}
