//
// Created by Ilya on 31.03.2022.
//

#include <fcntl.h>
#include "filesearch_algo.h"

filesearch_algo::filesearch_algo(bool search_method) {
    fast_impl_ = search_method;
}

void filesearch_algo::file_read(std::string &filepath) {
    filepath_ = std::move(filepath);
    if (fast_impl_) {
        std::ifstream file(filepath_);
        std::string buf;
        std::string text;
        while (std::getline(file, buf)) {
            text += buf;
            text += " ";
        }
        aut_.init(std::move(text));
    }
}

ssize_t filesearch_algo::find_substring(const std::string &substr) {
    return find_impl_(substr);
}

ssize_t filesearch_algo::find_impl_(const std::string &substr) {
    if (fast_impl_) {
        return aut_.find_substr(substr);
    } else {
        return hash_find_impl_(substr);
    }
}

ssize_t filesearch_algo::hash_find_impl_(const std::string &substr) { // Алгоритм Рабина-Карпа
    FILE* file_;
    if ((file_ = fopen(filepath_.c_str(), "r")) == nullptr) {
        return -1;
    }
    const long long prime_ = 31;
    const long long mod_ = 1e9 + 7;
    char buf[substr.size()];
    if (fgets(buf, substr.size() + 1, file_) == nullptr) {
        fclose(file_);
        return -1;
    }
    for (int i = 0; i < substr.size(); ++i) {
        if (buf[i] == '\n') {
            buf[i] = ' ';
        }
    }
    std::deque<long long> hash_(substr.size());  // Используется дек для контроля памяти - хеши префиксов, которые прошли через проверку будут удаляться pop_front-ом
    long long hash_substr_ = substr[0] % mod_;
    for (int i = 1; i < substr.size(); ++i) {
        hash_substr_ = ((hash_substr_ * prime_) % mod_ + substr[i]) % mod_;
    }
    hash_[0] = buf[0];
    for (int i = 1; i < substr.size(); ++i) {
        hash_[i] = ((hash_[i - 1] * prime_) % mod_ + buf[i]) % mod_;
    }
    long long prime_pow_ = 1;
    for (int i = 0; i < substr.size(); ++i) {
        prime_pow_ *= prime_;
        prime_pow_ %= mod_;
    }
    long long pos = 0;
    char new_symbol_;
    if (hash_substr_ == hash_.back()) {
        fclose(file_);
        return pos;
    }
    while ((new_symbol_ = fgetc(file_)) != EOF) {
        ++pos;
        hash_.emplace_back(((hash_.back() * prime_) % mod_ + new_symbol_) % mod_);
        if (new_symbol_ != '\n' && (hash_.back() - hash_.front() * prime_pow_ - hash_substr_ + 2 * mod_) % mod_ == 0) {
            fclose(file_);
            return pos;
        }
        hash_.pop_front();
    }
    fclose(file_);
    return -1;
}
