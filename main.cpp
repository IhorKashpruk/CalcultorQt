#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "history.h"
#include "manager.h"
#include "converter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<History>("calculator.history", 1, 0, "History");
    qmlRegisterType<Manager>("org.calculator", 1, 0, "Calculator");
    qmlRegisterType<Converter>("converter.converter", 1, 0, "Converter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
