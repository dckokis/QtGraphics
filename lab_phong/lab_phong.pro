QT += core
QT += gui
QT += openglwidgets
QT += opengl
LIBS += -lopengl32
CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        color_widget.cpp \
        cube.cpp \
        cube_widget.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    close.ico \
    cube.ico \
    hint.ico \
    settings.ico

HEADERS += \
    camera.h \
    color_widget.h \
    cube.h \
    cube_widget.h \
    light_source.h \
    lights_controller.h \
    object.h
