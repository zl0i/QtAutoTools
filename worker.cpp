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






