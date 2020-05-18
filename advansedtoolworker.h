#ifndef ADVANSEDTOOLWORKER_H
#define ADVANSEDTOOLWORKER_H

#include <QObject>
#include "toolworker.h"

class AdvansedToolWorker : public ToolWorker
{
    Q_OBJECT
public:
    AdvansedToolWorker();

protected:
    void run() override;

private:
    void killAllWorkers();
    QJsonArray getTaskDependense(QString label);

    QList<ToolWorker*> listWorker;

private slots:
    void toolWorkerFinished(QString taskName, int exitCode, int exitStatus);

public slots:
    void kill() override;

};

#endif // ADVANSEDTOOLWORKER_H
