#include "scriptstorage.h"

ScriptStorage::ScriptStorage(QObject *parent) : QObject(parent)
{
    scriptDir.mkpath("./scripts");
    scriptDir.setPath("./scripts");
}

QJsonObject ScriptStorage::getScriptByName(QString name) const
{
    QFile script(scriptDir.path() + QDir::separator() + name);
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

void ScriptStorage::saveScript(QJsonObject object, QString name) const
{
    QFile script(scriptDir.path() + QDir::separator() + name + ".json");
    if(script.open(QIODevice::ReadWrite)) {
        script.resize(0);
        QJsonDocument documnet(object);
        script.write(documnet.toJson());
        script.close();
    }
}

QStringList ScriptStorage::getNameScripts() const
{
    QStringList scripts = scriptDir.entryList(QStringList {"*.json"}, QDir::Files);
    return scripts;
}

void ScriptStorage::removeScript(QString name) const
{
    QFile::remove(scriptDir.path() + QDir::separator() + name);
}

void ScriptStorage::removeAllScripts() const
{
    QStringList scripts = scriptDir.entryList(QStringList {"*.json"}, QDir::Files);
    for(int i = 0; i < scripts.length(); ++i)
        QFile::remove(scriptDir.path() + QDir::separator() + scripts.at(i));
}
