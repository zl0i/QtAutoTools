#include "finstaller.h"

FInstaller::FInstaller(QObject *parent) : QProcess(parent)
{
    connect(this, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, QOverload<int>::of(&FInstaller::slotFinished));
    connect(this, &QProcess::readyRead, this, &FInstaller::slotReadChanel);
}

void FInstaller::slotReadChanel()
{
    setReadChannel(QProcess::StandardError);
    QByteArray error = readAll();
    if(!error.isEmpty())
        emit newErrorData(error);

    setReadChannel(QProcess::StandardOutput);
    QByteArray output = readAll();
    if(!output.isEmpty())
        emit newOutputData(output);

}

void FInstaller::slotFinished(int code) {
    if(code > 0) {
        emit newErrorData(readAllStandardError());
    }
    Worker::removeBatFile();
}

void FInstaller::setPath(QString path)
{
    this->path = path;
}

void FInstaller::create(QJsonObject config, QJsonArray packages)
{
    createConfig(config);
    createPackages(packages);
    QStringList arguments;
    arguments.append("-c");
    arguments.append(path + "/config/config.xml");
    arguments.append("-p");
    arguments.append(path + "/packages");
    arguments.append(path +"/" + config.value("Name").toString());

    QFile *batFile = Worker::prepareBatFile(true);
    QString str = Worker::getInstance()->qtPath() + "/Tools/QtInstallerFramework/3.1/bin/binarycreator " + arguments.join(" ");
    batFile->write(str.toLocal8Bit());
    batFile->close();
    batFile->deleteLater();
    qDebug() << str;

    start(batFile->fileName());

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


void FInstaller::createConfig(QJsonObject config)
{
    QDir configDir(path);
    configDir.mkdir("config");
    QFile configFile(configDir.path()+"/config/config.xml");
    if(configFile.open(QIODevice::ReadWrite)) {

        QXmlStreamWriter streamConfigFile(&configFile);
        streamConfigFile.setAutoFormatting(true);
        streamConfigFile.writeStartDocument();
        streamConfigFile.writeStartElement("Installer");

        QStringList keys = config.keys();
        keys.removeOne("Arguments");
        keys.removeOne("Repositories");

        for(int i = 0; i < keys.length(); i++) {
            QString key = keys.at(i);
            if(config.value(key).isString()) {
                writeXmlTextElement(&streamConfigFile, key, config.value(key).toString());
            } else if (config.value(key).isBool()) {
                if(config.value(key).toBool())
                    writeXmlTextElement(&streamConfigFile, key, "true");
                else
                    writeXmlTextElement(&streamConfigFile, key, "false");
            }
        }

        if(config.value("Arguments").toArray().size() > 0) {
            streamConfigFile.writeStartElement("RunProgramArguments");
            for (int i = 0; i < config.value("Arguments").toArray().size(); i++) {
                streamConfigFile.writeTextElement("Argument", config.value("Arguments").toArray().at(i).toString());
            }
            streamConfigFile.writeEndElement();
        }

        streamConfigFile.writeEndElement();
        streamConfigFile.writeEndDocument();
        configFile.close();
    }
}

void FInstaller::createPackages(QJsonArray packages)
{
    QDir packagesDir(path);
    packagesDir.mkdir("packages");
    packagesDir.setPath(path + "/packages");
    for (int i = 0; i < packages.size(); i++) {
        packagesDir.mkdir(packages[i].toObject().value("Name").toString());
        QDir packageDir(packagesDir.absolutePath() + "/" + packages[i].toObject().value("Name").toString());
        packageDir.mkdir("meta");
        packageDir.mkdir("data");
        copyDir(packages[i].toObject().value("packageFolder").toString(), packageDir.path() + "/data");
        QFile packageFile(packageDir.absolutePath() + "/meta/package.xml");
        if(packageFile.open(QIODevice::ReadWrite)) {
            QXmlStreamWriter streamPackageFile(&packageFile);
            streamPackageFile.setAutoFormatting(true);
            streamPackageFile.writeStartDocument();
            streamPackageFile.writeStartElement("Package");

            QJsonObject obj = packages.at(i).toObject();
            QStringList keys = obj.keys();
            keys.removeOne("UserInterfaces");
            keys.removeOne("Licenses");
            keys.removeOne("packageFolder");
            for(int i = 0; i < keys.length(); i++) {
                QString key = keys.at(i);
                if(obj.value(key).isString()) {
                    writeXmlTextElement(&streamPackageFile, key, obj.value(key).toString());
                } else if (obj.value(key).isBool()) {
                    if(obj.value(key).toBool())
                        writeXmlTextElement(&streamPackageFile, key, "true");
                    else
                        writeXmlTextElement(&streamPackageFile, key, "false");
                }
            }

            if(!obj.value("Licenses").toArray().empty()) {
                streamPackageFile.writeStartElement("Licenses");
                for (int i = 0; i < obj.value("Licenses").toArray().size(); i++) {
                    QJsonObject license = obj.value("Licenses").toArray().at(i).toObject();
                    streamPackageFile.writeStartElement("License");
                    streamPackageFile.writeAttribute("name", license.value("name").toString());
                    streamPackageFile.writeAttribute("file", license.value("file").toString());
                    streamPackageFile.writeEndElement();
                }
                streamPackageFile.writeEndElement();
            }

            if(!obj.value("UserInterfaces").toArray().empty()) {
                streamPackageFile.writeStartElement("UserInterfaces");
                for (int i = 0; i < obj.value("UserInterfaces").toArray().size(); i++) {
                    QString page = obj.value("UserInterfaces").toArray().at(i).toString();
                    streamPackageFile.writeTextElement("UserInterface", page);
                }
                streamPackageFile.writeEndElement();
            }


            streamPackageFile.writeEndElement();
            streamPackageFile.writeEndDocument();
            packageFile.close();
        }
    }
}


void FInstaller::copyDir(QString out, QString in) {
    QDir outDir(out);
    if(!outDir.exists())
        return;

    QStringList dirList = outDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for(int i = 0; i < dirList.length(); ++i) {
        QString in_path = in + QDir::separator() + dirList[i];
        outDir.mkpath(in_path);
        copyDir(out+ QDir::separator() + dirList[i], in_path);
    }

    QStringList fileList = outDir.entryList(QDir::Files);
    for(int i = 0; i < fileList.length(); ++i) {
        QFile::copy(out + QDir::separator() + fileList.at(i), in + QDir::separator() + fileList.at(i));
    }
}

void FInstaller::writeXmlTextElement(QXmlStreamWriter *stream, QString key, QString value)
{
    if(value.length() > 0) {
        stream->writeTextElement(key, value);
    }
}




