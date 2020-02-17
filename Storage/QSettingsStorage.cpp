#include "qsettingsstorage.h"

QSettingsStorage::QSettingsStorage(QObject *parent) : SettingsStorage(parent)
{

}

QString QSettingsStorage::getQtPath()
{
    return settings.value("qtpath").toString();
}

void QSettingsStorage::setQtPath(QString path)
{
    settings.setValue("qtpath", path);
}

QString QSettingsStorage::getProfilePath()
{
    return settings.value("profilepath").toString();
}

void QSettingsStorage::setProfilePath(QString path)
{
     settings.setValue("profilepath", path);
}

QString QSettingsStorage::getCompilerPath()
{
    return settings.value("compilerpath").toString();
}

void QSettingsStorage::setCompilerPath(QString path)
{
    settings.setValue("compilerpath", path);
}

void QSettingsStorage::setCustomValue(QString name, QVariant value)
{
    settings.setValue(name, value);
}

QVariant QSettingsStorage::setCustomValue(QString name)
{
    return settings.value(name);
}

void QSettingsStorage::clearAllSettings()
{
    settings.clear();
}
