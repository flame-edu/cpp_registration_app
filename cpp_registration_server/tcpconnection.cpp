#include "tcpconnection.h"

TcpConnection::TcpConnection(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &TcpConnection::newConnection);
    dbworker.initDatabase();
}

TcpConnection::~TcpConnection(){
    server->close();
}

bool TcpConnection::startServer(int port){
    if (!server->listen(QHostAddress::Any, port)){
        qDebug() << "Server didn't start " << server->errorString();
        return false;
    }
    qDebug() << "Server listening on port " << port;
    return true;
}

void TcpConnection::writeJsonRequest(QTcpSocket *socket, const QJsonObject &jsonObject){
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();
    socket->write(jsonData);
    socket->flush();
}

void TcpConnection::newConnection(){
    while (server->hasPendingConnections()) {
        QTcpSocket *socket = server->nextPendingConnection();
        if (socket) {
            connect(socket, &QTcpSocket::readyRead, this, &TcpConnection::readData);
            connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
            sockets.append(socket);
            qDebug() << "New connection from:" << socket->peerAddress().toString();
        }
    }
}

void TcpConnection::readData(){
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket)
        return;
    while (socket->bytesAvailable() > 0) {
        QByteArray data = socket->readAll();
        processJsonRequest(data, socket);
    }
}

void TcpConnection::processJsonRequest(const QByteArray &jsonData, QTcpSocket *socket){
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
    // actual data processing
    qDebug() << "Received JSON data:" << jsonObject;
    bool check1 = jsonObject.contains("type");
    bool check2 = jsonObject.contains("command");
    bool check3 = (jsonObject.value("type") == "client");
    // if all fine then do some serverside Magik :trademark:
    if ((check1 && check2 && check3) && jsonObject["command"] == "login"){
        QString username = jsonObject.value("username").toString();
        QString password = jsonObject.value("password").toString();
        int login_res = dbworker.authCheck(username, password);
        qDebug() << "Processed login request";
        sendLoginResponse(username, login_res, socket);
    } else if ((check1 && check2 && check3) && jsonObject["command"] == "register"){
        QString username = jsonObject.value("username").toString();
        QString password = jsonObject.value("password").toString();
        int reg_res = dbworker.registrationAttempt(username, password);
        sendRegisterResponse(username, reg_res, socket);
    } else if ((check1 && check2 && check3) && jsonObject["command"] == "info"){
        QString username = jsonObject.value("username").toString();
        sendUserInfo(username, socket);
    }
}

void TcpConnection::sendLoginResponse(QString login, int result, QTcpSocket *socket){
    QJsonObject response;
    response["type"] = "server";
    response["command"] = "login";
    response["username"] = login;
    response["status"] = (result == 0) ? "success" : "failure";
    response["message"] = (result == 0) ? "You successfully logged in!" : "Invalid username or password, check and try again";
    writeJsonRequest(socket, response);
}

void TcpConnection::sendRegisterResponse(QString login, int result, QTcpSocket *socket){
    QJsonObject response;
    response["type"] = "server";
    response["command"] = "register";
    response["username"] = login;
    response["status"] = (result == 0) ? "success" : "failure";
    switch(result){
        case 0: response["message"] = "You successfully registered!"; break;
        case 1: response["message"] = "The username is already in use"; break;
        case 2: response["message"] = "Internal DB error occured"; break;
        case 3: response["message"] = "Unknown error"; break;
    }
    writeJsonRequest(socket, response);
}

void TcpConnection::sendUserInfo(QString login, QTcpSocket *socket){
    QJsonObject response;
    response["type"] = "server";
    response["command"] = "info";
    response["username"] = login;
    QJsonObject info = dbworker.getUserInfo(login);
    if (info.contains("name")){
        response["name"] = info["name"];
        response["userid"] = info["userid"];
        writeJsonRequest(socket, response);
    }
}
