#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include "toolsfabric.h"
#include "toolworker.h"
#include "IAdapter.h"

class TaskManager : public QObject
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = nullptr);



private:
    //ToolWorker *worker;
    //QList<ToolWorker*> listToolWorker;

signals:
    void taskStarted();
    void taskNewData();
    void taskNewError();
    void taskFinished();

public slots:
    void executeTask(QJsonObject);



};

#endif // TASKMANAGER_H
