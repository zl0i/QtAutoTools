#include "consoleadapter.h"

ConsoleAdapter::ConsoleAdapter(QString file, SettingsStorage *storage, QObject *parent) : BaseAdapter(storage, parent)
{
    QFile scriptFile(file);
    if(scriptFile.exists()) {
        if(scriptFile.open(QIODevice::ReadOnly)) {
            QJsonDocument jsonDocument = QJsonDocument::fromJson(scriptFile.readAll());
            script = jsonDocument.object();
        }
    } else {
        script = scriptStorage.getScriptByName(file);
    }
}

bool ConsoleAdapter::start()
{
    if(script.isEmpty()) {
        qDebug() << "Error script";
        emit scriptFinished(1);
        return false;
    }
    emit signalExecuteTask(script);
    return true;
}

void ConsoleAdapter::displayScripts()
{
    QStringList names = scriptStorage.getNameScripts();
    for(int i = 0; i < names.size(); i++)
        qDebug() << names.at(i);
}


QJsonObject ConsoleAdapter::getUserSettings(QObject*)
{
    return QJsonObject {};
}

bool ConsoleAdapter::isRunningTask(QObject *)
{
    return true;
}

void ConsoleAdapter::started(QString)
{
    qDebug() << "Started";
}

void ConsoleAdapter::newErrorData(QString, QByteArray line)
{
    QList<QByteArray> out = line.split('\n');
    for(int i = 0; i < out.size(); i++) {
        QString str = out.at(i);
        qDebug() << str.replace("\r", "");
    }
}

void ConsoleAdapter::newOutputData(QString, QByteArray line)
{
    QList<QByteArray> out = line.split('\n');
    for(int i = 0; i < out.size(); i++) {
        QString str = out.at(i);
        qDebug() << str.replace("\r", "");
    }
}

void ConsoleAdapter::finished(QString, int exitCode, int)
{
    /*if(exitCode == 0)
        qDebug() << "Script to be complited success";
    else
        qDebug() << "Script to be complited fail";*/
    emit scriptFinished(exitCode);
}

void ConsoleAdapter::kill()
{

}
