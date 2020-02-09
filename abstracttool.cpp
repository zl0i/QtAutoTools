#include "abstracttool.h"

AbstractTool::AbstractTool(QObject *parent) : QObject(parent)
{
    process = new QProcess();

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, QOverload<int>::of(&AbstractTool::slotFinished));
    connect(process, &QProcess::readyRead, this, &AbstractTool::slotReadChanel);
}


void AbstractTool::kill()
{
    process->kill();
}

void AbstractTool::slotFinished(int code)
{
    if(code > 0) {
        emit newErrorData(process->readAllStandardError());
    }
    Worker::removeBatFile();
    emit newOutputData("Done!\r\n");
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

QFile* AbstractTool::prepareBatFile(bool addQtPath) {
    QFile *file = new QFile("temp.bat");
    if(file->open(QIODevice::ReadWrite)) {
        if(addQtPath) {
            QString str = "set PATH="+ Worker::getInstance()->compilerPath() + "/bin;%PATH%\n"; //+ Worker::getInstance()->compilerToolPath() + "/bin;%PATH%\n";
            file->write(str.toLocal8Bit());
        }
        return file;
    }
    return  nullptr;
}
