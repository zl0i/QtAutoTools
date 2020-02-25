#include "./finstaller.h"

FInstaller::FInstaller(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{

}

void FInstaller::setPath(QString path)
{
    this->path = path;
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

void FInstaller::configFromJson(QJsonObject obj) {
    path = obj.value("path").toString();
    config = obj.value("config").toObject();
    packages = obj.value("packages").toArray();
    isCreateMixedInstaller = obj.value("isCreateMixedInstaller").toBool();
    isCreateOfflineInstaller = obj.value("isCreateOfflineInstaller").toBool();
    isCreateOnlineInstaller = obj.value("isCreateOnlineInstaller").toBool();
    isCreateRepository = obj.value("isCreateRepository").toBool();
}

void FInstaller::run()
{
    if(path == "")
        return;

    emit started();
    installerName = config.value("Name").toString();
    emit newOutputData("Create config and packages dir\r\n");
    installerHelper = new InstallerHelper();
    installerHelper->setPath(path);
    installerHelper->createConfigAndPackages(config, packages);
    installerHelper->deleteLater();

    emit newOutputData("Create installers\r\n");
    QFile *batFile = prepareBatFile(true);
    QStringList arguments;
    if(isCreateMixedInstaller) {
        arguments.clear();
        arguments.append("-c");
        arguments.append(path + "/config/config.xml");
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/" + installerName + "Mixed");

        QString str = qtPath + "/Tools/QtInstallerFramework/3.2/bin/binarycreator " + arguments.join(" ") + "\r\n";
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

        QString str = qtPath + "/Tools/QtInstallerFramework/3.2/bin/binarycreator " + arguments.join(" ") + "\r\n";
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

        QString str = qtPath + "/Tools/QtInstallerFramework/3.2/bin/binarycreator " + arguments.join(" ") + "\r\n";
        batFile->write(str.toLocal8Bit());
    }

    if(isCreateRepository) {
        arguments.clear();
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/repository");

        QString str = qtPath + "/Tools/QtInstallerFramework/3.2/bin/repogen " + arguments.join(" ") + "\r\n";
        batFile->write(str.toLocal8Bit());
    }

    batFile->close();
    batFile->deleteLater();
    process->start(batFile->fileName());
}
