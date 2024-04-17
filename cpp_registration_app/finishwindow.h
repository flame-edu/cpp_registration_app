#ifndef FINISHWINDOW_H
#define FINISHWINDOW_H

#include <QDialog>

namespace Ui {
class FinishWindow;
}

class FinishWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FinishWindow(QWidget *parent = nullptr, int user_id = 0, QString user_name = "");
    ~FinishWindow();


signals:
    void logout();

private slots:
    void on_FinishWindow_destroyed();

    void on_loginButton_clicked();

private:
    Ui::FinishWindow *ui;
};

#endif // FINISHWINDOW_H
