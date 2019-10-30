#ifndef FINSTALLER_H
#define FINSTALLER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QStringList>
#include <QDebug>
#include "worker.h"

class FInstaller : public QObject
{
    Q_OBJECT
public:
    explicit FInstaller(QObject *parent = nullptr);

    Q_INVOKABLE void setDeployPath(QString);
    Q_INVOKABLE void setInstallerPath(QString);
    Q_INVOKABLE void setVendorName(QString);
    Q_INVOKABLE void createConfig();
    Q_INVOKABLE void createPackages();

    Q_INVOKABLE void createOffInstaller();


private:

    QString m_deploypath;
    QString m_installerpath;
    QString m_vendorName = "com.vendor.example";

    QProcess *process = new QProcess();


    void copyDir(QString out, QString in);
    QFile *prepareBatFile();

    QString configText = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                         "<Installer>\n"
                         "    <Name>Installer</Name>\n"
                         "    <Version>1.0.0</Version>\n"
                         "    <Title>1.0.0 Installer</Title>\n"
                         "    <Publisher>Installer</Publisher>\n"
                         "    <StartMenuDir>Installer</StartMenuDir>\n"
                         "    <TargetDir>@RootDir@Program Files (x86)\Installer</TargetDir>\n"
                         "        <AllowSpaceInPath>true</AllowSpaceInPath>\n"
                         "</Installer>\n";

    QString packageText = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<Package>\n"
            "     <DisplayName>Installer</DisplayName>\n"
            "    <Description>The main component</Description>\n"
            "    <Version>1.0.0</Version>\n"
            "    <ReleaseDate>2019-01-30</ReleaseDate>\n"
            "        <Default>true</Default>\n"
            "    <Name>" + m_vendorName + "</Name>\n"
            "    <ForcedInstallation>true</ForcedInstallation>\n"
            "    <RequiresAdminRights>true</RequiresAdminRights>\n"
            "</Package>\n";





signals:
    void finished();

public slots:
    void slotFinished();
};

#endif // FINSTALLER_H
