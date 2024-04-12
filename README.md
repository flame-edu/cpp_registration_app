Simple authorization app written in C++ with Qt 6.2.

Project structure:

- Client - GUI application with auth/registration forms that connects to Server via QTcpSocket, sends login/register requests in JSON format and gives user access to a FinishWindow on auth success.

- Server - console application that handles requests from Client, based on PostgreSQL and QTcpServer.
