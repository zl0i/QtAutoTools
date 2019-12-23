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

    void createConfigAndPackages(QString, QJsonObject, QJsonArray);

    void setPath(QString);

    void createConfig(QJsonObject);
    void createPackages(QJsonArray);

private:

    QString path;

     void writeConfigFile(QFile*, QJsonObject);

    QString createDirPackage(QString path, QString name);
    void writePackageFile(QFile*, QJsonObject);

    void copyDir(QString out, QString in);

    void writeXmlObjectElement(QXmlStreamWriter *stream, QString key, QJsonObject value);
    void writeXmlTextElement(QXmlStreamWriter *stream, QString key, QString value);

signals:

    void finished();
};

#endif // INSTALLERHELPER_H
