#include "finstaller.h"

FInstaller::FInstaller(QObject *parent) : QProcess(parent)
{
    //connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotFinished()));
}

void FInstaller::setPath(QString path)
{
    this->path = path;
}

void FInstaller::create(QJsonObject config, QJsonArray packages)
{
    createConfig(config);
    createPackages(packages);

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

void FInstaller::slotFinished()
{

}

void FInstaller::createConfig(QJsonObject config)
{
    qDebug() << config;
}

void FInstaller::createPackages(QJsonArray packages)
{
    qDebug() << packages;
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




