#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QDebug>

class Logger : public QObject {
    Q_OBJECT

public:
    explicit Logger(QObject *parent = nullptr);
    ~Logger();
    // публичная функция, осуществляющая лог сразу в консоль и в файл
    void log(const QString& message);

private:
    // функция журналирования в файл
    void logToFile(const QString& message);
    // функция журналирования в консоль
    void logToConsole(const QString& message);
    QFile logFile;
};


#endif // LOGGER_H
