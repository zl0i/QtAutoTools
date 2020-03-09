#ifndef QSETTINGSSTORAGE_H
#define QSETTINGSSTORAGE_H

#include <QObject>
#include <QSettings>
#include <QJsonObject>
#include <QDebug>
#include "BaseAdapter/settingsstorage.h"

class QSettingsStorage : public SettingsStorage
{
    Q_OBJECT

public:
    explicit QSettingsStorage(QObject *parent = nullptr);

    QJsonObject getUserSettings(QString) override;
    void saveUserSettings(QString, QJsonObject) override;

    void clearAllSettings() override;

private:
    QSettings settings;

signals:

};

#endif // QSETTINGSSTORAGE_H
