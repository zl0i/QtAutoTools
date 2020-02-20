#include "guiadapter.h"

GUIAdapter::GUIAdapter(SettingsStorage *storage, QObject *parent) : BaseAdapter(storage, parent)
{
    engine.addImportPath(":/GUIAdapter/qml");
    engine.rootContext()->setContextProperty("_guiAdapter", this);

    connect(&translator, &GUITranslator::retranslate, &engine, &QQmlEngine::retranslate);
    //qDebug() << QLocale::system().name();
}

void GUIAdapter::start()
{
    QString lg = storage()->getCustomValue("language").toString();
    translator.setLanguage(lg);
    engine.load("qrc:/GUIAdapter/main.qml");
}

bool GUIAdapter::isRunningTask(QObject*)
{
    if(taskName.isEmpty())
        return false;
    return  true;
}

void GUIAdapter::started(QString name)
{
    taskName = name;
    emit startedTask();
}

void GUIAdapter::newErrorData(QString, QByteArray line)
{
    emit newErrorDataTask(line);
}

void GUIAdapter::newOutputData(QString, QByteArray line)
{
    emit newOutputDataTask(line);
}

void GUIAdapter::finished(QString, int exitCode, int exitStatus)
{
    taskName = "";
    emit finishedTask(exitCode, exitStatus);
}

void GUIAdapter::kill()
{
    emit killTask(taskName);
}

void GUIAdapter::setLanguage(QString lg)
{
    storage()->setCustomValue("language", lg);
    translator.setLanguage(lg);
}
