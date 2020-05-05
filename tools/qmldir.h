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
#include <QJsonArray>
#include <QProcess>
#include <QJsonObject>
#include "abstracttool.h"

class QmlDir : public AbstractTool
{
    Q_OBJECT
    Q_PROPERTY(QStandardItemModel *files READ files NOTIFY filesChanged)

public:
    explicit QmlDir(QJsonObject settings, QObject *parent = nullptr);  

    QStandardItemModel *files() { return filesModel; }

    void configFromJson(QJsonObject) override;
    bool exec() override;
    void cancelExec() override;

private:    
    typedef enum {
        Type = Qt::UserRole + 1,
        Name,
        Version,
        File
    }TypeRoles;    

    QString getFileName(QString);
    QString getExtension(QString);
    QString buildString(QModelIndex);
    QString getStringVersion();

    QString path;

    QStandardItemModel *filesModel = new QStandardItemModel(this);

    bool createTypes = false;
    bool supportDesigner = false;

    QString getMinimumVersion();    

signals:
    void filesChanged();


public slots:

};

#endif // QMLDIR_H
