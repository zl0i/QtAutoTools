#include <QGuiApplication>
#include <QIcon>
#include <QObject>
#include "taskmanager.h"
#include "GUIAdapter/guiadapter.h"
#include "ConsoleAdapter/consoleadapter.h"
#include "WebAdapter/webadapter.h"
#include "Storage/qsettingsstorage.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setOrganizationName("zloi");
    QCoreApplication::setApplicationName("QtAutoTools");
    qRegisterMetaType<ToolWorker>();

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icon/icon.png"));

    TaskManager manager;

    QSettingsStorage *storage = new QSettingsStorage();
    //storage->clearAllSettings();
    ToolsDetector::instanse()->setSettingsStorage(storage);
    ToolsDetector::instanse()->detect();
    qDebug() << ToolsDetector::instanse()->getDetectTools();

    GUIAdapter guiAdapter(storage);
    guiAdapter.start();
    QObject::connect(&guiAdapter, &GUIAdapter::signalExecuteTask, &manager, &TaskManager::executeTask);
    QObject::connect(&guiAdapter, &GUIAdapter::killTask, &manager, &TaskManager::killTask);

    /*ConsoleAdapter consoleAdapter(storage);
    consoleAdapter.start();
    QObject::connect(&consoleAdapter, &ConsoleAdapter::signalExecuteTask, &manager, &TaskManager::executeTask);

    WebAdapter webAdapter(storage);
    webAdapter.start();
    QObject::connect(&webAdapter, &WebAdapter::signalExecuteTask, &manager, &TaskManager::executeTask);*/

    return app.exec();
}
