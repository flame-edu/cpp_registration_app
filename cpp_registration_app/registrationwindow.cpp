#include "registrationwindow.h"
#include "ui_registrationwindow.h"

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_loginButton_clicked()
{
    emit gotoLoginForm(true);
}


void RegistrationWindow::on_registButton_clicked()
{
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit_1->text();
    if (ui->passwordEdit_1->text() != ui->lineEdit_3->text()){
        return;
    } else {
        emit registerAttempt(login, password);
    }
}

