#ifndef QSETTINGSSTORAGE_H
#define QSETTINGSSTORAGE_H

#include <QObject>
#include <QSettings>
#include "BaseAdapter/settingsstorage.h"

class QSettingsStorage : public SettingsStorage
{
    Q_OBJECT

public:
    explicit QSettingsStorage(QObject *parent = nullptr);

    void setCustomValue(QString, QVariant) override;
    QVariant getCustomValue(QString) override;

public slots:
    QString getQtPath() override;
    void setQtPath(QString) override;

    QString getProfilePath() override;
    void setProfilePath(QString) override;

    QString getCompilerPath() override;
    void setCompilerPath(QString) override;



    void clearAllSettings() override;

private:
    QSettings settings;

signals:

};

#endif // QSETTINGSSTORAGE_H
