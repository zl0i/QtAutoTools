#include "webadapter.h"

WebAdapter::WebAdapter(SettingsStorage *storage, QObject *parent) : BaseAdapter(storage, parent)
{
    server = new QWebSocketServer("QtAutoToolsServer", QWebSocketServer::NonSecureMode);

    connect(server, &QWebSocketServer::newConnection,
            this, &WebAdapter::newConnection);
    /*connect(server, &QWebSocketServer::sslErrors,
            this, &WebAdapter::onSslErrors);*/

}

void WebAdapter::start()
{
    server->listen(QHostAddress::Any, 3434);
}

void WebAdapter::newConnection()
{
    QWebSocket *pSocket = server->nextPendingConnection();

    qDebug() << "Client connected:" << pSocket->peerName() << pSocket->origin();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebAdapter::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived,
            this, &WebAdapter::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebAdapter::socketDisconnected);
}

void WebAdapter::processTextMessage(QString str)
{
    QWebSocket *socket = qobject_cast<QWebSocket*>(sender());
    socket->sendTextMessage("oooooyyeeeee");
    qDebug() << str;
}

void WebAdapter::processBinaryMessage(QByteArray arr)
{
    qDebug() << arr;
}

void WebAdapter::socketDisconnected()
{
     qDebug() << "Client disconnected";
}
