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

    virtual bool start() = 0;

protected:

    explicit BaseAdapter(SettingsStorage *storage, QObject *parent = nullptr);

    virtual bool isRunningTask(QObject* sender = nullptr) = 0;
    virtual QJsonObject getUserSettings(QObject* sender = nullptr) = 0;

    ScriptStorage scriptStorage;
    SettingsStorage *storage() const;

private:
    SettingsStorage *settingsStorage;

signals:
    void signalExecuteTask(QJsonObject);
    void killTask(QString);

public slots:
    void executeTask(QJsonObject obj);
    void executeScript(QString);

    virtual void kill() = 0;

};

#endif // BASEADAPTER_H
