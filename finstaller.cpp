#include "finstaller.h"

FInstaller::FInstaller(QObject *parent) : QObject(parent)
{
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotFinished()));
}

void FInstaller::setDeployPath(QString path) {
    m_deploypath = path;
}

void FInstaller::setInstallerPath(QString path) {
    m_installerpath = path;
}

void FInstaller::setVendorName(QString name) {
    m_vendorName = name;
}

void FInstaller::createConfig() {
    QDir configDir(m_installerpath + "/config");
    if(!configDir.exists()) {
        bool result = configDir.mkpath(m_installerpath + "/config");
        if(!result)
            return;
    }
    QFile config(m_installerpath + "/config/" +"config.xml");
    if(config.open(QIODevice::ReadWrite)) {
        const QString str = configText;
        config.write(str.toLocal8Bit());
        config.close();
    }
}

void FInstaller::createPackages() {
    QDir packagesDir(m_installerpath + "/packages/" + m_vendorName);
    if(!packagesDir.exists()) {
        bool result = packagesDir.mkpath(m_installerpath + "/packages/" + m_vendorName + "/data");
        result =  result & packagesDir.mkpath(m_installerpath + "/packages/" + m_vendorName + "/meta");
        if(!result)
            return;
    }
    QFile packages(m_installerpath + "/packages/" + m_vendorName + "/meta/package.xml");
    if(packages.open(QIODevice::ReadWrite)) {
        const QString str = packageText;
        packages.write(str.toLocal8Bit());
        packages.close();
    }
}

QFile *FInstaller::prepareBatFile() {
    QFile *file = new QFile("temp.bat");
    if(file->open(QIODevice::ReadWrite)) {
        QString str = "set PATH="+ Worker::getInstance()->compilerPath() + "/bin;" +Worker::getInstance()->compilerToolPath() + "/bin;%PATH%\n";
        file->write(str.toLocal8Bit());
        return file;
    }
    return  nullptr;
}

void FInstaller::createOffInstaller() {
    copyDir(m_deploypath, m_installerpath + "/packages/" + m_vendorName + "/data");

    QStringList arguments;
    arguments.append("-c " + m_installerpath + "/config/config.xml");
    arguments.append("-p " + m_installerpath + "/packages");
    arguments.append("-f");
    arguments.append(m_installerpath + "/Installer.exe");


    QFile *file = prepareBatFile();
    QString str = Worker::getInstance()->qtPath() + "/Tools/QtInstallerFramework/3.1/bin/binarycreator " + arguments.join(" ");
    file->write(str.toLocal8Bit());
    file->close();
    file->deleteLater();
    process->start("temp.bat");
}

void FInstaller::slotFinished() {
     QFile::remove("temp.bat");
     emit finished();
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




