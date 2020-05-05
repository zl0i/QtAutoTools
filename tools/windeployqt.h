#ifndef WINDEPLOYQT_H
#define WINDEPLOYQT_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QJsonObject>
#include <QEventLoop>
#include "abstracttool.h"

class Windeployqt : public AbstractTool
{
    Q_OBJECT
public:
    explicit Windeployqt(QJsonObject settings,QObject *parent = nullptr);

    void configFromJson(QJsonObject) override;
    bool exec() override;
    void cancelExec() override;

private:

    QString exeFile;
    QString deployDir;
    QString pluginDir;
    QString libDir;
    QString qmlDir;
    QString qmlimport;
    QString flags;
    QString libraries;

};



#endif // WINDEPLOYQT_H
