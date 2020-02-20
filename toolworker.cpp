#include "toolworker.h"

ToolWorker::ToolWorker(QObject *parent) : QThread(parent)
{

}

ToolWorker::ToolWorker(const ToolWorker &worker) : QThread(worker.parent()), taskArray(worker.taskArray), taskName(worker.taskName)
{

}

ToolWorker &ToolWorker::operator=(const ToolWorker &worker)
{
    taskArray = worker.taskArray;
    return *this;
}

ToolWorker *ToolWorker::setTaskJson(QJsonArray arr)
{
    taskArray = arr;
    return this;
}

void ToolWorker::setTaskName(QString name)
{
    taskName = name;
}

ToolWorker::~ToolWorker()
{

}

void ToolWorker::run()
{
    emit started(taskName);
    for(int i = 0; i < taskArray.size(); ++i) {
        QJsonObject task = taskArray.at(i).toObject();
        currentTool = ToolsFabric::createTool(task.value("tool").toString(), task.value("settings").toObject());
        connect(currentTool, &AbstractTool::newOutputData, [=] (QByteArray line) {
            emit newOutputData(taskName, line);
        });
        connect(currentTool, &AbstractTool::newErrorData,  [=] (QByteArray line) {
            emit newErrorData(taskName, line);
        });
        currentTool->configFromJson(task);
        currentTool->run();
        currentTool->waitFinished();
        currentTool->deleteLater();
    }
    emit finished(taskName, 0, 0);
}

void ToolWorker::kill()
{
    currentTool->kill();
    currentTool->deleteLater();
    exit(1);
}
