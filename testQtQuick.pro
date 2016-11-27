TEMPLATE = app

QT += qml quick widgets

CONFIG += c++14

SOURCES += main.cpp \
    history.cpp \
    manager.cpp \
    calculator.cpp \
    exception.cpp \
    number.cpp \
    expression.cpp \
    validator.cpp \
    operation.cpp \
    symbol.cpp \
    converter.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    history.h \
    manager.h \
    calculator.h \
    validator.h \
    exception.h \
    expression.h \
    operation.h \
    number.h \
    symbol.h \
    converter.h

DISTFILES +=
