#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include "loginwindow.h"
#include "registrationwindow.h"
#include "finishwindow.h"
#include "tcpclient.h"
#include "logger.h"
#include "encryption.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void jsonDataReceived(const QJsonObject &jsonObject);
    void swapForm(bool isRegistered);
    void loginAttempted(QString login, QString password);
    void registrationAttempted(QString login, QString password);
    void logoutPrompted();

private slots:
    void on_pushButton_clicked();

    void on_MainWindow_destroyed();

private:
    Ui::MainWindow *ui;
    LoginWindow *loginwindow;
    RegistrationWindow *registrationwindow;
    FinishWindow *finishwindow;
    TcpClient *tcpclient;
    QMessageBox msgbox;

};
#endif // MAINWINDOW_H

