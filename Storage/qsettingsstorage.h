#ifndef QSETTINGSSTORAGE_H
#define QSETTINGSSTORAGE_H

#include <QObject>
#include <QSettings>
#include "BaseAdapter/settingsstorage.h"

class QSettingsStorage : public SettingsStorage
{
    Q_OBJECT
    //Q_PROPERTY(QString qtPath WRITE )

public:
    explicit QSettingsStorage(QObject *parent = nullptr);

    QString getQtPath() override;
    void setQtPath(QString) override;

    QString getProfilePath() override;
    void setProfilePath(QString) override;

    QString getCompilerPath() override;
    void setCompilerPath(QString) override;

    void setCustomValue(QString, QVariant) override;
    QVariant setCustomValue(QString) override;

    void clearAllSettings() override;

private:
    QSettings settings;

signals:

};

#endif // QSETTINGSSTORAGE_H
