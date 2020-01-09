#ifndef WINDEPLOYQT_H
#define WINDEPLOYQT_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include "worker.h"

class Windeployqt : public QProcess
{
    Q_OBJECT
public:
    explicit Windeployqt(QObject *parent = nullptr);

    Q_INVOKABLE void setExeFile(QString);
    Q_INVOKABLE void setDir(QString);
    Q_INVOKABLE void setPlugindir(QString);
    Q_INVOKABLE void setLibdir(QString);
    Q_INVOKABLE void setQmldir(QString);
    Q_INVOKABLE void setQmlimport(QString);
    Q_INVOKABLE void setFlags(QString);
    Q_INVOKABLE void setLibraries(QString);

    Q_INVOKABLE void deploy();


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

    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);


public slots:
    void slotFinished(int);
    void slotReadChanel();

};



#endif // WINDEPLOYQT_H
