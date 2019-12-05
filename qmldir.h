#ifndef QMLDIR_H
#define QMLDIR_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStringList>
#include <QStandardItemModel>


class QmlDir : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStandardItemModel *files READ files NOTIFY filesChanged)

public:
    explicit QmlDir(QObject *parent = nullptr);

    Q_INVOKABLE void setPath(QString);
    Q_INVOKABLE void setCreateTypes(bool);


    QStandardItemModel *files() { return filesModel; }

    //Q_INVOKABLE void setMajorVersion(uint);
    //Q_INVOKABLE void setMinorVersion(uint);

    Q_INVOKABLE void createQmlDir();

private:    
    QString getStringVersion();

    QString path;
    QStandardItemModel *filesModel = new QStandardItemModel(this);
    bool createTypes = false;

signals:
    void error(QString str);
    void finished();

    void filesChanged();
public slots:
};

#endif // QMLDIR_H
