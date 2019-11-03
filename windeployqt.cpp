#include "windeployqt.h"

Windeployqt::Windeployqt(QObject *parent) : QObject(parent)
{
    process = new QProcess(this);
    worker = Worker::getInstance();
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotFinished()));
    //connect(process, &QProcess::finished, this, &Windeployqt::slotFinished);

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

QFile *Windeployqt::prepareBatFile() {
    QFile *file = new QFile("deploy.bat");
    if(file->open(QIODevice::ReadWrite)) {
        QString str = "set PATH="+ worker->compilerPath() + "/bin;" +worker->compilerToolPath() + "/bin;%PATH%\n";
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
        arguments.append(flags);
    }
    arguments.append(path);
    QFile *file = prepareBatFile();
    QString str = worker->compilerPath() + "/bin/windeployqt " + arguments.join(" ");
    file->write(str.toLocal8Bit());
    file->close();
    file->deleteLater();
    process->start("deploy.bat");
}

void Windeployqt::slotFinished() {
     QFile::remove("deploy.bat");
     emit finished();
}
