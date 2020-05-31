#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include "toolsfabric.h"
#include "toolworker.h"
#include "advansedtoolworker.h"
#include "IAdapter.h"

class TaskManager : public QObject
{
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = nullptr);

protected:
    virtual ToolWorker *getWorkerByVersion(QString);

private:    
    QHash<QString, ToolWorker*> toolWorkerMap;
    QThreadPool poolTask;

signals:
    void taskStarted();
    void taskNewData();
    void taskNewError();
    void taskFinished();

public slots:
    void executeTask(QJsonObject);
    void killTask(QString);



};

#endif // TASKMANAGER_H
