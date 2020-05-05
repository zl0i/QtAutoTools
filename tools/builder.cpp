#include "./builder.h"

Builder::Builder(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{
    m_systemBuildList.append("qmake");
    systemBuild  = "qmake";
}

void Builder::configFromJson(QJsonObject obj) {
    proFile = obj.value("proFile").toString();
    systemBuild = obj.value("systemBuild").toString();
    mkspec = obj.value("mkspec").toString();
    buildDir = obj.value("buildDir").toString();
    addConfigure = obj.value("configure").toString();
}

bool Builder::exec() {
    QStringList arguments;

    if(proFile.isEmpty()) {
        emit newErrorData("Profile field is empty.");
        return false;
    }

    if(buildDir.isEmpty()) {
        emit newErrorData("Build dir field is empty.");
        return false;
    }

    QDir(buildDir).mkpath(buildDir);

    if(systemBuild == "qmake") {
        arguments.append(proFile);

        arguments.append("-spec");
        arguments.append(mkspec);

        QStringList config = addConfigure.split(" ");
        for(int i = 0; i < config.size(); ++i) {
            arguments.append("\"CONFIG+=" + config.at(i) + "\"");
        }

        QStringList command;

        command.append("cd " + buildDir);
        command.append(pathFabric.qmakePath() + " " + arguments.join(" "));
        command.append(pathFabric.makeCompilerPath() + " -f " + buildDir + "/Makefile "  + "qmake_all");
        command.append(pathFabric.makeCompilerPath() + " -j " + QString::number(QThreadPool::globalInstance()->maxThreadCount()));
        command.append(pathFabric.makeCompilerPath() + " install");

        if(execCommand(command.join("\r\n"))) {
            return true;
        } else {
            emit newErrorData("");
            return false;
        }
    }
    return false;

}

void Builder::cancelExec()
{
    QDir(buildDir).rmdir(buildDir);
}
