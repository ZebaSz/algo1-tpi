#include "aux.h"

void split(const std::string &s, char delim, std::vector<std::string> &elems) {;
    elems.clear();
    elems.resize(1);
    size_t i = 0;
    while(i < s.size()) {
        if(s[i] == delim) {
            elems.push_back(std::string());
        } else {
            elems[elems.size() - 1].push_back(s[i]);
        }
        ++i;
    }
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}