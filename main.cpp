#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QObject>
#include <QQmlContext>
#include "worker.h"
#include "windeployqt.h"
#include "qmldir.h"
#include "lupdate.h"
#include "finstaller.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setOrganizationName("zloi");
    QCoreApplication::setApplicationName("QtAutoTools");   

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icon/icon.png"));


    QQmlApplicationEngine engine;
    QObject::connect(Worker::getInstance(), &Worker::retranslate, &engine, &QQmlEngine::retranslate);

    engine.addImportPath(":/qml");    

    engine.rootContext()->setContextProperty("_worker", Worker::getInstance());

    qmlRegisterType<Worker>("AutoTools", 1, 0, "Worker");
    qmlRegisterType<Windeployqt>("AutoTools", 1, 0, "Windeployqt");
    qmlRegisterType<QmlDir>("AutoTools", 1, 0, "QmlDir");   
    qmlRegisterType<Lupdate>("AutoTools", 1, 0, "Lupdate");
    qmlRegisterType<FInstaller>("AutoTools", 1, 0, "FInstaller");

    engine.load("qrc:/main.qml");       
    Worker::getInstance()->setLanguage();

    return app.exec();
}
