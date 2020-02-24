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
    Q_PROPERTY(QStringList qtVersion READ getQtVersion NOTIFY qtVersionChanged)
    Q_PROPERTY(QStringList qtProfile READ getQtProfile NOTIFY qtProfileChanged)
    Q_PROPERTY(QStringList compilerList READ getCompilerList NOTIFY compilerListChanged)
    Q_PROPERTY(QStringList installerVerison READ getInstallerVerison NOTIFY installerVerisonChanged)
    Q_PROPERTY(QJsonObject detectTools READ getDetectTools NOTIFY detectToolsChanged)

public:
    explicit ToolsDetector(QObject *parent = nullptr);

    Q_INVOKABLE void detect(QString qtpath);

    Q_INVOKABLE void detectProfile(QString versionDir);
    Q_INVOKABLE void setProfile(QString);
    Q_INVOKABLE void setCompiler(QString);
    Q_INVOKABLE void setInstallerFramework(QString);
    //Q_INVOKABLE void detectOtherTools();
    Q_INVOKABLE void checkAllTools();

    QStringList getQtVersion() {return versionsDirs; }
    QStringList getQtProfile() {return qtProfile; }
    QStringList getCompilerList() { return compilerList; }
    QStringList getInstallerVerison() { return installerList; }
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
    void qtVersionChanged();
    void qtProfileChanged();
    void compilerListChanged();
    void installerVerisonChanged();
    void detectToolsChanged();
};

#endif // TOOLSDETECTOR_H
