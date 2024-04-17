#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "encryption.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;

signals:
    void loginAttempt(QString login, QString password);
    void gotoRegisterForm(bool isRegistered);

private slots:
    void on_registButton_clicked();
    void on_loginButton_clicked();
};

#endif // LOGINWINDOW_H
