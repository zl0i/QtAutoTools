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
    ~ToolWorker() override;
    ToolWorker(const ToolWorker &);
    ToolWorker &operator=(const ToolWorker &);

    ToolWorker *setTaskJson(QJsonArray);     
    void setTaskName(QString);


protected:
    void run() override;

private:
    QJsonArray taskArray;
    ITool *currentTool;

    QString taskName;


signals:
    void started(QString);
    void newOutputData(QString, QByteArray line);
    void newErrorData(QString, QByteArray line);
    void finished(QString name, int exitCode, int exitStatus);

public slots:
    void kill();

};
Q_DECLARE_METATYPE(ToolWorker)

#endif // TOOLWORKER_H
