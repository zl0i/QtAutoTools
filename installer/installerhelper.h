#ifndef INSTALLERHELPER_H
#define INSTALLERHELPER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QXmlStreamWriter>
#include <QDebug>

class InstallerHelper : public QObject
{
    Q_OBJECT
public:
    explicit InstallerHelper(QObject *parent = nullptr);


    void setPath(QString);
    void setConfig(QJsonObject);
    void setPackages(QJsonArray);

private:

    QString path;
    QJsonObject config;
    QJsonArray packages;

    void createConfig(QJsonObject);
    void writeConfigFile(QFile*, QJsonObject);

    void createPackages(QJsonArray);
    QString createDirPackage(QString path, QString name);
    void writePackageFile(QFile*, QJsonObject);

    void copyDir(QString out, QString in);

    void writeXmlObjectElement(QXmlStreamWriter *stream, QString key, QJsonObject value);
    void writeXmlTextElement(QXmlStreamWriter *stream, QString key, QString value);

public slots:
    void run();

signals:

    void finished();
};

#endif // INSTALLERHELPER_H
