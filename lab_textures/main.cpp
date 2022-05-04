#include <QApplication>
#include "sphere_widget.h"

auto main(int argc, char* argv[]) -> int {
	QApplication a(argc, argv);
	const auto main_window = new QWidget;
	const auto sphere_widget = new SphereWidget(main_window);
	sphere_widget->setMinimumSize(1700, 1080);
	main_window->show();
	sphere_widget->show();
	return QApplication::exec();
}
