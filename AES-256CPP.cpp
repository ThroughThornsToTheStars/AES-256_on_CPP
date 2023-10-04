#include <iostream>
#include <fstream>
#include <vector>

int main() {
    int result = system("g++ -o TextToBin TextToBin.cpp"); 
    if (result == 0) {
        system("TextToBin.exe");
    }
    int result1 = system("g++ -o Encrypt-Decrypt Encrypt-Decrypt.cpp"); 
    if (result1 == 0) {
        system("Encrypt-Decrypt.exe");
    }

    // Открываем бинарный файл для чтения
    std::ifstream inputFile("decrypted.bin", std::ios::binary);

    if (!inputFile) {
        std::cerr << "Failed to open input binary file" << std::endl;
        return 1;
    }

    // Создаем файл для записи текстовых данных
    std::ofstream outputFile("output.txt");

    if (!outputFile) {
        std::cerr << "Failed to create output file." << std::endl;
        return 1;
    }

    // Читаем биты из бинарного файла и преобразуем их в символы текста
    char byte;
    std::string textBuffer;

    while (inputFile.get(byte)) {
        textBuffer += byte;
        if (textBuffer.size() == 8) {
            char character = static_cast<char>(std::stoi(textBuffer, nullptr, 2));
            outputFile << character;
            textBuffer.clear();
        }
    }

    // Закрываем файлы
    inputFile.close();
    outputFile.close();

    std::cout << "Conversion completed successfully." << std::endl;

    std::string file_name = "input.bin" ;
    remove(file_name.c_str()) ;

    file_name = "TextToBin.exe" ;
    remove(file_name.c_str()) ;

    file_name = "Encrypt-Decrypt.exe" ;
    remove(file_name.c_str()) ;

    return 0;
}