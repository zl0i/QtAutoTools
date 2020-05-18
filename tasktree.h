#ifndef TASKTREE_H
#define TASKTREE_H

#include <QObject>

#include "tasknode.h"

class TaskTree
{
    //Q_OBJECT
public:
    TaskTree();

    void insert(QJsonObject, QString);

    void start();

private:
    TaskNode *root;
};

#endif // TASKTREE_H
