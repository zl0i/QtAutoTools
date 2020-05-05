#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThreadPool>
#include "abstracttool.h"

class Builder : public AbstractTool
{
    Q_OBJECT
    Q_PROPERTY(QStringList specList READ specList NOTIFY specListChanged)
    Q_PROPERTY(QStringList systemBuildList READ systemBuildList NOTIFY systemBuildListChanged)

public:
    explicit Builder(QJsonObject settings, QObject *parent = nullptr);

    QStringList specList() { return  m_specList; }
    QStringList systemBuildList() { return  m_systemBuildList; }

    void configFromJson(QJsonObject) override;
    bool exec() override;
    void cancelExec() override;

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
