#ifndef SCRIPTSTORAGE_H
#define SCRIPTSTORAGE_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

class ScriptStorage : public QObject
{
    Q_OBJECT
public:
    explicit ScriptStorage(QObject *parent = nullptr);

    Q_INVOKABLE QJsonObject getScriptByName(QString);
    Q_INVOKABLE void saveScript(QJsonObject, QString);
    Q_INVOKABLE QStringList getNameScripts();
    Q_INVOKABLE void removeScript(QString);
    Q_INVOKABLE void removeAllScripts();

private:
    QDir scriptDir;

signals:

};

#endif // SCRIPTSTORAGE_H
