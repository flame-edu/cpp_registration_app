#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>

class DbWorker : public QObject
{
    Q_OBJECT
public:
    explicit DbWorker(QObject *parent = nullptr);
    // инициализация БД на старте работы объекта
    int initDatabase();
    // набор запросов к БД

    // функция аутентификации
    int authCheck(QString login, QString password);
    // функция регистрации
    int registrationAttempt(QString login, QString password);
    // функция получения данных о пользователе (после авторизации)
    QJsonObject getUserInfo(QString login);

private:
    QSqlDatabase db;

};

#endif // DBWORKER_H
