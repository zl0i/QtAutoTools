#include "finstaller.h"

FInstaller::FInstaller(QObject *parent) : QObject(parent)
{
    thread = new QThread(this);
    installerHelper = new InstallerHelper();    
    connect(thread, &QThread::started, installerHelper, &InstallerHelper::run);
    connect(installerHelper, &InstallerHelper::finished, this, &FInstaller::createInstallers);
    installerHelper->moveToThread(thread);

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

    installerHelper->setPath(path);
    installerHelper->setConfig(config);
    installerHelper->setPackages(packages);
    thread->start();
}

void FInstaller::setCreateMixedInstaller(bool b)
{
    isCreateMixedInstaller = b;
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
    QFile *batFile = Worker::prepareBatFile(true);
    QStringList arguments;
    if(isCreateMixedInstaller) {
        arguments.clear();
        arguments.append("-c");
        arguments.append(path + "/config/config.xml");
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/" + installerName + "Mixed");

        QString str = Worker::getInstance()->qtPath() + "/Tools/QtInstallerFramework/3.1/bin/binarycreator " + arguments.join(" ") + "\r\n";
        batFile->write(str.toLocal8Bit());
    }

    if(isCreateOnlineInstaller) {
        arguments.clear();
        arguments.append("-n");
        arguments.append("-c");
        arguments.append(path + "/config/config.xml");
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/" + installerName + "Online");

        QString str = Worker::getInstance()->qtPath() + "/Tools/QtInstallerFramework/3.1/bin/binarycreator " + arguments.join(" ") + "\r\n";
        batFile->write(str.toLocal8Bit());
    }

    if(isCreateOfflineInstaller) {
        arguments.clear();
        arguments.append("-f");
        arguments.append("-c");
        arguments.append(path + "/config/config.xml");
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/" + installerName + "Offline");

        QString str = Worker::getInstance()->qtPath() + "/Tools/QtInstallerFramework/3.1/bin/binarycreator " + arguments.join(" ") + "\r\n";
        batFile->write(str.toLocal8Bit());
    }

    if(isCreateRepository) {
        arguments.clear();
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/repository");

        QString str = Worker::getInstance()->qtPath() + "/Tools/QtInstallerFramework/3.1/bin/repogen " + arguments.join(" ") + "\r\n";
        batFile->write(str.toLocal8Bit());
    }

    batFile->close();
    batFile->deleteLater();
    process->start(batFile->fileName());
}
