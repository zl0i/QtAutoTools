#ifndef SETTINGSSTORAGE_H
#define SETTINGSSTORAGE_H

#include <QObject>

class SettingsStorage : public QObject
{
    Q_OBJECT

public:
    virtual void saveUserSettings(QString, QJsonObject) = 0;
    virtual QJsonObject getUserSettings(QString) = 0;

    virtual void clearAllSettings() = 0;

signals:


};

#endif // SETTINGSSTORAGE_H
