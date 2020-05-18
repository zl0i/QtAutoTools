#include "abstracttool.h"

AbstractTool::AbstractTool(QJsonObject task, QObject *parent) : ITool(parent), pathFabric(task.value("environment").toObject())
{
    process = new QProcess();
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, &QProcess::readyRead, this, &AbstractTool::slotReadChanel);
}

bool AbstractTool::execCommand(QString command, bool detach) {

    if(!detach) {
        QFile *bat = prepareBatFile(true);

        bat->write(command.toLocal8Bit());
        bat->close();
        bat->deleteLater();

        process->start(bat->fileName());

        QEventLoop loop;
        connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), &loop, SLOT(quit()));
        connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), &loop, SLOT(quit()));
        loop.exec();
        removeBatFile();

        if(process->exitCode() == 0)
            return true;        
    } else {
        if(QProcess::startDetached(command))
            return true;
    }
    return false;
}

void AbstractTool::kill()
{      
    process->kill();
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
            QString str = "set PATH="+ pathFabric.profileBinPath() + ";" + pathFabric.compilatorBinPath() + ";%PATH%\n";
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
