#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "searchfile.h"

int main() {
    std::string rootPath = "."; // Поточний каталог
    std::string targetFileName = "main.cpp"; // Ім'я файлу, яке ви шукаєте

    FoundFileInfo fileInfo;
    std::vector<std::thread> threads;

    for (int i = 0; i < 8; ++i) {
        threads.emplace_back(searchFile, rootPath, targetFileName, std::ref(fileInfo), std::ref(threads));
    }

    for (auto& thread : threads) {
        thread.join(); // Дочекатися завершення всіх потоків
    }

    if (fileInfo.found) {
        std::cout << "File found: " << fileInfo.filePath << std::endl;
    } else {
        std::cout << "File not found." << std::endl;
    }

    return 0;
}
