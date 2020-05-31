#include "taskmanager.h"

TaskManager::TaskManager(QObject *parent) : QObject(parent)
{

}

ToolWorker *TaskManager::getWorkerByVersion(QString version)
{
    if(version == "1.0")
        return  new ToolWorker();
    else if(version == "1.1")
        return new AdvansedToolWorker();

    return new ToolWorker();
}

void TaskManager::executeTask(QJsonObject obj)
{
    QString taskName = obj.value("name").toString();
    ToolWorker *worker = getWorkerByVersion(obj.value("version").toString());
    worker->setTaskName(taskName);
    toolWorkerMap[taskName] = worker;

    QJsonArray tasks = obj.value("tasks").toArray();
    IAdapter *adapter = qobject_cast<IAdapter*>(sender());

    connect(worker, &ToolWorker::started, adapter, &IAdapter::started);
    connect(worker, &ToolWorker::newOutputData, adapter, &IAdapter::newOutputData);
    connect(worker, &ToolWorker::newErrorData, adapter, &IAdapter::newErrorData);
    connect(worker, &ToolWorker::finished, adapter, &IAdapter::finished);
    connect(worker, &ToolWorker::finished, worker, &ToolWorker::deleteLater);

    worker->setTaskJson(tasks);
    worker->start();
}

void TaskManager::killTask(QString name)
{
    ToolWorker *worker = toolWorkerMap.value(name);
    if(worker)
        worker->kill();
    worker->deleteLater();

}


