#ifndef FINSTALLER_H
#define FINSTALLER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QThread>
#include "installerhelper.h"
#include "worker.h"

class FInstaller : public QObject
{
    Q_OBJECT
public:
    explicit FInstaller(QObject *parent = nullptr);

    Q_INVOKABLE void setPath(QString);

    Q_INVOKABLE void create(QJsonObject config, QJsonArray packages);

    Q_INVOKABLE void setCreateOfflineInstaller(bool);
    Q_INVOKABLE void setCreateOnlineInstaller(bool);
    Q_INVOKABLE void setCreateRepo(bool);


private:   
    QProcess *process;

    QString path;
    QString installerName;

    QThread *thread;
    InstallerHelper *installerHelper;

    bool isCreateOfflineInstaller = false;
    bool isCreateOnlineInstaller = false;
    bool isCreateRepository = false;


signals:
    void started();
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);
    void finished();

private slots:
    void createInstallers();

public slots:
    void slotFinished(int);
    void slotReadChanel();
};

#endif // FINSTALLER_H
