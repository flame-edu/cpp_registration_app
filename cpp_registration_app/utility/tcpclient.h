#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    // конструктор
    explicit TcpClient(QObject *parent = nullptr);
    // деструктор
    ~TcpClient(){socket->close();}
    // подключение к серверу
    void connectToServer(const QString &hostAddress, quint16 port);
    // отправка json данных на сервер
    void sendJsonData(const QJsonObject &jsonObject);

signals:
    // подключен к серверу
    void connected();
    // отключен
    void disconnected();
    // получены json данные
    void jsonDataReceived(const QJsonObject &jsonObject);

private slots:
    // чтение входящих сообщений с сервера
    void readData();
    // процессинг сообщений json формата
    void processJsonData(const QByteArray &jsonData);

private:
    QTcpSocket *socket;
};

#endif // TCPCLIENT_H
