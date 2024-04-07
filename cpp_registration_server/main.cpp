#include <QCoreApplication>
#include "tcpconnection.h"
#include "dbworker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpConnection tcpconnection;
    tcpconnection.startServer(5555);

    return a.exec();
}

