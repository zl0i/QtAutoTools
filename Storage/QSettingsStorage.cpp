#include "qsettingsstorage.h"

QSettingsStorage::QSettingsStorage(QObject*)
{

}

QJsonObject QSettingsStorage::getUserSettings(QString user)
{
    return  settings.value(user).toJsonObject();
}

void QSettingsStorage::saveUserSettings(QString user, QJsonObject obj)
{
   settings.setValue(user, obj);
}

void QSettingsStorage::clearAllSettings()
{
    settings.clear();
}
