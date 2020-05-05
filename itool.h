#ifndef ITOOL_H
#define ITOOL_H

#include <QObject>
#include <QJsonObject>

class ITool : public QObject
{
    Q_OBJECT
public:
    ITool(QObject *parent = nullptr) : QObject(parent) {};

    virtual void configFromJson(QJsonObject) = 0;
    virtual bool exec() = 0;
    virtual void cancelExec() = 0;

signals:
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);

public slots:
    virtual void kill() = 0;

};

#endif // ITOOL_H
