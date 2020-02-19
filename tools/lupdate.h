#ifndef LUPDATE_H
#define LUPDATE_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QStandardItemModel>
#include <QJsonObject>
#include "abstracttool.h"


class Lupdate : public AbstractTool
{
    Q_OBJECT
    Q_PROPERTY(QStandardItemModel *files READ files NOTIFY filesChanged)

public:
    explicit Lupdate(QJsonObject settings, QObject *parent = nullptr);

    Q_INVOKABLE void addFile();
    Q_INVOKABLE void removeFile(int);

    Q_INVOKABLE void setFiles(int, QString);
    Q_INVOKABLE void setLanguage(QString);
    Q_INVOKABLE void setUpdateFile(QString);
    Q_INVOKABLE void setTsFileName(QString);

    Q_INVOKABLE void runLinguist();

    void configFromJson(QJsonObject) override;
    void run() override;

    QStandardItemModel *files() { return filesModel; }

private:
    QString getStringFileTs(QString file);


    QString tsFile;
    QString updateFile;
    QStringList langList;
    QString translatorList;


    QStandardItemModel *filesModel = new QStandardItemModel(this);


signals:

    void filesChanged();


};

#endif // LUPDATE_H
