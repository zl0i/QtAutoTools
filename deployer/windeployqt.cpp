#include "deployer/windeployqt.h"

Windeployqt::Windeployqt(QObject *parent) : QProcess(parent)
{   
    connect(this, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, QOverload<int>::of(&Windeployqt::slotFinished));
    connect(this, &QProcess::readyRead, this, &Windeployqt::slotReadChanel);
}

void Windeployqt::slotReadChanel() {    
    setReadChannel(QProcess::StandardError);
    QByteArray error = readAll();   
    if(!error.isEmpty())
        emit newErrorData(error);

    setReadChannel(QProcess::StandardOutput);
    QByteArray output = readAll();    
    if(!output.isEmpty())
        emit newOutputData(output);

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

void Windeployqt::deploy()
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
    QFile *file = Worker::prepareBatFile(true);
    QString str = Worker::getInstance()->compilerPath() + "/bin/windeployqt " + arguments.join(" ");
    file->write(str.toLocal8Bit());
    file->close();
    file->deleteLater();
    start(file->fileName());
}

void Windeployqt::slotFinished(int code) {
    if(code > 0) {
        emit newErrorData(readAllStandardError());
    } else {
        if(!dir.isEmpty()) {
            QString nameExeFile = exeFile.split("/").last();
            QFile::copy(exeFile, dir+"/" + nameExeFile);
        }
    }
    Worker::removeBatFile();
}
