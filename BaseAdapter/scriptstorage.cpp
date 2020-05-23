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
        if(validateScript(document.object()))
            return document.object();
    }
    return  QJsonObject {};
}

void ScriptStorage::saveScript(QJsonObject object, QString name) const
{
    if(!validateScript(object))
        return;

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

bool ScriptStorage::validateScript(QJsonObject script)
{
    QJsonArray tasks = script.value("tasks").toArray();
    QStringList labelList;
    for(int i = 0; i < tasks.count(); i++) {
        QString label = tasks.at(i).toObject().value("label").toString();
        if(label.isEmpty())
            return false;

        for(int j = 0; j < labelList.count(); j++) {
            if(labelList.at(j) == label)
                return false;
        }
        labelList.append(label);
    }

    for(int i = 0; i < tasks.count(); i++) {
        bool find = false;
        QString dependence = tasks.at(i).toObject().value("dependence").toString();
        if(dependence.isEmpty())
            continue;

        for(int j = 0; j < labelList.count(); j++) {
            if(dependence == labelList.at(j)) {
                find = true;
                break;
            }
        }
        if(!find)
            return false;
    }

    return true;
}

