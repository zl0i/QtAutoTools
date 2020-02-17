#include <QGuiApplication>
#include <QIcon>
#include <QObject>
#include "taskmanager.h"
#include "GUIAdapter/guiadapter.h"
#include "Storage/qsettingsstorage.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setOrganizationName("zloi");
    QCoreApplication::setApplicationName("QtAutoTools");
    //qRegisterMetaType<ToolWorker>();

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icon/icon.png"));

    TaskManager manager;

    QSettingsStorage *storage = new QSettingsStorage();
    GUIAdapter adapter(storage);
    adapter.start();

    QObject::connect(&adapter, &GUIAdapter::signalExecuteTask, &manager, &TaskManager::executeTask);


    return app.exec();
}
