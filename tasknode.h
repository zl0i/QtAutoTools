#ifndef TASKNODE_H
#define TASKNODE_H

#include <QObject>
#include <QJsonObject>

class TaskNode
{
    //Q_OBJECT
public:
    TaskNode(QJsonObject);


    void insertChild();
    void start();

private:
    QJsonObject task;
    QList<TaskNode*> list;


};

#endif // TASKNODE_H
