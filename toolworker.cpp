#include "toolworker.h"

ToolWorker::ToolWorker(QObject *) : QThread()
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

void ToolWorker::run()
{
    emit started(taskName);
    for(int i = 0; i < taskArray.size(); ++i) {
        QJsonObject task = taskArray.at(i).toObject();
        currentTool = ToolsFabric::createTool(task.value("tool").toString(), task);
        QObject::connect(currentTool, &ITool::newOutputData, [=] (QByteArray line) {
            emit newOutputData(taskName, line);
        });
        QObject::connect(currentTool, &ITool::newErrorData,  [=] (QByteArray line) {
            emit newErrorData(taskName, line);
        });
        currentTool->configFromJson(task);
        if(!currentTool->exec()) {
            emit finished(taskName, 1, 1);
            currentTool->deleteLater();
            return;
        }
        currentTool->deleteLater();
    }
    emit finished(taskName, 0, 0);
}

void ToolWorker::kill()
{
    currentTool->kill();    
    emit finished(taskName, 1, 1);
}
