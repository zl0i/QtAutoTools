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


protected:

    QString currentNameTask;

    SettingsStorage *storage() const;

    void killCurrentTask();
    void killScript(QString);

private:
    ToolsDetector *toolDetector;
    SettingsStorage *settingsStorage;
    ScriptStorage scriptStorage;

signals:

    void signalExecuteTask(QJsonObject);

    void storageChanged();
public slots:

    void executeTask(QJsonObject obj);
    void executeScript(QString);

};

#endif // BASEADAPTER_H
