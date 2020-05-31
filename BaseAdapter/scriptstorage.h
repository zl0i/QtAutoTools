#ifndef SCRIPTSTORAGE_H
#define SCRIPTSTORAGE_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

class ScriptStorage : public QObject
{
    Q_OBJECT
public:
    explicit ScriptStorage(QObject *parent = nullptr);

    Q_INVOKABLE QJsonObject getScriptByName(QString) const;
    Q_INVOKABLE void saveScript(QJsonObject, QString) const;
    Q_INVOKABLE QStringList getNameScripts() const ;
    Q_INVOKABLE void removeScript(QString) const;
    Q_INVOKABLE void removeAllScripts() const;

   static bool validateScript(QJsonObject);

private:
    QDir scriptDir;

signals:
    void errorScript(QString);
};

#endif // SCRIPTSTORAGE_H
