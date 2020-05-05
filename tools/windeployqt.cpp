#include "./windeployqt.h"

Windeployqt::Windeployqt(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{   

}

void Windeployqt::configFromJson(QJsonObject obj)
{
    exeFile = obj.value("exeFile").toString();
    deployDir = obj.value("deployDir").toString();
    pluginDir = obj.value("pluginDir").toString();
    libDir = obj.value("libraryDir").toString();
    qmlDir = obj.value("qmlFilesDir").toString();
    qmlimport = obj.value("qmlPluginsDir").toString();
    flags = obj.value("flags").toString();
    libraries = obj.value("library").toString();
}

bool Windeployqt::exec()
{
    if(!QFile(exeFile).exists()) {
        emit newErrorData("Exe file is not exist.");
        return false;
    }

    if(deployDir.isEmpty()) {
        emit newErrorData("Deploy dir is not exist."); ///!!!!!!!!!!!
        return false;
    }

    QDir(deployDir).mkpath(deployDir) ;

    QStringList arguments;
    if(!deployDir.isEmpty()) {
        arguments.append("--dir " + deployDir);
    }
    if(!pluginDir.isEmpty()) {
        arguments.append("--plugindir " + pluginDir);
    }
    if(!libDir.isEmpty()) {
        arguments.append("--libdir " + libDir);
    }
    if(!qmlDir.isEmpty()) {
        arguments.append("--qmldir " + qmlDir);
    }
    if(!qmlimport.isEmpty()) {
        arguments.append("--qmlimport " + qmlimport);
    }
    if(!exeFile.isEmpty()) {
        arguments.append(exeFile);
    }
    if(flags.length() != 0) {
        arguments.append(flags);
    }
    if(libraries.length() != 0) {
        arguments.append(libraries);
    }
    QString program = pathFabric.windeployqtPath() + " " + arguments.join(" ");
    if(execCommand(program)) {
        QString nameExeFile = exeFile.split("/").last();
        QFile::copy(exeFile, deployDir + QDir::separator() + nameExeFile);
        return true;
    }
    return false;
}

void Windeployqt::cancelExec()
{
    QDir(deployDir).rmdir(deployDir);
}
