#include "taskmanager.h"

TaskManager::TaskManager(QObject *parent) : QObject(parent)
{

}

void TaskManager::executeTask(QJsonObject obj)
{
    ToolWorker *worker = new ToolWorker;
    //listToolWorker.append(worker);
    QJsonArray tasks = obj.value("tasks").toArray();
    IAdapter *adapter = qobject_cast<IAdapter*>(sender());

    connect(worker, &ToolWorker::started, adapter, &IAdapter::started);
    connect(worker, &ToolWorker::newOutputData, adapter, &IAdapter::newOutputData);
    connect(worker, &ToolWorker::newErrorData, adapter, &IAdapter::newErrorData);
    connect(worker, &ToolWorker::finished, adapter, &IAdapter::finished);
    connect(worker, &ToolWorker::finished, worker, &ToolWorker::deleteLater);
    worker->setTaskJson(tasks)->start();
}


