#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include "toolsfabric.h"
#include "toolworker.h"

class TaskManager : public QObject
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = nullptr);



private:
    ToolWorker *worker;

signals:
    void taskStarted();
    void taskNewData();
    void taskNewError();
    void taskFinished();

public slots:
    void executeTask(QJsonArray);



};

#endif // TASKMANAGER_H
