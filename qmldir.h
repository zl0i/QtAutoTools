#ifndef QMLDIR_H
#define QMLDIR_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStringList>


class QmlDir : public QObject
{
    Q_OBJECT
public:
    explicit QmlDir(QObject *parent = nullptr);

    Q_INVOKABLE void setPath(QString);
    Q_INVOKABLE void setVersion(int, int);
    Q_INVOKABLE void createModule();

private:
    QString path;
    QString version;

signals:
    void error(QString str);
    void finished();

public slots:
};

#endif // QMLDIR_H
