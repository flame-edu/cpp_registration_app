#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "dbworker.h"

class TcpConnection : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnection(QObject *parent = nullptr);
    ~TcpConnection();
    bool startServer(int port);
    void writeJsonRequest(QTcpSocket *socket, const QJsonObject &jsonObject); // handles actually writing json stuff into the data stream

private:
    QTcpServer *server;
    QList<QTcpSocket *> sockets;
    DbWorker dbworker;

private slots:
    // handles new connection
    void newConnection();
    // handles the data stream from tcpsocket
    void readData();
    // handles processing data that comes from data stream
    void processJsonRequest(const QByteArray &jsonData, QTcpSocket *socket);

public slots:
    // send response to client prompting the authorization
    void sendLoginResponse(QString login, int result, QTcpSocket *socket);
    // send response to client prompting the registration
    void sendRegisterResponse(QString login, int result, QTcpSocket *socket);
    // send current user info to client
    void sendUserInfo(QString login, QTcpSocket *socket);
};

#endif // TCPCONNECTION_H
