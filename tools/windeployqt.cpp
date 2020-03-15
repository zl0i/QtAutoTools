#include "./windeployqt.h"

Windeployqt::Windeployqt(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{   

}


void Windeployqt::setExeFile(QString path)
{
    exeFile = path;
}

void Windeployqt::setDir(QString path)
{
    dir = path;
}

void Windeployqt::setPlugindir(QString path)
{
    plugindir = path;
}

void Windeployqt::setLibdir(QString path)
{
    libdir = path;
}

void Windeployqt::setQmlimport(QString path)
{
    qmlimport = path;
}

void Windeployqt::setQmldir(QString path)
{
    qmldir = path;
}

void Windeployqt::setFlags(QString flags)
{
    this->flags = flags;
}

void Windeployqt::setLibraries(QString libraries)
{
    this->libraries = libraries;
}


void Windeployqt::configFromJson(QJsonObject obj)
{
    exeFile = obj.value("exeFile").toString();
    dir = obj.value("deployDir").toString();
    plugindir = obj.value("pluginDir").toString();
    libdir = obj.value("libraryDir").toString();
    qmldir = obj.value("qmlFilesDir").toString();
    qmlimport = obj.value("qmlPluginsDir").toString();
    flags = obj.value("flags").toString();
    libraries = obj.value("library").toString();
}

void Windeployqt::run()
{
    if(!QFile(exeFile).exists())
        return;

    QStringList arguments;
    if(!dir.isEmpty()) {
        arguments.append("--dir " + dir);
    }
    if(!plugindir.isEmpty()) {
        arguments.append("--plugindir " + plugindir);
    }
    if(!libdir.isEmpty()) {
        arguments.append("--libdir " + libdir);
    }
    if(!qmldir.isEmpty()) {
        arguments.append("--qmldir " + qmldir);
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
    QFile *file = prepareBatFile(true);
    QString str = pathFabric.windeployqtPath() + " " + arguments.join(" ");
    file->write(str.toLocal8Bit());
    file->close();
    file->deleteLater();
    process->start(file->fileName());
}

void Windeployqt::successFinished() {
    if(!dir.isEmpty()) {
        QString nameExeFile = exeFile.split("/").last();
        QFile::copy(exeFile, dir+"/" + nameExeFile);
    }
}


