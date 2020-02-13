#include "toolworker.h"

ToolWorker::ToolWorker(QObject *parent) : QThread(parent)
{

}

ToolWorker *ToolWorker::setTaskJson(QJsonArray arr)
{
    taskArray = arr;
    return  this;
}

void ToolWorker::run()
{
    AbstractTool *tool = ToolsFabric::createTool("Windeployqt");
    qDebug() << tool;
    tool->run();


}
