#ifndef IADAPTER_H
#define IADAPTER_H

#include<QObject>

class IAdapter : public QObject
{
    Q_OBJECT

public:
    IAdapter() {}

public slots:
    virtual void started(QString name) = 0;
    virtual void newOutputData(QString name, QByteArray line) = 0;
    virtual void newErrorData(QString name, QByteArray line) = 0;
    virtual void finished(QString name, int exitCode, int exitStatus) = 0;
};

#endif // IADAPTER_H
