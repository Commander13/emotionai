//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "interfacehandler.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    InterfaceHandler *interfaceHandler = InterfaceHandler::Instance();
    //Expose objects to qml
    //Load Application
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("interfaceHandler", interfaceHandler);


    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}
