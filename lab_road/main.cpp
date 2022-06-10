#include "RoadWidget.h"

#include <QApplication>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QGridLayout>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	auto main_window = new QWidget;
	auto road_widget = new RoadWidget(main_window);
	const auto mix_slider = new QSlider(Qt::Horizontal);
	mix_slider->setTickInterval(1);
	mix_slider->setRange(0, 100);
	QObject::connect(mix_slider, &QSlider::valueChanged, road_widget, &RoadWidget::changeMixParameter);
	auto* road_filter_selector = new QDoubleSpinBox;
	auto* rock_filter_selector = new QDoubleSpinBox;
	auto* crack_filter_selector = new QDoubleSpinBox;
	road_filter_selector->setRange(0, 2);
	rock_filter_selector->setRange(0, 2);
	crack_filter_selector->setRange(0, 2);
	QObject::connect(road_filter_selector, &QDoubleSpinBox::valueChanged, road_widget, &RoadWidget::changeRoadFiltering);
	QObject::connect(rock_filter_selector, &QDoubleSpinBox::valueChanged, road_widget, &RoadWidget::changeRockFiltering);
	QObject::connect(crack_filter_selector, &QDoubleSpinBox::valueChanged, road_widget, &RoadWidget::changeCracksFiltering);
	auto layout = std::make_unique<QGridLayout>();
	layout->addWidget(rock_filter_selector, 0, 0);
	layout->addWidget(road_filter_selector, 0, 1);
	layout->addWidget(crack_filter_selector, 0, 2);
	layout->addWidget(mix_slider, 1, 0);
	auto settings_window = new QWidget;
	road_widget->setMinimumSize(800, 800);
	road_widget->show();
	settings_window->setLayout(layout.release());
	settings_window->show();
	main_window->show();
	return QApplication::exec();
}
