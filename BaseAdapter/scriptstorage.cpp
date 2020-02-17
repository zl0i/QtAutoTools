#include "scriptstorage.h"

ScriptStorage::ScriptStorage(QObject *parent) : QObject(parent)
{
    scriptDir.mkpath("./scripts");
    scriptDir.setPath("./scripts");
}

QJsonObject ScriptStorage::getScriptByName(QString name)
{
    QFile script(scriptDir.path() + QDir::separator() + name + ".json");
    if(!script.exists())
        return QJsonObject {};

    if(script.open(QIODevice::ReadOnly)) {
        QByteArray array = script.readAll();
        QJsonDocument document = QJsonDocument::fromJson(array);
        script.close();
        return  document.object();
    }
    return  QJsonObject {};
}

void ScriptStorage::saveScript(QJsonObject object, QString name)
{
    QFile script(scriptDir.path() + QDir::separator() + name + ".json");
    if(script.open(QIODevice::ReadWrite)) {
        script.resize(0);
        QJsonDocument documnet(object);
        script.write(documnet.toJson());
        script.close();
    }
}

QStringList ScriptStorage::getNameScripts()
{
    QStringList scripts = scriptDir.entryList(QStringList {"*.json"}, QDir::Files);
    return scripts;
}

void ScriptStorage::removeScript(QString name)
{
    QFile::remove(scriptDir.path() + QDir::separator() + name + ".json");
}

void ScriptStorage::removeAllScripts()
{
    QStringList scripts = scriptDir.entryList(QStringList {"*.json"}, QDir::Files);
    for(int i = 0; i < scripts.length(); ++i)
        QFile::remove(scriptDir.path() + QDir::separator() + scripts.at(i));
}
