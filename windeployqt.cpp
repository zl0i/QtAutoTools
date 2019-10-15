#include "windeployqt.h"

Windeployqt::Windeployqt(QObject *parent) : QObject(parent)
{
    process = new QProcess(this);
    worker = Worker::getInstance();
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SIGNAL(finished()));
    //connect(process, &QProcess::finished, this, &Windeployqt::finished);

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

void Windeployqt::setFlags(QStringList list)
{
    flags = list;
}

QFile *Windeployqt::prepareBatFile() {
    QFile *file = new QFile("deploy.bat");
    if(file->open(QIODevice::ReadWrite)) {
        QString str = "set PATH="+ worker->compl1Path() + "/bin;" +worker->compl2Path() + "/bin;%PATH%\n";
        file->write(str.toLocal8Bit());
        return file;
    }
    return  nullptr;
}

void Windeployqt::deploy(QString path)
{
    Q_UNUSED(path)
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
    if(flags.length() != 0) {
        arguments.append(flags.join(" "));
    }
    arguments.append(path);
    QFile *file = prepareBatFile();
    QString str = worker->compl1Path() + "/bin/windeployqt " + arguments.join(" ");
    file->write(str.toLocal8Bit());
    file->close();
    process->start("deploy.bat");
}

