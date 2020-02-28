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

void Builder::run() {
    QStringList arguments;
    if(proFile.isEmpty() || buildDir.isEmpty())
        return;

    emit started();

    if(systemBuild == "qmake") {
        arguments.append(proFile);

        arguments.append("-spec");
        arguments.append(mkspec);

        QStringList config = addConfigure.split(" ");
        for(int i = 0; i < config.size(); ++i) {
            arguments.append("\"CONFIG+=" + config.at(i) + "\"");
        }

        QFile *bat = prepareBatFile(true);

        QStringList command;

        command.append("cd " + buildDir);
        command.append(profilePath + "/bin/qmake.exe " + arguments.join(" "));
        command.append(compilerPath + "/bin/mingw32-make.exe -f " + buildDir + "/Makefile "  + "qmake_all");
        command.append(compilerPath + "/bin/mingw32-make.exe");
        command.append(compilerPath + "/bin/mingw32-make.exe install");

        bat->write(command.join("\r\n").toLocal8Bit());
        bat->close();
        bat->deleteLater();
        process->start(bat->fileName());
    }
}

void Builder::setProFile(QString path)
{
    proFile = path;
}

void Builder::setSystemBuild(QString system)
{
    systemBuild = system;
}

void Builder::setBuildDir(QString path)
{
    buildDir = path;
}

void Builder::setMkSpec(QString spec)
{
    mkspec = spec;
}

void Builder::setConfigure(QString configure)
{
    addConfigure = configure;
}

