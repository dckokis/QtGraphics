#include "lights_controller.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>

auto main(int argc, char* argv[]) -> int {
	QApplication app(argc, argv);
	const auto cube_widget = new CubeWidget();
	QPalette dark_theme_pal;
	dark_theme_pal.setColor(QPalette::Window, QColor(53, 53, 53));
	dark_theme_pal.setColor(QPalette::WindowText, QColor(203, 203, 203));
	const auto lights_controller = set_up_controller(cube_widget, dark_theme_pal);
	/*
	 * labels
	 */
	auto* grid_label = new QLabel("Grid");
	auto* amount_label = new QLabel("Cubes Amount");
	auto* camera_label = new QLabel("Camera");
	auto* ka_label = new QLabel("Ambient");
	auto* kd_label = new QLabel("Diffusion");
	auto* ks_label = new QLabel("Specular");
	/*
	 * light coefficients sliders
	 */
	auto* ka_slider = new QSlider(Qt::Horizontal);
	auto* kd_slider = new QSlider(Qt::Horizontal);
	auto* ks_slider = new QSlider(Qt::Horizontal);

	ka_slider->setRange(1, 20);
	kd_slider->setRange(1, 20);
	ks_slider->setRange(1, 40);
	ka_slider->setSliderPosition(4);
	kd_slider->setSliderPosition(4);
	ks_slider->setSliderPosition(20);

	QObject::connect(ka_slider, &QSlider::valueChanged, cube_widget, &CubeWidget::setAmbientCoef);
	QObject::connect(kd_slider, &QSlider::valueChanged, cube_widget, &CubeWidget::setDiffuseCoef);
	QObject::connect(ks_slider, &QSlider::valueChanged, cube_widget, &CubeWidget::setSpecularCoef);
	/*
	 * grid slider
	 */
	auto* grid_slider = new QSlider(Qt::Vertical);
	grid_slider->setRange(1, 100);
	grid_slider->setSliderPosition(20);
	QObject::connect(grid_slider, &QSlider::valueChanged, cube_widget, &CubeWidget::setGrid);
	/*
	 * camera slider
	 */
	auto* camera_slider = new QSlider(Qt::Vertical);
	camera_slider->setRange(1, 100);
	camera_slider->setSliderPosition(7);
	QObject::connect(camera_slider, &QSlider::valueChanged, cube_widget, &CubeWidget::moveCamera);
	/*
	 * settings button
	 */
	auto* settings_button = new QPushButton("Lights Settings");
	QObject::connect(settings_button, &QAbstractButton::clicked, lights_controller, &QWidget::show);
	/*
	 * layout
	 */
	auto* amount_slider = new QSlider(Qt::Horizontal);
	amount_slider->setRange(1, 1000);
	amount_slider->setSliderPosition(10);
	QObject::connect(amount_slider, &QSlider::valueChanged, cube_widget, &CubeWidget::setNumberOfCubes);
	auto layout = std::make_unique<QGridLayout>();

	layout->addWidget(settings_button, 2, 2);
	layout->addWidget(amount_slider, 5, 1);
	layout->addWidget(amount_label, 5, 0);
	layout->addWidget(cube_widget, 0, 1);

	layout->addWidget(grid_slider, 0, 3);
	layout->addWidget(ka_slider, 2, 1);
	layout->addWidget(kd_slider, 3, 1);
	layout->addWidget(ks_slider, 4, 1);
	layout->addWidget(camera_slider, 0, 2);

	layout->addWidget(grid_label, 1, 3);
	layout->addWidget(camera_label, 1, 2);
	layout->addWidget(ka_label, 2, 0);
	layout->addWidget(kd_label, 3, 0);
	layout->addWidget(ks_label, 4, 0);
	auto* main_window = new QWidget;

	const QIcon icon(R"(C:\ComputerGraphics\lab_phong\cube.ico)");
	main_window->setWindowIcon(icon);
	main_window->setPalette(dark_theme_pal);
	main_window->setFixedSize(800, 600);
	main_window->setWindowTitle("Phong Application");
	main_window->setWindowFlag(Qt::FramelessWindowHint);

	auto* close_button = new QPushButton();
	const QIcon close_icon(R"(C:\ComputerGraphics\lab_phong\close.ico)");
	close_button->setIcon(close_icon);
	QObject::connect(close_button, &QAbstractButton::clicked, lights_controller, &QWidget::close);
	QObject::connect(close_button, &QAbstractButton::clicked, main_window, &QWidget::close);
	layout->addWidget(close_button, 3, 2);
	main_window->setLayout(layout.release());
	main_window->show();

	return QApplication::exec();
}
