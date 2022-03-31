//
// Created by Ilya on 31.03.2022.
//

#include "SuffixAuto.h"

void SuffixAuto::init(std::string&& str) {
    to_.push_back({0, 0, -1});
    last_ = 0;
    for (char i: str) {
        add_char(i);
    }
}

ssize_t SuffixAuto::find_substr(const std::string& substr) {
    int p = 0;
    int counter = 0;
    if (counter == substr.size()) return 0;
    while (to_[p].edge.find(substr[counter]) != to_[p].edge.end()) {
        p = to_[p].edge[substr[counter]];
        ++counter;
        if (counter == substr.size()) return to_[p].firstpos - substr.size() + 1;
    }
    return -1;
}

void SuffixAuto::add_char(char c) {
    Node new_condition = {to_[last_].len, to_[last_].len + 1, 0};
    to_.push_back(std::move(new_condition));
    int p = last_;
    while (p >= 0 && to_[p].edge.find(c) == to_[p].edge.end()) {
        to_[p].edge[c] = to_.size() - 1;
        p = to_[p].link;
    }
    int curr = to_.size() - 1;
    if (p != -1) {
        int q = to_[p].edge[c];
        if (to_[p].len + 1 == to_[q].len) {
            to_.back().link = q;
        } else {
            Node clone_condition = {to_[q].firstpos, to_[p].len + 1, to_[q].link};
            clone_condition.edge = to_[q].edge;
            to_.push_back(clone_condition);
            to_[q].link = to_.size() - 1;
            to_[curr].link = to_.size() - 1;
            while (p != -1 && to_[p].edge.find(c) != to_[p].edge.end() && to_[p].edge[c] == q) {
                to_[p].edge[c] = to_.size() - 1;
                p = to_[p].link;
            }
        }
    }
    last_ = curr;
}