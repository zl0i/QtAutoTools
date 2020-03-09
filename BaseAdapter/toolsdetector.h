#ifndef TOOLSDETECTOR_H
#define TOOLSDETECTOR_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QJsonObject>
#include <QJsonArray>
#include "settingsstorage.h"

class ToolsDetector : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList buildSystems READ getBuildSystems CONSTANT)
    Q_PROPERTY(QStringList qmlTypesFile READ getQmlTypesFile CONSTANT)
    Q_PROPERTY(QJsonObject detectTools READ getDetectTools CONSTANT)

public:


    static ToolsDetector* instanse() {
        static ToolsDetector* detector;
        if(!detector)
            detector = new ToolsDetector;
        return detector;
    }


    void setSettingsStorage(SettingsStorage*);

    Q_INVOKABLE void detect(QString qtpath = "");
    bool checkTools();

    Q_INVOKABLE QJsonObject getDetectTools() { return detectTools; }

    QStringList getBuildSystems() { return  QStringList {"qmake"}; } //cmake, Qbs
    QStringList getQmlTypesFile() { return  QStringList {"", "singleton", "internal"}; }

protected:
    explicit ToolsDetector();
    ToolsDetector(ToolsDetector&) = delete;
    ToolsDetector &operator= (ToolsDetector&) = delete;

private:
    QString qtPath;
    SettingsStorage *storage;

    QJsonObject detectTools;

    QStringList detectQtVersion();
    QStringList detectProfile(QString path);
    QStringList detectMkspecs(QString path);
    QStringList detectCompilers();
    QStringList detectIntallerFramework();

    void detectOtherTools();

    QJsonArray convertToJArray(QStringList);
};

#endif // TOOLSDETECTOR_H
