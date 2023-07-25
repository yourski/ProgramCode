#include "searchfile.h"
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <thread>
#include <mutex>

std::mutex mtx;

void searchFileRecursive(const std::string& rootPath, const std::string& targetFileName, FoundFileInfo& fileInfo, std::vector<std::thread>& threads) {
    DIR* dir = opendir(rootPath.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) {
                std::string fileName = entry->d_name;
                if (fileName == targetFileName) {
                    std::lock_guard<std::mutex> lock(mtx);
                    fileInfo.filePath = rootPath + "/" + fileName;
                    fileInfo.found = true;
                    return; // Зупинити рекурсію, якщо файл знайдено
                }
            } else if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                std::string newPath = rootPath + "/" + entry->d_name;
                if (!fileInfo.found) {
                    searchFileRecursive(newPath, targetFileName, fileInfo, threads);
                }
            }
        }
        closedir(dir);
    }
}

void searchFile(const std::string& rootPath, const std::string& targetFileName, FoundFileInfo& fileInfo, std::vector<std::thread>& threads) {
    fileInfo.found = false;
    searchFileRecursive(rootPath, targetFileName, fileInfo, threads);
}
