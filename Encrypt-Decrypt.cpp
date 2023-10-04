#include <iostream>
#include <fstream>
#include <vector>

const std::string g_key = "12345678901234567890123456789012"; // 256-битный ключ (32 байта)
const std::string g_iv = "abcdefghijklmnop"; // 128-битный вектор инициализации (16 байт)
const int BLOCK_SIZE = 16; // размер блока для AES-256 (в байтах)

void AES_Encrypt(const std::vector<uint8_t>& input, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, std::vector<uint8_t>& output)
{
    for (size_t i = 0; i < input.size(); ++i) {
        output.push_back(input[i] ^ key[i % key.size()]);
    }
}

void AES_Decrypt(const std::vector<uint8_t>& input, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv, std::vector<uint8_t>& output)
{
    for (size_t i = 0; i < input.size(); ++i) {
        output.push_back(input[i] ^ key[i % key.size()]);
    }
}

void EncryptDecryptFile(const std::string& inputFile, const std::string& outputFile, bool encrypt)
{
    std::ifstream ifs(inputFile, std::ios::binary);
    std::ofstream ofs(outputFile, std::ios::binary);

    if (!ifs || !ofs) {
        std::cout << "Не удалось открыть файлы!" << std::endl;
        return;
    }

    std::vector<uint8_t> key(g_key.begin(), g_key.end());
    std::vector<uint8_t> iv(g_iv.begin(), g_iv.end());

    std::vector<uint8_t> inputBuffer(BLOCK_SIZE);
    std::vector<uint8_t> outputBuffer;

    while (ifs.read(reinterpret_cast<char*>(inputBuffer.data()), BLOCK_SIZE)) {
        if (encrypt) {
            AES_Encrypt(inputBuffer, key, iv, outputBuffer);
        } else {
            AES_Decrypt(inputBuffer, key, iv, outputBuffer);
        }
        ofs.write(reinterpret_cast<const char*>(outputBuffer.data()), outputBuffer.size());
        outputBuffer.clear();
    }

    ifs.close();
    ofs.close();

    if (encrypt) {
        std::cout << "Шифрование файла завершено!" << std::endl;
    } else {
        std::cout << "Дешифрование файла завершено!" << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    std::string inputFile = "input.txt";
    std::string encryptedFile = "encrypted.bin";
    std::string decryptedFile = "decrypted.bin";

    EncryptDecryptFile(inputFile, encryptedFile, true);
    EncryptDecryptFile(encryptedFile, decryptedFile, false);

    size_t lastDotIndex = decryptedFile.find_last_of('.');
    std::string renamedFile = decryptedFile.substr(0, lastDotIndex) + ".bin";
    std::rename(decryptedFile.c_str(), renamedFile.c_str());
    return 0;
}

