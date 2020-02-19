#include "abstracttool.h"

AbstractTool::AbstractTool(QJsonObject settings, QObject *parent) : QObject(parent),
    qtPath(settings.value("qtPath").toString()),
    profilePath(settings.value("profilePath").toString()),
    compilerPath(settings.value("compilerPath").toString())
{
    process = new QProcess();

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, QOverload<int>::of(&AbstractTool::slotFinished));
    connect(process, &QProcess::readyRead, this, &AbstractTool::slotReadChanel);
}

void AbstractTool::waitFinished()
{
    process->waitForFinished(-1);
}

void AbstractTool::successFinished()
{

}

void AbstractTool::failFinished()
{

}


void AbstractTool::kill()
{
    process->kill();
}

void AbstractTool::slotFinished(int code)
{
    if(code == 0) {
        successFinished();
        emit newOutputData("Done!\r\n");
    } else {
        failFinished();
        emit newErrorData(process->readAllStandardError());
    }
    removeBatFile();
    emit finished(process->exitCode(), process->exitStatus());
}

void AbstractTool::slotReadChanel()
{
    process->setReadChannel(QProcess::StandardError);
    QByteArray error = process->readAll();
    if(!error.isEmpty())
        emit newErrorData(error);

    process->setReadChannel(QProcess::StandardOutput);
    QByteArray output = process->readAll();
    if(!output.isEmpty())
        emit newOutputData(output);
}

QFile* AbstractTool::prepareBatFile(bool addQtPath) const {
    QFile *file = new QFile("temp.bat");
    if(file->open(QIODevice::ReadWrite)) {
        if(addQtPath) {
            QString str = "set PATH="+ profilePath + "/bin;" + compilerPath + "/bin;%PATH%\n";
            file->write(str.toLocal8Bit());
        }
        return file;
    }
    return  nullptr;
}

void AbstractTool::removeBatFile()
{
    QFile::remove("temp.bat");
}
