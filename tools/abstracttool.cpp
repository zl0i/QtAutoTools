#include "abstracttool.h"

AbstractTool::AbstractTool(QJsonObject settings, QObject *parent) : ITool(parent),
    qtPath(settings.value("qtPath").toString()),
    profilePath(settings.value("profilePath").toString()),
    compilerPath(settings.value("compilerPath").toString())
{
    process = new QProcess();
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, QOverload<int>::of(&AbstractTool::slotFinished));
    connect(process, &QProcess::readyRead, this, &AbstractTool::slotReadChanel);
    connect(process, &QProcess::errorOccurred, this, &AbstractTool::errorOcured);
}

void AbstractTool::waitFinished()
{
    process->waitForFinished(-1);
}

void AbstractTool::successFinished()
{
      QFile *file = prepareBatFile(false);
      file->readAll();
      file = prepareBatFile(true);

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
    qDebug() << process->readAllStandardOutput() << process->readAllStandardError();
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

void AbstractTool::errorOcured(QProcess::ProcessError error)
{
    qDebug() << error;
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

QFile *AbstractTool::prepareBatFile(bool addQtPath)  {
    currentFileName = QString::number(QDateTime::currentMSecsSinceEpoch()) + QString::number(QRandomGenerator::global()->generate());
    QFile *const file = new QFile(currentFileName + ".bat");
    if(file->open(QIODevice::ReadWrite)) {
        if(addQtPath) {
            QString str = "set PATH="+ profilePath + "/bin;" + compilerPath + "/bin;%PATH%\n";
            file->write(str.toLocal8Bit());
        }
        return file;
    }
    return nullptr;
}

void AbstractTool::removeBatFile()
{
   QFile::remove(currentFileName + ".bat");
}
