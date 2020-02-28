#ifndef TOOLSDETECTOR_H
#define TOOLSDETECTOR_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QJsonObject>
#include <QJsonArray>


class ToolsDetector : public QObject
{
    Q_OBJECT


public:
    explicit ToolsDetector(QObject *parent = nullptr);

    void detect(QString qtpath);
    bool checkTools();

    QJsonObject getDetectTools() { return detectTools; }

private:
    QString qtPath;

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
