#include "guiadapter.h"

GUIAdapter::GUIAdapter(SettingsStorage *storage, QObject *parent) : BaseAdapter(storage, parent)
{
    engine.addImportPath(":/GUIAdapter/qml");
    engine.rootContext()->setContextProperty("_guiAdapter", this);
    engine.rootContext()->setContextProperty("_toolDetector", ToolsDetector::instanse());

    connect(&translator, &GUITranslator::retranslate, &engine, &QQmlEngine::retranslate);   
    settings = storage->getUserSettings("guiAdapter");
}

void GUIAdapter::start()
{    
    if(!settings.value("lang").toString().isEmpty()) {
        setLanguage(settings.value("lang").toString());
    } else {
        setLanguage(QLocale::system().name());
    }
    engine.load("qrc:/GUIAdapter/main.qml");
}

bool GUIAdapter::isRunningTask(QObject*)
{
    if(taskName.isEmpty())
        return false;
    return  true;
}

QJsonObject GUIAdapter::getUserSettings(QObject *)
{
    return  settings;
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
    settings.insert("lang", lg);
    storage()->saveUserSettings("guiAdapter", settings);
    translator.setLanguage(lg);
}

QJsonObject GUIAdapter::detectToolsByQtPath(QString path)
{
    ToolsDetector::instanse()->detect(path);
    return ToolsDetector::instanse()->getDetectTools();
}

void GUIAdapter::clearAllSettings()
{
    storage()->saveUserSettings("guiAdapter", QJsonObject {});
}
