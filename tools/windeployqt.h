#ifndef WINDEPLOYQT_H
#define WINDEPLOYQT_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QJsonObject>
#include "abstracttool.h"

class Windeployqt : public AbstractTool
{
    Q_OBJECT
public:
    explicit Windeployqt(QJsonObject settings,QObject *parent = nullptr);

    Q_INVOKABLE void setExeFile(QString);
    Q_INVOKABLE void setDir(QString);
    Q_INVOKABLE void setPlugindir(QString);
    Q_INVOKABLE void setLibdir(QString);
    Q_INVOKABLE void setQmldir(QString);
    Q_INVOKABLE void setQmlimport(QString);
    Q_INVOKABLE void setFlags(QString);
    Q_INVOKABLE void setLibraries(QString);

    void configFromJson(QJsonObject) override;
    void run() override;

protected:
    void successFinished() override;


private:

    QString exeFile;
    QString dir;
    QString plugindir;
    QString libdir;
    QString qmldir;
    QString qmlimport;
    QString flags;
    QString libraries;

signals:  




public slots:



};



#endif // WINDEPLOYQT_H
