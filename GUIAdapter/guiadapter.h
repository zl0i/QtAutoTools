#ifndef GUIADAPTER_H
#define GUIADAPTER_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QLocale>
#include "BaseAdapter/baseadapter.h"
#include "guitranslator.h"

class GUIAdapter : public BaseAdapter
{
    Q_OBJECT
public:
    explicit GUIAdapter(SettingsStorage *storage, QObject *parent = nullptr);

    void start() override;

protected:
    bool isRunningTask(QObject *sender = nullptr) override;

private:
    QQmlApplicationEngine engine;
    GUITranslator translator;



    QString taskName;

signals:
    void startedTask();
    void newErrorDataTask(QByteArray line);
    void newOutputDataTask( QByteArray line);
    void finishedTask(int exitCode, int exitStatus);

public slots:

    void started(QString name) override;
    void newErrorData(QString name, QByteArray line) override;
    void newOutputData(QString name, QByteArray line) override;
    void finished(QString name, int exitCode, int exitStatus) override;

    void kill() override;

    void setLanguage(QString);

};

#endif // GUIADAPTER_H
