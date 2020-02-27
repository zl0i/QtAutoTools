#ifndef TOOLSDETECTOR_H
#define TOOLSDETECTOR_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QJsonObject>


class ToolsDetector : public QObject
{
    Q_OBJECT


public:
    explicit ToolsDetector(QObject *parent = nullptr);

    Q_INVOKABLE void detect(QString qtpath);
    bool checkTools();

    Q_INVOKABLE void detectProfile(QString versionDir);
    Q_INVOKABLE void setProfile(QString);
    Q_INVOKABLE void setCompiler(QString);
    Q_INVOKABLE void setInstallerFramework(QString);
    //Q_INVOKABLE void detectOtherTools();
    Q_INVOKABLE void checkAllTools();


    QJsonObject getDetectTools() { return detectTools; }

private:

    const QStringList qmlTypes = {"", "singleton", "internal"};

    QString qtPath;

    QStringList versionsDirs;
    QStringList qtProfile;
    QStringList compilerList;
    QStringList installerList;

    QJsonObject detectTools;

    void detectQtVersion();
    void detectCompiler();
    void detectIntallerFramework();
    void detectOtherTools();

signals:

    void detectToolsChanged();
};

#endif // TOOLSDETECTOR_H
