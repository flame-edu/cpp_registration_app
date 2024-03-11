#include "encryption.h"

QString Encryption::encrypt(string text, int shift) {
    QString result = "";

    // Перебираем все символы в строке
    for (int i = 0; i < text.length(); ++i) {
        // Шифруем только английские буквы
        if (isalpha(text[i])) {
            // Определяем новую позицию символа после сдвига
            int newPos = (int)text[i] + shift;

            // Проверяем, не выходит ли новая позиция за пределы кодовых значений букв a-z или A-Z
            if (isupper(text[i])) {
                if (newPos > (int)'Z') {
                    newPos = ((newPos - (int)'A') % 26) + (int)'A';
                }
            }
            else {
                if (newPos > (int)'z') {
                    newPos = ((newPos - (int)'a') % 26) + (int)'a';
                }
            }

            // Добавляем зашифрованный символ к результату
            result += (char)newPos;
        }
        else {
            result += text[i];
        }
    }

    return result;
}
