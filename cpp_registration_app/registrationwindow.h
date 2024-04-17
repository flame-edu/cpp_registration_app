#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>
#include "encryption.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RegistrationWindow; }
QT_END_NAMESPACE

class RegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

signals:
    void registerAttempt(QString login, QString password); // попытка регистрации
    void gotoLoginForm(bool isRegistered);

private slots:
    void on_loginButton_clicked();

    void on_registButton_clicked();

private:
    Ui::RegistrationWindow *ui;
};

#endif // REGISTRATIONWINDOW_H
