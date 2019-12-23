#include "installerhelper.h"

InstallerHelper::InstallerHelper(QObject *parent) : QObject(parent)
{

}

void InstallerHelper::createConfigAndPackages(QString path, QJsonObject config, QJsonArray packages)
{
    this->path = path;
    createConfig(config);
    createPackages(packages);
    emit finished();
}

void InstallerHelper::setPath(QString path)
{
    this->path = path;
}


void InstallerHelper::createConfig(QJsonObject config)
{
    QDir configDir(path);
    configDir.mkdir("config");
    QFile configFile(configDir.path()+"/config/config.xml");
    if(configFile.open(QIODevice::ReadWrite)) {
        writeConfigFile(&configFile, config);
        configFile.close();
    }
}

void InstallerHelper::createPackages(QJsonArray packages)
{
    QDir packagesDir(path);
    packagesDir.mkdir("packages");
    packagesDir.setPath(path + "/packages");
    for (int i = 0; i < packages.size(); i++) {
        QJsonObject package = packages[i].toObject();

        QString packagePathDir = createDirPackage(packagesDir.absolutePath(), package.value("Name").toString());
        copyDir(package.value("packageFolder").toString(), packagePathDir + "/data");

        QFile packageFile(packagePathDir + "/meta/package.xml");
        if(packageFile.open(QIODevice::ReadWrite)) {
            writePackageFile(&packageFile, packages.at(i).toObject());
            packageFile.close();
        }
    }
}

void InstallerHelper::writeConfigFile(QFile *configFile, QJsonObject config)
{
    QXmlStreamWriter streamConfigFile(configFile);
    streamConfigFile.setAutoFormatting(true);
    streamConfigFile.writeStartDocument();
    streamConfigFile.writeStartElement("Installer");

    QStringList keys = config.keys();
    keys.removeOne("Arguments");
    keys.removeOne("RemoteRepositories");

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

    if(config.value("RemoteRepositories").toArray().size() > 0) {
        streamConfigFile.writeStartElement("RemoteRepositories");
        QJsonArray remoteRepositories = config.value("RemoteRepositories").toArray();
        for (int i = 0; i < remoteRepositories.size(); i++) {
            streamConfigFile.writeStartElement("Repository");
            QJsonObject repository = remoteRepositories.at(i).toObject();

            writeXmlTextElement(&streamConfigFile, "Url", repository.value("Url").toString());
            writeXmlTextElement(&streamConfigFile, "Username", repository.value("Username").toString());
            writeXmlTextElement(&streamConfigFile, "Password", repository.value("Password").toString());
            writeXmlTextElement(&streamConfigFile, "DisplayName", repository.value("DisplayName").toString());
            if(repository.value("Enabled").toBool())
                writeXmlTextElement(&streamConfigFile, "Enabled", "1");
            else
                writeXmlTextElement(&streamConfigFile, "Enabled", "0");

            streamConfigFile.writeEndElement();
        }
        streamConfigFile.writeEndElement();
    }

    streamConfigFile.writeEndElement();
    streamConfigFile.writeEndDocument();
}

QString InstallerHelper::createDirPackage(QString path, QString name)
{
    QDir packagesDir(path);
    packagesDir.mkdir(name);
    QDir packageDir(packagesDir.absolutePath() + "/" + name);
    packageDir.mkdir("meta");
    packageDir.mkdir("data");
    return  packageDir.absolutePath();
}

void InstallerHelper::writePackageFile(QFile *packageFile, QJsonObject obj)
{
    QXmlStreamWriter streamPackageFile(packageFile);
    streamPackageFile.setAutoFormatting(true);
    streamPackageFile.writeStartDocument();
    streamPackageFile.writeStartElement("Package");

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
}


void InstallerHelper::copyDir(QString out, QString in) {
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

void InstallerHelper::writeXmlTextElement(QXmlStreamWriter *stream, QString key, QString value)
{
    if(value.length() > 0) {
        stream->writeTextElement(key, value);
    }
}
