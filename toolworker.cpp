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
    for(int i = 0; i < taskArray.size(); ++i) {
        QJsonObject task = taskArray.at(i).toObject();
        AbstractTool *tool = ToolsFabric::createTool(task.value("tool").toString());
        qDebug() << tool;
        tool->configFromJson(task);
        tool->run();
        tool->deleteLater();
    }
}
