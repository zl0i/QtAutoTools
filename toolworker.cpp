#include "toolworker.h"

ToolWorker::ToolWorker(QObject *parent) : QThread(parent)
{

}

ToolWorker::ToolWorker(const ToolWorker &worker) : QThread(), taskArray(worker.taskArray)
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

ToolWorker::~ToolWorker()
{

}

void ToolWorker::run()
{
    emit started();
    for(int i = 0; i < taskArray.size(); ++i) {
        QJsonObject task = taskArray.at(i).toObject();
        AbstractTool *tool = ToolsFabric::createTool(task.value("tool").toString(), task.value("settings").toObject());
        connect(tool, &AbstractTool::newOutputData, this, &ToolWorker::newOutputData);
        connect(tool, &AbstractTool::newErrorData, this, &ToolWorker::newErrorData);
        tool->configFromJson(task);
        tool->run();
        tool->waitFinished();
        tool->deleteLater();
    }
    emit finished(0, 0);
}
