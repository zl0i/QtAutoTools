#ifndef TOOLSPATHFABRIC_H
#define TOOLSPATHFABRIC_H

#include <QString>
#include <QDir>
#include <QJsonObject>

class ToolsPathFabric
{
public:
    ToolsPathFabric(QJsonObject);

    QString profileBinPath();
    QString compilatorBinPath();

    QString qmakePath();
    //QString cmakePath();
    QString makeCompilerPath();
    QString windeployqtPath();
    QString binaryCreatorPath();
    QString repogenPath();
    QString lupdatePath();
    QString linguistPath();
    QString qmlplugindumpPath();


private:
    const QJsonObject settings;
};

#endif // TOOLSPATHFABRIC_H
