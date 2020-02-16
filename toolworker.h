#ifndef TOOLWORKER_H
#define TOOLWORKER_H

#include <QObject>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "abstracttool.h"
#include "toolsfabric.h"

class ToolWorker : public QThread
{
    Q_OBJECT

public:
    explicit ToolWorker(QObject *parent = nullptr);
    ~ToolWorker();
    ToolWorker(const ToolWorker &);
    ToolWorker &operator=(const ToolWorker &);

    ToolWorker *setTaskJson(QJsonArray);     

protected:
    void run() override;

private:
    QJsonArray taskArray;


signals:
    void started();
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);
    void finished(int exitCode, int exitStatus);

};
Q_DECLARE_METATYPE(ToolWorker)

#endif // TOOLWORKER_H
