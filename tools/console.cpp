#include "console.h"

Console::Console(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{

}

void Console::configFromJson(QJsonObject obj)
{
    QJsonArray arr = obj.value("comands").toArray();
    sequentially = obj.value("sequentially").toBool();

    for(int i = 0; i < arr.count(); ++i) {
        comands.append(arr.at(i).toString());
    }
}

bool Console::exec()
{
    if(comands.isEmpty()) {
        emit newErrorData("Comands is empty");
        return false;
    }

    QString joinCommadns;
    if(sequentially)
        joinCommadns = comands.join(" & ");
    else
        joinCommadns = comands.join(" |");

    if(execCommand(joinCommadns)) {
        return true;
    } else {
        emit newErrorData("");
        return false;
    }
    return false;
}

void Console::cancelExec()
{

}
