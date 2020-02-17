#ifndef BASEADAPTER_H
#define BASEADAPTER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include "IAdapter.h"
#include "scriptstorage.h"
#include "settingsstorage.h"
#include "toolsdetector.h"

class BaseAdapter : public IAdapter
{
    Q_OBJECT

public:
    explicit BaseAdapter(SettingsStorage *storage, QObject *parent = nullptr);


protected:
    ScriptStorage scriptStorage;
    SettingsStorage *settingsStorage;
    ToolsDetector *toolDetector;

signals:
    void signalExecuteTask(QJsonObject);

public slots:
    void executeTask(QJsonObject obj);
    void executeScript(QString);

};

#endif // BASEADAPTER_H
