#include "baseadapter.h"

BaseAdapter::BaseAdapter(SettingsStorage *storage, QObject *parent)
{
    this->setParent(parent);
    settingsStorage = storage;

}

void BaseAdapter::executeTask(QJsonObject obj)
{
    QJsonObject main;
    main.insert("name", QString::number(QDateTime::currentMSecsSinceEpoch()));
    main.insert("version", "1.0");
    main.insert("task", obj);
    emit signalExecuteTask(main);
}

void BaseAdapter::executeScript(QString name)
{
    QJsonObject main = scriptStorage.getScriptByName(name);
    emit signalExecuteTask(main);
}
