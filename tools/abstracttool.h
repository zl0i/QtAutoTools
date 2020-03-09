#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QDateTime>
#include <QRandomGenerator>
#include "itool.h"
#include "toolspathfabric.h"

class AbstractTool : public ITool
{
    Q_OBJECT

public:
    AbstractTool(QJsonObject obj, QObject *parent = nullptr);
    AbstractTool(QObject *parent = nullptr);

    virtual void configFromJson(QJsonObject) = 0;
    void waitFinished();
    virtual void run() = 0;


protected:
    QProcess *process;

    virtual void successFinished();
    virtual void failFinished();

    QFile *prepareBatFile(bool env = true);
    void removeBatFile();

    ToolsPathFabric pathFabric;

private:
    QString currentFileName;

signals:
    void started();
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);
    void finished(int exitCode, int exitStatus);

public slots:
    virtual void slotFinished(int);
    void errorOcured(QProcess::ProcessError error);
    void slotReadChanel();
    void kill();
};

#endif // ABSTRACTTOOL_H
