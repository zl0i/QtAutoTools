#include "advansedtoolworker.h"

AdvansedToolWorker::AdvansedToolWorker()
{

}

void AdvansedToolWorker::run()
{
    emit started(taskName);

    QJsonArray tasks = getTaskDependense("");

    for(int i = 0; i < tasks.count(); i++) {
        ToolWorker *worker = new ToolWorker();
        listWorker.append(worker);
        QString label = tasks.at(i).toObject().value("label").toString();

        worker->setTaskName(label);
        worker->setTaskJson(QJsonArray {tasks.at(i)});

        emit newOutputData(taskName, label.toLocal8Bit() + " started!\r\n");

        connect(worker, &ToolWorker::newErrorData, this, &ToolWorker::newErrorData);
        connect(worker, &ToolWorker::finished, this, &AdvansedToolWorker::toolWorkerFinished);
        worker->start();
    }
}

void AdvansedToolWorker::killAllWorkers()
{
    emit finished(this->taskName, 1, 1);
    for(int i = 0; i < listWorker.count(); i++) {
        disconnect(listWorker.at(i), &ToolWorker::finished, this, &AdvansedToolWorker::toolWorkerFinished);
        listWorker.at(i)->kill();
        listWorker.at(i)->deleteLater();
    }
}

QJsonArray AdvansedToolWorker::getTaskDependense(QString label)
{
    QJsonArray arr;
    for(int i = 0; i < taskArray.count(); i++) {
        QJsonObject task = taskArray.at(i).toObject();
        if(task.value("dependence").toString() == label) {
            arr.append(task);
            taskArray.removeAt(i);
            i--;
        }
    }
    return  arr;
}

void AdvansedToolWorker::toolWorkerFinished(QString taskName, int exitCode, int)
{
    ToolWorker *fworker = qobject_cast<ToolWorker*>(sender());
    listWorker.removeOne(fworker);
    fworker->deleteLater();

    if(exitCode != 0) {
        emit newErrorData(taskName, taskName.toLocal8Bit() + " error!\r\n");
        killAllWorkers();
        return;
    } else {
        emit newOutputData(taskName, taskName.toLocal8Bit() + " finished!\r\n");
    }

    QJsonArray tasks = getTaskDependense(taskName);

    for(int i = 0; i < tasks.count(); i++) {
        ToolWorker *nworker = new ToolWorker();
        listWorker.append(nworker);
        QString label = tasks.at(i).toObject().value("label").toString();

        nworker->setTaskName(label);
        nworker->setTaskJson(QJsonArray {tasks.at(i)});

        emit newOutputData(taskName, label.toLocal8Bit() + " started!\r\n");
        connect(nworker, &ToolWorker::finished, this, &AdvansedToolWorker::toolWorkerFinished);
        nworker->start();
    }

    if(listWorker.count() == 0)
        emit finished(taskName, 0, 0);
}

void AdvansedToolWorker::kill()
{
    killAllWorkers();
}
