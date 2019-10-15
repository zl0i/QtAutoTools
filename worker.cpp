#include "worker.h"

Worker* Worker::p_instance = nullptr;

QString Worker::qtPath()
{
    return  m_qtPath;
}

void Worker::setQtPath(QString path)
{
    settings->setValue("global/qtpath", path);
    m_qtPath = path;
    emit qtPathChanged();
}

QString Worker::compl1Path()
{
    return  m_compl1Path;
}

void Worker::setCompl1Path(QString path)
{
    settings->setValue("global/compl1Path", path);
    m_compl1Path = path;
    emit compl1PathChanged();
}

QString Worker::compl2Path()
{
    return  m_compl2Path;
}

void Worker::setCompl2Path(QString path)
{
    settings->setValue("global/compl2Path", path);
    m_compl2Path = path;
    emit compl2PathChanged();
}

void Worker::clearAllSettings()
{
    settings->clear();
}




