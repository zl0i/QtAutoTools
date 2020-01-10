#include "./builder.h"

Builder::Builder(QObject *parent) : AbstractTool(parent)
{
    m_systemBuildList.append("qmake");
    systemBuild  = "qmake";

    QDir dir(Worker::getInstance()->compilerPath() + "/mkspecs");
    m_specList = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    mkspec = m_specList.at(0);
    emit specListChanged();
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

void Builder::build()
{
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

        QFile *bat = Worker::prepareBatFile(true);

        QStringList command;

        command.append("cd " + buildDir);
        command.append(Worker::getInstance()->compilerPath() + "/bin/qmake.exe " + arguments.join(" "));
        command.append(Worker::getInstance()->compilerToolPath() + "/bin/mingw32-make.exe -f " + buildDir + "/Makefile "  + "qmake_all");
        command.append(Worker::getInstance()->compilerToolPath() + "/bin/mingw32-make.exe");
        command.append(Worker::getInstance()->compilerToolPath() + "/bin/mingw32-make.exe install");

        bat->write(command.join("\r\n").toLocal8Bit());
        bat->close();
        bat->deleteLater();
        process->start(bat->fileName());
    }
}

