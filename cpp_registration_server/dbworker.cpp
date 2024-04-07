#include "dbworker.h"


DbWorker::DbWorker(QObject *parent)
    : QObject{parent}
{

}

int DbWorker::initDatabase(){
    db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("127.0.0.1");
    db.setDatabaseName("test");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setPassword("12345678");

    qDebug() << "abracadabra";

    bool db_open_res = db.open();

    if (db_open_res){
        qDebug() << "DB opened successfully";
        return 0;
    }
    else {
        qDebug() << "DB not opened";
        return 1;
    }
}

int DbWorker::authCheck(QString login, QString password_cyp){
    QSqlQuery query;
    QString query_text = "SELECT * FROM system_users WHERE (email = :email_var) AND (password = :password_var)";
    query.prepare(query_text);
    query.bindValue(":email_var", login);
    query.bindValue(":password_var", password_cyp);
    query.exec();
    qDebug() << query.lastError();
    qDebug() << query.size();
    if (query.size() > 0) {
        return 0; // login successful
    } else {
        return 1; // login failed
    }
}

int DbWorker::registrationAttempt(QString login, QString password_cyp){
    QSqlQuery query_avcheck, query_insuser; // регистрация будет требовать 2 запроса к БД
    // первый - проверка наличия таких данных регистрации в БД (конкретно username)
    // второй - вставка непосредственно данных в БД
    QString query_text_avcheck = "SELECT * FROM system_users WHERE (email = :email_var)";
    query_avcheck.prepare(query_text_avcheck);
    query_avcheck.bindValue(":email_var", login);
    query_avcheck.exec();
    qDebug() << query_avcheck.lastError();
    qDebug() << query_avcheck.size();
    if (query_avcheck.size() > 0){
        return 1; // 1 - код "пользователь уже есть"
    }
    QString query_text_insuser = "INSERT INTO system_users (email, password, displayname) VALUES (:email_var, :password_var, :name_var)";
    query_insuser.prepare(query_text_insuser);
    query_insuser.bindValue(":email_var", login);
    query_insuser.bindValue(":password_var", password_cyp);
    query_insuser.bindValue(":name_var", login); // предположим?
    query_insuser.exec();
    qDebug() << query_insuser.lastError();
    qDebug() << query_insuser.size();
    if (query_insuser.isActive()) {
        return 0; // 0 - код "пользователь добавлен успешно"
    } else
        return 2; // 2 - код "ошибка при добавлении"
}

QJsonObject DbWorker::getUserInfo(QString login){
    QJsonObject userinfo;
    QSqlQuery query;
    QString query_text = "SELECT * FROM system_users WHERE (email = :email_var)";
    query.prepare(query_text);
    query.bindValue(":email_var", login);
    query.exec();
    qDebug() << query.lastError();
    qDebug() << query.size();
    if (query.size() <= 0){
        return QJsonObject();
    } else {
        query.first();
        userinfo["userid"] = query.value("id").toInt();
        userinfo["username"] = query.value("email").toString();
        userinfo["name"] = query.value("displayname").toString();
        return userinfo;
    }
}
