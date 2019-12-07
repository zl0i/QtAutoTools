#ifndef QMLDIR_H
#define QMLDIR_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStringList>
#include <QStandardItemModel>
#include <QHash>
#include <QJsonObject>
#include <QProcess>
#include "worker.h"


class QmlDir : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStandardItemModel *files READ files NOTIFY filesChanged)

public:
    explicit QmlDir(QObject *parent = nullptr);
    ~QmlDir();

    Q_INVOKABLE void setPath(QString);
    Q_INVOKABLE void setCreateTypes(bool);
    Q_INVOKABLE void setSupportDesigner(bool);

    Q_INVOKABLE void setTypeByIndex(int, QString);
    Q_INVOKABLE void setNameByIndex(int, QString);
    Q_INVOKABLE void setVersionByIndex(int, QString);

    QStandardItemModel *files() { return filesModel; }


    Q_INVOKABLE void createModule();

private:    
    typedef enum {
        Extension,
        Types,
        Type,
        Name,
        Version,
        File
    }TypeRoles;

    const QStringList qmlTypes = {"", "singleton", "internal"};

    QString getFileName(QString);
    QString getExtension(QString);

    QString getStringVersion();

    QString path;

    QStandardItemModel *filesModel = new QStandardItemModel(this);

    QProcess *process = new QProcess(this);

    bool createTypes = false;
    bool supportDesigner = false;

    QString getMinimumVersion();

signals:
    void started();
    void finished(int exitCode, int status);
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);

    void filesChanged();

private slots:
    void processFinished(int, QProcess::ExitStatus);
    void readChanel();
};

#endif // QMLDIR_H
