#ifndef IADAPTER_H
#define IADAPTER_H

#include<QObject>

class IAdapter : public QObject
{
    Q_OBJECT

public:


signals:
    void kill(QString);
    void started();
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);
    void finished(int exitCode, int exitStatus);
};

#endif // IADAPTER_H
