#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "worker.h"
#include "windeployqt.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setOrganizationName("zloi");
    QCoreApplication::setApplicationName("QtAutoTools");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Worker>("AutoTools", 1, 0, "Worker");
    qmlRegisterType<Windeployqt>("AutoTools", 1, 0, "Windeployqt");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
