#include <iostream>
#include "src/filesearch_algo.h"

int main(int argc, char*argv[]) {
    std::string filepath;
    std::cout << "Введите полный путь до файла:" << std::endl;
    std::cin >> filepath;
    bool is_fast{false};
    if (argc > 1 && argv[1][0] == 'f' && argv[1][1] == 'a' && argv[1][2] == 's' && argv[1][3] == 't') {
        is_fast = true;
    }
    filesearch_algo searcher(is_fast);
    searcher.file_read(filepath);
    std::string input;
    std::cout << "Введите паттерн для поиска в тексте:" << std::endl;
    while (std::cin >> input) {
        ssize_t result = searcher.find_substring(input);
        if (result == -1) {
            std::cout <<  "Вхождений не найдено." << std::endl;
        } else {
            std::cout << "Позиция первого вхождения в тексте - " << result << std::endl;
        }
        std::cout << "Введите паттерн для поиска в тексте:" << std::endl;
    }
    return 0;
}
