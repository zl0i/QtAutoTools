#ifndef BASEADAPTER_H
#define BASEADAPTER_H

#include <QObject>
#include <QJsonObject>
#include "IAdapter.h"
#include "scriptstorage.h"

class BaseAdapter : public IAdapter
{
    Q_OBJECT
public:
    explicit BaseAdapter(QObject *parent = nullptr);


protected:


signals:
    void signalExecuteTask(QJsonObject);

public slots:
    void executeTask(QJsonObject obj) { emit signalExecuteTask(obj); }
    void executeScript(QString) {}

};

#endif // BASEADAPTER_H
