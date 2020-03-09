#include "baseadapter.h"

BaseAdapter::BaseAdapter(SettingsStorage *storage, QObject *parent)
{
    this->setParent(parent);
    settingsStorage = storage;
}

SettingsStorage *BaseAdapter::storage() const
{
    return settingsStorage;
}

void BaseAdapter::executeTask(QJsonObject obj)
{
    if(isRunningTask(sender()))
        return;

    QJsonObject main;
    QString nameTask = QString::number(QDateTime::currentMSecsSinceEpoch());
    main.insert("name", nameTask);
    main.insert("version", "1.0");

    QJsonArray tasks;
    obj.insert("environment", getUserSettings());
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
