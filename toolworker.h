#ifndef TOOLWORKER_H
#define TOOLWORKER_H

#include <QObject>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "abstracttool.h"
#include "toolsfabric.h"

class ToolWorker : public QThread
{
    Q_OBJECT
public:
    explicit ToolWorker(QObject *parent = nullptr);

    ToolWorker *setTaskJson(QJsonArray);

protected:
    void run() override;

private:
    QJsonArray taskArray;


signals:

};

#endif // TOOLWORKER_H
