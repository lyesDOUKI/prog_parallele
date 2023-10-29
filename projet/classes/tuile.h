#ifndef TUILE_H
#define TUILE_H

#include <string> 
#include <vector>
class Tuile {
public:
    char *tab;
    bool isPlaced = false;
    std::string BLEU = "\033[34mB\033[0m";
    std::string VERT = "\033[32mG\033[0m";
    std::string ROUGE = "\033[31mR\033[0m";
public:
    Tuile();
    Tuile(char *tab);
    void remplir(std::string ligne);
    void affiche_tuile(std::string & affichage1, std::string & affichage2, std::string & affichage3);
    char * get_tab();
};

#endif
