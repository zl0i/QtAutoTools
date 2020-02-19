#ifndef SETTINGSSTORAGE_H
#define SETTINGSSTORAGE_H

#include <QObject>

class SettingsStorage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString qtPath READ getQtPath WRITE setQtPath NOTIFY qtPathChanged)
    Q_PROPERTY(QString profilePath READ getProfilePath WRITE setProfilePath NOTIFY profilePathChanged)
    Q_PROPERTY(QString compilerPath READ getCompilerPath WRITE setCompilerPath NOTIFY compilerPathChanged)
public:
    explicit SettingsStorage(QObject *parent = nullptr);

    virtual void setCustomValue(QString, QVariant) = 0;
    virtual QVariant getCustomValue(QString) = 0;

public slots:

    virtual QString getQtPath() = 0;
    virtual void setQtPath(QString) = 0;

    virtual QString getProfilePath() = 0;
    virtual void setProfilePath(QString) = 0;

    virtual QString getCompilerPath() = 0;
    virtual void setCompilerPath(QString) = 0;

    virtual void clearAllSettings() = 0;

signals:
    void qtPathChanged();
    void profilePathChanged();
    void compilerPathChanged();

};

#endif // SETTINGSSTORAGE_H
