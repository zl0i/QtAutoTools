#ifndef TOOLWORKER_H
#define TOOLWORKER_H

#include <QObject>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "itool.h"
#include "toolsfabric.h"

class ToolWorker : public QThread
{
    Q_OBJECT

public:
    explicit ToolWorker(QObject *parent = nullptr);

    ToolWorker(const ToolWorker &);
    ToolWorker &operator=(const ToolWorker &);

    ToolWorker *setTaskJson(QJsonArray);     
    void setTaskName(QString);

    QString getTaskName() { return taskName; }
    QJsonArray getTaskJson() { return taskArray; }

protected:
    void run() override;

    QJsonArray taskArray;
    QString taskName;

private:
    ITool *currentTool;

signals:
    void started(QString);
    void newOutputData(QString, QByteArray line);
    void newErrorData(QString, QByteArray line);
    void finished(QString name, int exitCode, int exitStatus);

public slots:
    virtual void kill();

};
Q_DECLARE_METATYPE(ToolWorker)

#endif // TOOLWORKER_H
