#ifndef TUILE_H
#define TUILE_H

#include <string>
#include <vector>
class Tuile {
private:
    char *tab;

public:
    Tuile();
    Tuile(char *tab);
    void remplir(std::string ligne);
    void affiche_tuile();
    //destructeur
    ~Tuile();
};

#endif
