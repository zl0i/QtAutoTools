#ifndef CONSOLEADAPTER_H
#define CONSOLEADAPTER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include "BaseAdapter/baseadapter.h"

class ConsoleAdapter : public BaseAdapter
{
    Q_OBJECT
public:
    explicit ConsoleAdapter(QString file, SettingsStorage *storage, QObject *parent = nullptr);

    bool start() override;

    void displayScripts();

protected:
    QJsonObject getUserSettings(QObject *sender = nullptr) override;
    bool isRunningTask(QObject *sender = nullptr) override;

    QJsonObject script;

signals:
    void scriptFinished(int);

public slots:
    void started(QString name) override;
    void newErrorData(QString name, QByteArray line) override;
    void newOutputData(QString name, QByteArray line) override;
    void finished(QString name, int exitCode, int exitStatus) override;

    void kill() override;

};

#endif // CONSOLEADAPTER_H
