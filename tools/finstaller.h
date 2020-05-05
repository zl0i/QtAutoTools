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

    void configFromJson(QJsonObject) override;
    bool exec() override;
    void cancelExec() override;

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
