#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QDateTime>
#include <QRandomGenerator>
#include <QEventLoop>
#include "itool.h"
#include "toolspathfabric.h"

class AbstractTool : public ITool
{
    Q_OBJECT

public:
    AbstractTool(QJsonObject obj, QObject *parent = nullptr);
    AbstractTool(QObject *parent = nullptr);

    bool execCommand(QString command, bool detach = false);

protected:

    ToolsPathFabric pathFabric;

private:
    QProcess *process;
    QString currentFileName;

    QFile *prepareBatFile(bool env = true);
    void removeBatFile();

signals:

public slots:
    void slotReadChanel();
    void kill() override;
};

#endif // ABSTRACTTOOL_H
