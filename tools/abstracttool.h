#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QDateTime>
#include <QRandomGenerator>
#include "itool.h"
#include "toolspathfabric.h"

class AbstractTool : public ITool
{
    Q_OBJECT

public:
    AbstractTool(QJsonObject obj, QObject *parent = nullptr);
    AbstractTool(QObject *parent = nullptr);

    void waitFinished() override;

protected:
    QProcess *process;

    virtual void successFinished();
    virtual void failFinished();

    QFile *prepareBatFile(bool env = true);
    void removeBatFile();

    ToolsPathFabric pathFabric;

private:
    QString currentFileName;

signals:

public slots:
    virtual void slotFinished(int);
    void errorOcured(QProcess::ProcessError error);
    void slotReadChanel();
    void kill() override;
};

#endif // ABSTRACTTOOL_H
