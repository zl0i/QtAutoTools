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

    QJsonObject getScriptByName(QString);
    void saveScript(QJsonObject, QString);
    QStringList getNameScripts();
    void removeScript(QString);
    void removeAllScripts();

private:
    QDir scriptDir;

signals:

};

#endif // SCRIPTSTORAGE_H
