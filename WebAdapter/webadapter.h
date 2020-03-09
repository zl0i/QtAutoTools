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

    void start() override;

private:
    QWebSocketServer *server;

public slots:
    void newConnection();

    void processTextMessage(QString);
    void processBinaryMessage(QByteArray);
    void socketDisconnected();
};

#endif // WEBADAPTER_H
