//
// Created by Ilya on 31.03.2022.
//

#ifndef TASK211_FILESEARCH_ALGO_H
#define TASK211_FILESEARCH_ALGO_H


#include "string"
#include <queue>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include "SuffixAuto.h"

class filesearch_algo {
public:
    filesearch_algo(bool search_method); // Конструктор алгоритмического класса. Передаваемый search_method определяет алгоритм поиска подстроки.

    filesearch_algo(filesearch_algo&) = delete;
    filesearch_algo& operator=(filesearch_algo&) = delete;

    filesearch_algo(filesearch_algo&&) = delete;
    filesearch_algo& operator=(filesearch_algo&&) = delete;

    void file_read(std::string& filepath); // Передача пути к файлу. В случае "быстрого" поиска также препроцессинг данных.

    ssize_t find_substring(const std::string& substr); // Поиск подстроки, возвращает -1 в случае отсутствия вхождений.

private:
    ssize_t find_impl_(const std::string &substr);
    ssize_t hash_find_impl_(const std::string &substr);

private:
    std::string filepath_;
    SuffixAuto aut_;
    bool fast_impl_{true};
};


#endif //TASK211_FILESEARCH_ALGO_H
