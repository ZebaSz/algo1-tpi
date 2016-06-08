#ifndef AUX_H
#define AUX_H

#include <iostream>
#include <vector>
#include "tipos.h"
#include "drone.h"

void split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

template<class T>
bool mismos(const std::vector<T> & lista, const std::vector<T> & otraLista);

#endif //AUX_H