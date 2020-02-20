#include "baseadapter.h"

BaseAdapter::BaseAdapter(SettingsStorage *storage, QObject *parent)
{
    this->setParent(parent);
    settingsStorage = storage;
    //connect(this, &BaseAdapter::started, this, &BaseAdapter::taskStarted);
    //connect(this, &BaseAdapter::finished, this, &BaseAdapter::taskFinished);
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

