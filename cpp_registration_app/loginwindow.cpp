#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_registButton_clicked()
{
    emit gotoRegisterForm(false);
}

void LoginWindow::on_loginButton_clicked()
{
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    emit loginAttempt(login, password);
}

