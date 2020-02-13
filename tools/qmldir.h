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
#include <QJsonObject>
#include "abstracttool.h"
#include "worker.h"


class QmlDir : public AbstractTool
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

    void configFromJson(QJsonObject) override;
    void run() override;

private:    
    typedef enum {
        Extension = Qt::UserRole+1,
        Types,
        Type,
        Name,
        Version,
        File
    }TypeRoles;

    const QStringList qmlTypes = {"", "singleton", "internal"};

    QString getFileName(QString);
    QString getExtension(QString);
    QString buildString(QModelIndex);
    QString getStringVersion();

    QString path;

    QStandardItemModel *filesModel = new QStandardItemModel(this);

    QProcess *process = new QProcess(this);

    bool createTypes = false;
    bool supportDesigner = false;

    QString getMinimumVersion();

signals:
    void filesChanged();

public slots:
    void slotFinished(int) override;



};

#endif // QMLDIR_H
