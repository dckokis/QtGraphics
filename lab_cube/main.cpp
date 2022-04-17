#include "cubewindow.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    CubeWindow window;
    window.setFormat(format);
    window.resize(720, 560);
    window.show();

    window.setAnimating(true);

    return app.exec();
}
