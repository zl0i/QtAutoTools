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

    TaskManager manager;

    QSettingsStorage *storage = new QSettingsStorage();
    ToolsDetector::instanse()->setSettingsStorage(storage);
    ToolsDetector::instanse()->detect();


    //if(argc == 1) {
        QGuiApplication app(argc, argv);
        app.setWindowIcon(QIcon(":/icon/icon.png"));

        GUIAdapter *guiAdapter = new GUIAdapter(storage);
        QObject::connect(guiAdapter, &GUIAdapter::signalExecuteTask, &manager, &TaskManager::executeTask);
        QObject::connect(guiAdapter, &GUIAdapter::killTask, &manager, &TaskManager::killTask);
        guiAdapter->start();

        return app.exec();
    /*} else {
        QCoreApplication app(argc, argv);

        QStringList agr = app.arguments();
        qDebug() << agr;

        if(agr.at(1) == "-web") {
            qDebug() << "Start Server";
            WebAdapter webAdapter(storage);

            QObject::connect(&webAdapter, &WebAdapter::signalExecuteTask, &manager, &TaskManager::executeTask);
            webAdapter.start();
            return app.exec();
        } else {

            if(agr.at(1) == "-scripts") {
                ConsoleAdapter consoleAdapter(argv[1], storage);
                consoleAdapter.displayScripts();
                return 0;
            }
            if(agr.at(1) == "-help" || agr.at(1) == "-h") {
                ConsoleAdapter consoleAdapter(argv[1], storage);
                qDebug() << "show help";
                //consoleAdapter.displayHelp();
                return 0;
            }
            ConsoleAdapter *consoleAdapter = new ConsoleAdapter(argv[1], storage);

            QObject::connect(consoleAdapter, &ConsoleAdapter::signalExecuteTask, &manager, &TaskManager::executeTask);
            QObject::connect(consoleAdapter, &ConsoleAdapter::scriptFinished, &app, &QCoreApplication::quit);
            if(consoleAdapter->start())
                return app.exec();
            else
                return 1;
        }
    }*/
    //return 0;
}
