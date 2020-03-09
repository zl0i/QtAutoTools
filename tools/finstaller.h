#ifndef FINSTALLER_H
#define FINSTALLER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QJsonObject>
#include <QJsonArray>
#include "abstracttool.h"
#include "installerhelper.h"

class FInstaller : public AbstractTool
{
    Q_OBJECT
public:
    explicit FInstaller(QJsonObject settings, QObject *parent = nullptr);

    Q_INVOKABLE void setPath(QString);

    Q_INVOKABLE void setCreateMixedInstaller(bool);
    Q_INVOKABLE void setCreateOfflineInstaller(bool);
    Q_INVOKABLE void setCreateOnlineInstaller(bool);
    Q_INVOKABLE void setCreateRepo(bool);

    void configFromJson(QJsonObject) override;
    void run() override;

private:   
    QString path;
    QString installerName;
    QJsonObject config;
    QJsonArray packages;

    InstallerHelper *installerHelper;

    bool isCreateMixedInstaller = false;
    bool isCreateOfflineInstaller = true;
    bool isCreateOnlineInstaller = false;
    bool isCreateRepository = false;


};

#endif // FINSTALLER_H
