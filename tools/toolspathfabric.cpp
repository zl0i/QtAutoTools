#include "toolspathfabric.h"

ToolsPathFabric::ToolsPathFabric(QJsonObject obj) : settings(obj)
{

}

QString ToolsPathFabric::profileBinPath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            settings.value("qtVersion").toString() + QDir::separator() +
            settings.value("profile").toString()+ QDir::separator() +
            "bin";
}

QString ToolsPathFabric::compilatorBinPath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            "Tools" + QDir::separator() +
            settings.value("compilator").toString() + QDir::separator() +
            "bin";
}

QString ToolsPathFabric::qmakePath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            settings.value("qtVersion").toString() + QDir::separator() +
            settings.value("profile").toString() + QDir::separator() +
            "bin" + QDir::separator() + "qmake.exe";
}

QString ToolsPathFabric::makeCompilerPath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            "Tools" + QDir::separator() +
            settings.value("compilator").toString() + QDir::separator() +
            "bin" + QDir::separator() + "mingw32-make.exe";
}

QString ToolsPathFabric::windeployqtPath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            settings.value("qtVersion").toString() + QDir::separator() +
            settings.value("profile").toString() + QDir::separator() +
            "bin" + QDir::separator() + "windeployqt.exe";
}

QString ToolsPathFabric::repogenPath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            "Tools" + QDir::separator() + "QtInstallerFramework" + QDir::separator() +
            settings.value("finstallerVersion").toString() + QDir::separator() +
            "bin" + QDir::separator() + "repogen.exe";
}

QString ToolsPathFabric::binaryCreatorPath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            "Tools" + QDir::separator() + "QtInstallerFramework" + QDir::separator() +
            settings.value("finstallerVersion").toString() + QDir::separator() +
            "bin" + QDir::separator() + "binarycreator.exe";
}

QString ToolsPathFabric::lupdatePath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            settings.value("qtVersion").toString() + QDir::separator() +
            settings.value("profile").toString() + QDir::separator() +
            "bin" + QDir::separator() + "lupdate.exe";
}

QString ToolsPathFabric::linguistPath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            settings.value("qtVersion").toString() + QDir::separator() +
            settings.value("profile").toString() + QDir::separator() +
            "bin" + QDir::separator() + "linguist.exe";
}

QString ToolsPathFabric::qmlplugindumpPath()
{
    return settings.value("qtPath").toString() + QDir::separator() +
            settings.value("qtVersion").toString() + QDir::separator() +
            settings.value("profile").toString() + QDir::separator() +
            "bin" + QDir::separator() + "qmlplugindump.exe";
}
