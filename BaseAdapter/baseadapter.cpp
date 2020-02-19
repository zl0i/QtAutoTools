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

void BaseAdapter::killCurrentTask()
{
    emit kill(currentNameTask);
}

void BaseAdapter::killScript(QString name)
{
    emit kill(name);
}

void BaseAdapter::executeTask(QJsonObject obj)
{
    QJsonObject main;
    currentNameTask = QString::number(QDateTime::currentMSecsSinceEpoch());
    main.insert("name", currentNameTask);
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
    QJsonObject main = scriptStorage.getScriptByName(name);
    emit signalExecuteTask(main);
}
