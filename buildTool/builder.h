#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include "abstracttool.h"
#include "worker.h"

class Builder : public AbstractTool
{
    Q_OBJECT
    Q_PROPERTY(QStringList specList READ specList NOTIFY specListChanged)
    Q_PROPERTY(QStringList systemBuildList READ systemBuildList NOTIFY systemBuildListChanged)

public:
    explicit Builder(QObject *parent = nullptr);

    QStringList specList() { return  m_specList; }
    QStringList systemBuildList() { return  m_systemBuildList; }

    Q_INVOKABLE void setProFile(QString);
    Q_INVOKABLE void setSystemBuild(QString);
    Q_INVOKABLE void setBuildDir(QString);
    Q_INVOKABLE void setMkSpec(QString);
    Q_INVOKABLE void setConfigure(QString);

    Q_INVOKABLE void build();

private:
    QStringList m_specList;
    QStringList m_systemBuildList;

    QString proFile;
    QString systemBuild;
    QString buildDir;
    QString mkspec;
    QString addConfigure;

signals:
    void specListChanged();
    void systemBuildListChanged();

public slots:


};

#endif // BUILDER_H
