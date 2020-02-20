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
    Q_PROPERTY(SettingsStorage *storage READ storage NOTIFY storageChanged)

public:
    explicit BaseAdapter(SettingsStorage *storage, QObject *parent = nullptr);

    virtual void start() = 0;


protected:

    virtual bool isRunningTask(QObject* sender = nullptr) = 0;


    SettingsStorage *storage() const;

private:
    ToolsDetector *toolDetector;
    SettingsStorage *settingsStorage;
    ScriptStorage scriptStorage;

signals:
    void signalExecuteTask(QJsonObject);
    void killTask(QString);
    void storageChanged();

public slots:
    void executeTask(QJsonObject obj);
    void executeScript(QString);

    virtual void kill() = 0;
};

#endif // BASEADAPTER_H
