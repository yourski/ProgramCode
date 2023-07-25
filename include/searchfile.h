#ifndef SEARCHFILE_H
#define SEARCHFILE_H

#include <string>
#include <vector>
#include <thread>
#include <mutex>

// Структура для зберігання інформації про знайдений файл
struct FoundFileInfo {
    std::string filePath;
    bool found;
};

// Функція для пошуку файлу у поточному каталозі та його підкаталогах
void searchFile(const std::string& rootPath, const std::string& targetFileName, FoundFileInfo& fileInfo, std::vector<std::thread>& threads);

#endif // SEARCHFILE_H
