#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <iostream>
#include <cstring>
#include <Windows.h>
#include <conio.h>
#include <algorithm>
#include <QObject>

using namespace std;

class Encryption : public QObject {
    Q_OBJECT

public:
    Encryption(QObject *parent = nullptr);
    ~Encryption() {exit(1);};
    static QString encrypt(string text, int shift); // функция шифрования пароля (шифр Цезаря)
private:


};

#endif // ENCRYPTION_H

