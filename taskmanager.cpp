#include "taskmanager.h"

TaskManager::TaskManager(QObject *parent) : QObject(parent)
{

    worker = new ToolWorker;

    connect(worker, &ToolWorker::started, this, &TaskManager::taskStarted);
    connect(worker, &ToolWorker::finished, this, &TaskManager::taskFinished);
}

void TaskManager::executeTask(QJsonArray arr)
{
    worker->setTaskJson(arr)->start();
}


