#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginwindow = new LoginWindow(this);
    registrationwindow = new RegistrationWindow(this);
    finishwindow = new FinishWindow(this);
    tcpclient = new TcpClient(this);
    tcpclient->connectToServer("127.0.0.1", 5555);

    msgbox.setAttribute(Qt::WA_QuitOnClose, false);

    connect(loginwindow, &LoginWindow::gotoRegisterForm, this, &MainWindow::swapForm);
    connect(registrationwindow, &RegistrationWindow::gotoLoginForm, this, &MainWindow::swapForm);

    connect(loginwindow, &LoginWindow::loginAttempt, this, &MainWindow::loginAttempted);
    connect(registrationwindow, &RegistrationWindow::registerAttempt, this, &MainWindow::registrationAttempted);

    connect(finishwindow, &FinishWindow::logout, this, &MainWindow::logoutPrompted);

    connect(tcpclient, &TcpClient::jsonDataReceived, this, &MainWindow::jsonDataReceived);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    loginwindow->show();
    this->hide();
}

void MainWindow::jsonDataReceived(const QJsonObject &jsonObject){
    if (jsonObject.value("command").toString() == "login"){
        if (jsonObject.value("status") == "success") {
            msgbox.setText(jsonObject.value("message").toString());
            msgbox.exec();
            QJsonObject inforeq;
            inforeq["type"] = "client";
            inforeq["command"] = "info";
            inforeq["username"] = jsonObject.value("username").toString();
            tcpclient->sendJsonData(inforeq);
        } else {
            msgbox.setText(jsonObject.value("message").toString());
            msgbox.exec();
        }
    } else if (jsonObject.value("command").toString() == "register"){
        if (jsonObject.value("status") == "success"){
            msgbox.setText(jsonObject.value("message").toString());
            msgbox.exec();
            registrationwindow->hide();
            loginwindow->show();
        } else {
            msgbox.setText(jsonObject.value("message").toString());
            msgbox.exec();
        }
    } else if (jsonObject.value("command").toString() == "info"){
        int id = jsonObject.value("userid").toInt();
        QString name = jsonObject.value("name").toString();
        finishwindow = new FinishWindow(this, id, name);
        finishwindow->show();
        connect(finishwindow, &FinishWindow::logout, this, &MainWindow::logoutPrompted);
        this->thread()->usleep(100000);
        loginwindow->hide();
        registrationwindow->hide();
    }
}

void MainWindow::swapForm(bool isRegistered){
    if (isRegistered){
        loginwindow = new LoginWindow(this);
        connect(loginwindow, &LoginWindow::gotoRegisterForm, this, &MainWindow::swapForm);
        connect(loginwindow, &LoginWindow::loginAttempt, this, &MainWindow::loginAttempted);
        loginwindow->show();
        registrationwindow->hide();
    } else {
        registrationwindow = new RegistrationWindow(this);
        connect(registrationwindow, &RegistrationWindow::gotoLoginForm, this, &MainWindow::swapForm);
        connect(registrationwindow, &RegistrationWindow::registerAttempt, this, &MainWindow::registrationAttempted);
        registrationwindow->show();
        loginwindow->hide();
    }
}

void MainWindow::loginAttempted(QString login, QString password){
    QString password_cyp = Encryption::encrypt(password.toStdString(), 3);
    QJsonObject login_request;
    login_request["type"] = "client";
    login_request["command"] = "login";
    login_request["username"] = login;
    login_request["password"] = password_cyp;
    tcpclient->sendJsonData(login_request);
}

void MainWindow::registrationAttempted(QString login, QString password){
    QString password_cyp = Encryption::encrypt(password.toStdString(), 3);
    QJsonObject reg_request;
    reg_request["type"] = "client";
    reg_request["command"] = "register";
    reg_request["username"] = login;
    reg_request["password"] = password_cyp;
    tcpclient->sendJsonData(reg_request);
}

void MainWindow::logoutPrompted(){
    loginwindow = new LoginWindow(this);
    connect(loginwindow, &LoginWindow::gotoRegisterForm, this, &MainWindow::swapForm);
    connect(loginwindow, &LoginWindow::loginAttempt, this, &MainWindow::loginAttempted);
    loginwindow->show();
    finishwindow->hide();
    finishwindow->deleteLater();
}


void MainWindow::on_MainWindow_destroyed()
{

}


