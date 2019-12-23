#include "finstaller.h"

FInstaller::FInstaller(QObject *parent) : QObject(parent)
{
    thread = new QThread(this);
    installerHelper = new InstallerHelper();
    installerHelper->moveToThread(thread);
    connect(installerHelper, &InstallerHelper::finished, this, &FInstaller::createInstallers);

    process = new QProcess(this);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, QOverload<int>::of(&FInstaller::slotFinished));
    connect(process, &QProcess::readyRead, this, &FInstaller::slotReadChanel);
}

void FInstaller::slotReadChanel()
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

void FInstaller::slotFinished(int code) {
    if(code > 0) {
        emit newErrorData(process->readAllStandardError());
    }
    Worker::removeBatFile();
    emit newOutputData("Done!\r\n");
    emit finished(process->exitCode(), process->exitStatus());
}

void FInstaller::setPath(QString path)
{
    this->path = path;
}

void FInstaller::create(QJsonObject config, QJsonArray packages)
{    
    if(path == "")
        return;

    emit started();
    installerName = config.value("Name").toString();
    emit newOutputData("Create config and packages dir\r\n");
    installerHelper->createConfigAndPackages(path, config, packages);
}


void FInstaller::setCreateOfflineInstaller(bool b)
{
    isCreateOfflineInstaller = b;
}

void FInstaller::setCreateOnlineInstaller(bool b )
{
    isCreateOnlineInstaller = b;
}

void FInstaller::setCreateRepo(bool b)
{
    isCreateRepository = b;
}

void FInstaller::kill()
{
    process->kill();
}

void FInstaller::createInstallers()
{
    emit newOutputData("Create installers\r\n");
    QStringList arguments;
    arguments.append("-c");
    arguments.append(path + "/config/config.xml");
    arguments.append("-p");
    arguments.append(path + "/packages");
    arguments.append(path +"/" + installerName);

    QFile *batFile = Worker::prepareBatFile(true);
    QString str = Worker::getInstance()->qtPath() + "/Tools/QtInstallerFramework/3.1/bin/binarycreator " + arguments.join(" ");
    batFile->write(str.toLocal8Bit());
    batFile->close();
    batFile->deleteLater();
    qDebug() << str;

    process->start(batFile->fileName());
}







