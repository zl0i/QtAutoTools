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


    static ToolsDetector* instanse() {
        static ToolsDetector* detector;
        if(!detector)
            detector = new ToolsDetector;
        return detector;
    }

    void detect(QString qtpath);
    bool checkTools();

    QJsonObject getDetectTools() { return detectTools; }

protected:
    explicit ToolsDetector();
    ToolsDetector(ToolsDetector&) = delete;
    ToolsDetector &operator= (ToolsDetector&) = delete;
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
