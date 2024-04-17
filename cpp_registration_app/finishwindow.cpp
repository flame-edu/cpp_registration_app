#include "finishwindow.h"
#include "ui_finishwindow.h"

FinishWindow::FinishWindow(QWidget *parent, int user_id, QString user_name) :
    QDialog(parent),
    ui(new Ui::FinishWindow)
{
    ui->setupUi(this);
    ui->user_id->setText(QString::number(user_id));
    ui->user_name->setText(user_name);
}

FinishWindow::~FinishWindow()
{
    delete ui;
}


void FinishWindow::on_FinishWindow_destroyed()
{

}


void FinishWindow::on_loginButton_clicked()
{
    emit logout();
}

