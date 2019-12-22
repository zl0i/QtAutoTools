#ifndef FINSTALLER_H
#define FINSTALLER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QXmlStreamWriter>
#include "worker.h"

class FInstaller : public QProcess
{
    Q_OBJECT
public:
    explicit FInstaller(QObject *parent = nullptr);

    Q_INVOKABLE void setPath(QString);

    Q_INVOKABLE void create(QJsonObject config, QJsonArray packages);

    Q_INVOKABLE void setCreateOfflineInstaller(bool);
    Q_INVOKABLE void setCreateOnlineInstaller(bool);
    Q_INVOKABLE void setCreateRepo(bool);

    void createConfig(QJsonObject);
    void createPackages(QJsonArray);



private:   
    QString path;

    bool isCreateOfflineInstaller = false;
    bool isCreateOnlineInstaller = false;
    bool isCreateRepository = false;

    //void createOffInstaller();

    void copyDir(QString out, QString in);    

    void writeXmlObjectElement(QXmlStreamWriter *stream, QString key, QJsonObject value);

    void writeXmlTextElement(QXmlStreamWriter *stream, QString key, QString value);


    QString packageText = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<Package>\n"
            "     <DisplayName>Installer</DisplayName>\n"
            "    <Description>The main component</Description>\n"
            "    <Version>1.0.0</Version>\n"
            "    <ReleaseDate>2019-01-30</ReleaseDate>\n"
            "        <Default>true</Default>\n"
            "    <Name> </Name>\n"
            "    <ForcedInstallation>true</ForcedInstallation>\n"
            "    <RequiresAdminRights>true</RequiresAdminRights>\n"
            "</Package>\n";


signals:
    void finished();

public slots:
    void slotFinished();
};

#endif // FINSTALLER_H
