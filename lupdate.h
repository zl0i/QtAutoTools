#ifndef LUPDATE_H
#define LUPDATE_H

#include <QObject>
#include <QDebug>
#include "worker.h"
#include <QDir>
#include <QFile>
#include <QProcess>

class Lupdate : public QObject
{
    Q_OBJECT
public:
    explicit Lupdate(QObject *parent = nullptr);

    Q_INVOKABLE void setPath(QString);
    Q_INVOKABLE void setLanguage(QStringList);

    Q_INVOKABLE void createTs();

    Q_INVOKABLE void runLinguist();

private:
    QString getStringFileTs();
    QString getProFileName();

    QString path;
    QStringList langList;
    QProcess *process = new QProcess(this);


signals:
    void finished();
    void error();

public slots:
    void finishedProcess(int, QProcess::ExitStatus);
};

#endif // LUPDATE_H
