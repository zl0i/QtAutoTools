#ifndef WEBADAPTER_H
#define WEBADAPTER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include "BaseAdapter/baseadapter.h"

class WebAdapter : public BaseAdapter
{
    Q_OBJECT
public:
    explicit WebAdapter(SettingsStorage *storage, QObject *parent = nullptr);

    bool start() override;

private:
    QWebSocketServer *server;

    QJsonObject getUserSettings(QObject *sender = nullptr) override;
    bool isRunningTask(QObject *sender = nullptr) override;

public slots:
    void started(QString name) override;
    void newErrorData(QString name, QByteArray line) override;
    void newOutputData(QString name, QByteArray line) override;
    void finished(QString name, int exitCode, int exitStatus) override;

    void newConnection();

    void processTextMessage(QString);
    void processBinaryMessage(QByteArray);
    void socketDisconnected();

    void kill() override;
};

#endif // WEBADAPTER_H
