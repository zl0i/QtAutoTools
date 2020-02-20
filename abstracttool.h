#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QJsonObject>

class AbstractTool : public QObject
{
    Q_OBJECT

public:
    AbstractTool(QJsonObject obj, QObject *parent = nullptr);
    AbstractTool(QObject *parent = nullptr);

    virtual void configFromJson(QJsonObject) = 0;
    void waitFinished();
    virtual void run() = 0;


protected:
    QProcess *process;

    const QString qtPath;
    const QString profilePath;
    const QString compilerPath;

    virtual void successFinished();
    virtual void failFinished();

    QFile* prepareBatFile(bool) const;
    void removeBatFile();

signals:
    void started();
    void newOutputData(QByteArray line);
    void newErrorData(QByteArray line);
    void finished(int exitCode, int exitStatus);

public slots:
    virtual void slotFinished(int);
    void slotReadChanel();
    void kill();
};

#endif // ABSTRACTTOOL_H
