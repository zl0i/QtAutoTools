#include "./finstaller.h"

FInstaller::FInstaller(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{

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

bool FInstaller::exec()
{
    if(path == "") {
        emit newErrorData("Path is empty.");
        return false;
    }

    QDir dir;
    dir.mkpath(path);

    installerName = config.value("Name").toString();
    emit newOutputData("Create config and packages dir\r\n");
    installerHelper = new InstallerHelper();
    installerHelper->setPath(path);
    installerHelper->createConfigAndPackages(config, packages);
    installerHelper->deleteLater();

    emit newOutputData("Create installers\r\n");

    QStringList arguments;
    QString program;

    if(isCreateMixedInstaller) {
        arguments.clear();
        arguments.append("-c");
        arguments.append(path + "/config/config.xml");
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/" + installerName + "Mixed");

        program.append(pathFabric.binaryCreatorPath() + " " + arguments.join(" ") + "\r\n");
    }

    if(isCreateOnlineInstaller) {
        arguments.clear();
        arguments.append("-n");
        arguments.append("-c");
        arguments.append(path + "/config/config.xml");
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/" + installerName + "Online");

        program.append(pathFabric.binaryCreatorPath() + " " + arguments.join(" ") + "\r\n");
    }

    if(isCreateOfflineInstaller) {
        arguments.clear();
        arguments.append("-f");
        arguments.append("-c");
        arguments.append(path + "/config/config.xml");
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/" + installerName + "Offline");

        program.append(pathFabric.binaryCreatorPath() + " " + arguments.join(" ") + "\r\n");
    }

    if(isCreateRepository) {
        arguments.clear();
        arguments.append("-p");
        arguments.append(path + "/packages");
        arguments.append(path +"/repository");
        program.append(pathFabric.repogenPath() + " " + arguments.join(" ") + "\r\n");
    }

    if(execCommand(program)) {
        emit newOutputData("Done!");
        return true;
    }
    return false;
}

void FInstaller::cancelExec()
{
    QDir(path).rmdir(path);
}
