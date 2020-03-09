#ifndef ITOOL_H
#define ITOOL_H

#include <QObject>
#include <QJsonObject>

class ITool : public QObject
{
    Q_OBJECT
public:
    ITool(QObject *parent = nullptr) : QObject(parent) {};

    //virtual void prepareTask() = 0;
    virtual void configFromJson(QJsonObject) = 0;
    virtual void waitFinished() = 0;
    virtual void run() = 0;

signals:
    void started();
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);
    void finished(int exitCode, int exitStatus);

public slots:
    virtual void kill() = 0;

};

#endif // ITOOL_H
