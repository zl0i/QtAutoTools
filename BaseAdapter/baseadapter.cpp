#include "baseadapter.h"

BaseAdapter::BaseAdapter(SettingsStorage *storage, QObject *parent)
{
    this->setParent(parent);
    settingsStorage = storage;
    toolDetector = new ToolsDetector(this);
    if(!settingsExist()) {
        existSettings = false;
        //toolDetector->detect();
    } else {
        existSettings = toolDetector->checkTools();
    }
    //toolDetector->detect()
}

QJsonObject BaseAdapter::detectTool()
{
    return toolDetector->getDetectTools();
}

bool BaseAdapter::settingsExist()
{
    QJsonObject obj = settingsStorage->getCustomValue("tools").toJsonObject();
    if(obj.isEmpty())
        return false;
    return true;
}

SettingsStorage *BaseAdapter::storage() const
{
    return settingsStorage;
}

void BaseAdapter::executeTask(QJsonObject obj)
{
    if(!existSettings)
        return;

    if(isRunningTask(sender()))
        return;

    QJsonObject main;
    QString nameTask = QString::number(QDateTime::currentMSecsSinceEpoch());
    main.insert("name", nameTask);
    main.insert("version", "1.0");

    QJsonObject settings;
    settings.insert("qtPath", storage()->getQtPath());
    settings.insert("profilePath", storage()->getProfilePath());
    settings.insert("compilerPath", storage()->getCompilerPath());
    obj.insert("settings", settings);
    QJsonArray tasks;
    tasks.append(obj);
    main.insert("tasks", tasks);

    emit signalExecuteTask(main);
}

void BaseAdapter::executeScript(QString name)
{
    if(isRunningTask(sender()))
        return;

    QJsonObject main = scriptStorage.getScriptByName(name);
    emit signalExecuteTask(main);
}

void BaseAdapter::setSettingsQtPath(QString path)
{
    toolDetector->detect(path);
}

