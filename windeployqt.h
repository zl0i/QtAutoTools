#ifndef WINDEPLOYQT_H
#define WINDEPLOYQT_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include "worker.h"

class Windeployqt : public QObject
{
    Q_OBJECT
public:
    explicit Windeployqt(QObject *parent = nullptr);

    Q_INVOKABLE void setDir(QString);
    Q_INVOKABLE void setPlugindir(QString);
    Q_INVOKABLE void setLibdir(QString);
    Q_INVOKABLE void setQmldir(QString);
    Q_INVOKABLE void setQmlimport(QString);
    Q_INVOKABLE void setFlags(QString);

    Q_INVOKABLE void deploy(QString);

private:
    QProcess *process;


    QString dir;
    QString plugindir;
    QString libdir;
    QString qmldir;
    QString qmlimport;
    QString flags;

    Worker *worker;

    QFile *prepareBatFile();

signals:
    void finished();

public slots:
    void slotFinished();

};



#endif // WINDEPLOYQT_H
