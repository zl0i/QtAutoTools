#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

#include <QObject>
#include <QProcess>
#include "worker.h"

class AbstractTool : public QObject
{
    Q_OBJECT

public:
    AbstractTool(QJsonObject obj, QObject *parent = nullptr);
    AbstractTool(QObject *parent = nullptr);

    virtual void configFromJson(QJsonObject) = 0;
    virtual void run() = 0;

    Q_INVOKABLE void kill();

protected:
    QProcess *process;

    QFile* prepareBatFile(bool);    

signals:
    void started();
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);
    void finished(int exitCode, int exitStatus);

public slots:
    virtual void slotFinished(int);
    void slotReadChanel();
};

#endif // ABSTRACTTOOL_H
