#include "./windeployqt.h"

Windeployqt::Windeployqt(QObject *parent) : AbstractTool(parent)
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


void Windeployqt::configFromJson(QJsonObject)
{
    qDebug() << "tut";
    if(!QFile(exeFile).exists())
        return;
qDebug() << "tut2";
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
    QString str = Worker::getInstance()->compilerPath() + "/bin/windeployqt " + arguments.join(" ");
    file->write(str.toLocal8Bit());
    file->close();
    file->deleteLater();
    process->start(file->fileName());
}

void Windeployqt::run()
{

}


