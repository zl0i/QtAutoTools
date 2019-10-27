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
    Q_INVOKABLE void setMajorVersion(uint);
    Q_INVOKABLE void setMinorVersion(uint);
    Q_INVOKABLE void createModule();

private:    
    QString getStringVersion();

    QString path;
    uint major = 1;
    uint minor = 0;

signals:
    void error(QString str);
    void finished();

public slots:
};

#endif // QMLDIR_H
