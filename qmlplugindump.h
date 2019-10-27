#ifndef QMLPLUGINDUMP_H
#define QMLPLUGINDUMP_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QDebug>
#include "worker.h"

class QmlPluginDump : public QObject
{
    Q_OBJECT
public:
    explicit QmlPluginDump(QObject *parent = nullptr);

    Q_INVOKABLE void setPath(QString);
    Q_INVOKABLE void setWriteQmlDir(bool);
    Q_INVOKABLE void dump();

private:
    QString getModuleName();

    QString path;
    QString version;
    bool wtiteQmldir = false;
    QProcess *process = new QProcess();

signals:
    void finished();
    void error();

public slots:
    void finishedProcess(int, QProcess::ExitStatus);
};

#endif // QMLPLUGINDUMP_H
