#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "../classes/tuile.h"

std::string readfile(std::string filename);
int get_taille_matrice(std::string ligne);
std::vector<Tuile *> get_vector_tuile(std::string filename);
void destroy_vector_tuile(std::vector<Tuile *> vector_tuile);
#endif
