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
    void log(const QString& message);

private:
    void logToFile(const QString& message);
    void logToConsole(const QString& message);
    QFile logFile;
};


#endif // LOGGER_H
