#ifndef LUPDATE_H
#define LUPDATE_H

#include <QObject>
#include <QDebug>
#include "worker.h"
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QStandardItemModel>


class Lupdate : public QProcess
{
    Q_OBJECT
    Q_PROPERTY(QStandardItemModel *files READ files NOTIFY filesChanged)

public:
    explicit Lupdate(QObject *parent = nullptr);

     Q_INVOKABLE void addFile();
    Q_INVOKABLE void removeFile(int);

    Q_INVOKABLE void setFile(int, QString);
    Q_INVOKABLE void setLanguage(QString);

    Q_INVOKABLE void createTs();
    Q_INVOKABLE void runLinguist();

    QStandardItemModel *files() { return filesModel; }

private:
    QString getStringFileTs(QString file);

    QString path;
    QStringList langList;
    QStringList translatorList;

    QStandardItemModel *filesModel = new QStandardItemModel(this);


signals:
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);

    void filesChanged();

public slots:    
    void slotFinished(int);
    void slotReadChanel();

};

#endif // LUPDATE_H
