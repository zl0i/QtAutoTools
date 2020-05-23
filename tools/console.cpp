#include "console.h"

Console::Console(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{

}

void Console::configFromJson(QJsonObject obj)
{
    QJsonArray arr = obj.value("comands").toArray();
    for(int i = 0; i < arr.count(); i++) {
        comands.append(arr.at(i).toString());
    }
    sequentially = obj.value("sequentially").toBool();
}

bool Console::exec()
{
    if(comands.isEmpty()) {
        emit newErrorData("Comands is empty");
        return false;
    }


    QString joinComands;
    if(sequentially)
        joinComands = comands.join(" & ");
    else
        joinComands = comands.join(" | ");

    if(execCommand(joinComands)) {
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

