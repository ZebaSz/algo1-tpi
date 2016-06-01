#ifndef AUX_H
#define AUX_H

#include <iostream>
#include <vector>

void split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif //AUX_H