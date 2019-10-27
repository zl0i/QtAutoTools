#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "worker.h"
#include "windeployqt.h"
#include "qmldir.h"
#include "qmlplugindump.h"
#include "lupdate.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setOrganizationName("zloi");
    QCoreApplication::setApplicationName("QtAutoTools");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icon/icon.png"));

    QQmlApplicationEngine engine;
    engine.addImportPath(":/qml");

    qmlRegisterType<Worker>("AutoTools", 1, 0, "Worker");
    qmlRegisterType<Windeployqt>("AutoTools", 1, 0, "Windeployqt");
    qmlRegisterType<QmlDir>("AutoTools", 1, 0, "QmlDir");
    qmlRegisterType<QmlPluginDump>("AutoTools", 1, 0, "QmlPluginDump");
    qmlRegisterType<Lupdate>("AutoTools", 1, 0, "Lupdate");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
