#include "lights_controller.h"
#include <QPushButton>
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>

auto main(int argc, char* argv[]) -> int {
	QApplication app(argc, argv);
	const auto mesh_widget = new MeshWidget();
	QPalette dark_theme_pal;
	dark_theme_pal.setColor(QPalette::Window, QColor(53, 53, 53));
	dark_theme_pal.setColor(QPalette::WindowText, QColor(203, 203, 203));
	const auto lights_controller = set_up_controller(mesh_widget, dark_theme_pal);
	/*
	 * labels
	 */
	const auto camera_label = new QLabel("Camera");
	const auto ka_label = new QLabel("Ambient");
	const auto kd_label = new QLabel("Diffusion");
	const auto ks_label = new QLabel("Specular");
	/*
	 * light coefficients sliders
	 */
	const auto ka_slider = new QSlider(Qt::Horizontal);
	const auto kd_slider = new QSlider(Qt::Horizontal);
	const auto ks_slider = new QSlider(Qt::Horizontal);

	ka_slider->setRange(1, 20);
	kd_slider->setRange(1, 20);
	ks_slider->setRange(1, 40);
	ka_slider->setSliderPosition(4);
	kd_slider->setSliderPosition(4);
	ks_slider->setSliderPosition(20);

	QObject::connect(ka_slider, &QSlider::valueChanged, mesh_widget, &MeshWidget::setAmbientCoef);
	QObject::connect(kd_slider, &QSlider::valueChanged, mesh_widget, &MeshWidget::setDiffuseCoef);
	QObject::connect(ks_slider, &QSlider::valueChanged, mesh_widget, &MeshWidget::setSpecularCoef);
	/*
	 * camera slider
	 */
	const auto camera_slider = new QSlider(Qt::Vertical);
	camera_slider->setRange(1, 100);
	camera_slider->setSliderPosition(7);
	QObject::connect(camera_slider, &QSlider::valueChanged, mesh_widget, &MeshWidget::moveCamera);
	/*
	 * settings button
	 */
	auto* settings_button = new QPushButton("Lights Settings");
	QObject::connect(settings_button, &QAbstractButton::clicked, lights_controller, &QWidget::show);
	/*
	 * layout
	 */
	auto layout = std::make_unique<QGridLayout>();

	layout->addWidget(settings_button, 2, 2);
	layout->addWidget(mesh_widget, 0, 1);

	layout->addWidget(ka_slider, 2, 1);
	layout->addWidget(kd_slider, 3, 1);
	layout->addWidget(ks_slider, 4, 1);
	layout->addWidget(camera_slider, 0, 2);

	layout->addWidget(camera_label, 1, 2);
	layout->addWidget(ka_label, 2, 0);
	layout->addWidget(kd_label, 3, 0);
	layout->addWidget(ks_label, 4, 0);
	const auto main_window = new QWidget;

	const QIcon icon(R"(cube.ico)");
	main_window->setWindowIcon(icon);
	main_window->setPalette(dark_theme_pal);
	main_window->setFixedSize(800, 600);
	main_window->setWindowTitle("Mesh Application");
	main_window->setWindowFlag(Qt::FramelessWindowHint);

	const auto close_button = new QPushButton();
	const QIcon close_icon(R"(close.ico)");
	close_button->setIcon(close_icon);
	QObject::connect(close_button, &QAbstractButton::clicked, lights_controller, &QWidget::close);
	QObject::connect(close_button, &QAbstractButton::clicked, main_window, &QWidget::close);
	layout->addWidget(close_button, 4, 2);
	main_window->setLayout(layout.release());
	main_window->show();

	return QApplication::exec();
}
