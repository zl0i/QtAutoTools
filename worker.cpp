#include "worker.h"

//Worker* Worker::p_instance = nullptr;

QString Worker::qtPath()
{
    return  m_qtPath;
}

void Worker::setQtPath(QString path)
{
    settings->setValue("global/qtPath", path);
    m_qtPath = path;
    parseInstallerVersion();
    emit qtPathChanged();
}

QString Worker::compilerPath()
{
    return  m_compilerPath;
}

void Worker::setCompilerPath(QString path)
{
    settings->setValue("global/compilerPath", path);
    m_compilerPath = path;
    emit compilerPathChanged();
}

QString Worker::compilerToolPath()
{
    return  m_compilerToolePath;
}

void Worker::setCompilerToolPath(QString path)
{
    settings->setValue("global/compilerToolPath", path);
    m_compilerToolePath = path;
    emit compilerToolPathChanged();
}

void Worker::clearAllSettings()
{
    settings->clear();
    m_qtPath = "";
    m_compilerPath = "";
    m_compilerToolePath = "";
    emit qtPathChanged();
    emit compilerPathChanged();
    emit compilerToolPathChanged();
}

QFile* Worker::prepareBatFile(bool addQtPath) {
    QFile *file = new QFile("temp.bat");
    if(file->open(QIODevice::ReadWrite)) {
        if(addQtPath) {
            QString str = "set PATH="+ Worker::getInstance()->compilerPath() + "/bin;" + Worker::getInstance()->compilerToolPath() + "/bin;%PATH%\n";
            file->write(str.toLocal8Bit());
        }
        return file;
    }
    return  nullptr;
}

void Worker::removeBatFile()
{
    QFile::remove("temp.bat");
}

QString Worker::getInstallerFrameworkPath()
{

}

void Worker::parseInstallerVersion()
{
    QDir dir(m_qtPath + "/Tools/QtInstallerFramework");
    if(!dir.exists())
        return;

    QFileInfoList version = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);


}

void Worker::parseCompiler()
{

}




