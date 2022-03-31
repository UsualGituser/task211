//
// Created by Ilya on 31.03.2022.
//

#ifndef TASK211_SUFFIXAUTO_H
#define TASK211_SUFFIXAUTO_H



#include <vector>
#include <string>
#include <map>

class SuffixAuto {
public:
    SuffixAuto() = default;

    SuffixAuto(SuffixAuto&) = default;
    SuffixAuto& operator=(SuffixAuto&) = default;

    SuffixAuto(SuffixAuto&&) = default;
    SuffixAuto& operator=(SuffixAuto&&) = default;

    void init(std::string&& s); // Инициализация суфф.автомата для текста s

    ssize_t find_substr(const std::string& substr); // Поиск подстроки в суфф.автомате

private:
    void add_char(char c);

private:
    struct Node {
        size_t firstpos;
        size_t len;
        int link;
        std::map<char, size_t> edge;
    };

    std::vector<Node> to_;
    long long last_;
};

#endif //TASK211_SUFFIXAUTO_H
