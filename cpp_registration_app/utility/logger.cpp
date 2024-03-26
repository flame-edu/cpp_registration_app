#include "logger.h"

Logger::Logger(QObject *parent) {
    // Open the log file
    logFile.setFileName("log.txt");
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Failed to open log file!";
    }
}

Logger::~Logger() {
    logFile.close();
}

void Logger::log(const QString& message) {
    logToFile(message);
    logToConsole(message);
}

void Logger::logToFile(const QString& message) {
    if (logFile.isOpen()) {
        QTextStream out(&logFile);
        out << QDateTime::currentDateTime().toString(Qt::ISODate) << " - " << message << "\n";
        out.flush();
    } else {
        qDebug() << "Log file is not open!";
    }
}

void Logger::logToConsole(const QString& message) {
    qDebug().noquote() << message;
}
