#include "aux.h"

template<class T>
bool mismos(const std::vector<T> & lista, const std::vector<T> & otraLista) {
    bool iguales = lista.size() == otraLista.size();
    if(iguales) {
        std::vector<bool> usados(lista.size(), false);
        size_t i = 0;
        while(iguales && i < lista.size()) {
            size_t j = 0;
            bool encontrado = false;
            while(!encontrado && j < lista.size()) {
                if(lista[i] == otraLista[j] && !usados[j]) {
                    usados[j] = true;
                    encontrado = true;
                }
                ++j;
            }
            iguales = encontrado;
            ++i;
        }
    }
    return iguales;
}

template bool mismos<Producto>(const std::vector<Producto> & lista, const std::vector<Producto> & otraLista);
template bool mismos<Drone>(const std::vector<Drone> & lista, const std::vector<Drone> & otraLista);

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
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