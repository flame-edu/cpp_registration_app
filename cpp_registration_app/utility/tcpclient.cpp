#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent)
    : QObject{parent}
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &TcpClient::connected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::readData);
}

void TcpClient::connectToServer(const QString &hostAddress, quint16 port)
{
    socket->connectToHost(hostAddress, port);
}

void TcpClient::sendJsonData(const QJsonObject &jsonObject){
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();
    socket->write(jsonData);
    socket->flush();
}

void TcpClient::readData(){
    while (socket->bytesAvailable() > 0) {
        QByteArray data = socket->readAll();
        processJsonData(data);
    }
}

void TcpClient::processJsonData(const QByteArray &jsonData){
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON:" << error.errorString();
        return;
    }

    if (!jsonDoc.isObject()) {
        qDebug() << "JSON data is not an object.";
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();
    emit jsonDataReceived(jsonObject); // отправка сигнала о получении json данных
}

