#include "tuile.h"
#include <iostream>
#include <string>

using namespace std;

Tuile::Tuile() {
    tab = new char[4];
}

Tuile::Tuile(char *tab) {
    this->tab = tab;
}

void Tuile::remplir(string ligne) {
    for (int i = 0; i < ligne.length(); i++) {
        if (i % 2 == 0) {
            this->tab[i / 2] = ligne[i];
        }
    }
}

void Tuile::affiche_tuile(std::string & affichage1, std::string & affichage2, std::string & affichage3) {
    /*std::string affichage = "";
    if(tab[1] == 'B'){
        affichage = affichage +  "       "+ BLEU + "       \n";
    }
    if(tab[1] == 'G'){
        affichage = affichage + "       "+ VERT + "       \n";
    }
    if(tab[1] == 'R'){
        affichage = affichage + "       "+ ROUGE + "       \n";
    }
    if(tab[0] == 'B'){
        affichage += BLEU;
    }
    if(tab[0] == 'G'){
        affichage += VERT;
    }
    if(tab[0] == 'R'){
        affichage += ROUGE;
    }
    if(tab[2] == 'B'){
        affichage = affichage + "       " + "       " + BLEU + "\n";
    }
    if(tab[2] == 'G'){
        affichage = affichage +  "       " + "       " + VERT + "\n";
    }
    if(tab[2] == 'R'){
        affichage = affichage + "       " + "       " + ROUGE + "\n";
    }
    if(tab[3] == 'B'){
        affichage = affichage + "       " + BLEU + "       ";
    }
    if(tab[3] == 'G'){
        affichage = affichage + "       " + VERT + "       ";
    }
    if(tab[3] == 'R'){
        affichage = affichage + "       " + ROUGE + "       ";
    }
  /* for(int i = 0; i < 4; i++){
       cout << tab[i] << " ";
   }*/
   if(tab[1] == 'B'){
        affichage1 = affichage1 +  "       "+ BLEU + "           ";
    }
    if(tab[1] == 'G'){
        affichage1 = affichage1 + "       "+ VERT + "           ";
    }
    if(tab[1] == 'R'){
        affichage1 = affichage1 + "       "+ ROUGE + "           ";
    }
    if(tab[0] == 'B'){
        affichage2  = affichage2 + BLEU + "             ";
    }
    if(tab[0] == 'G'){
        affichage2 = affichage2 + VERT + "             ";
    }
    if(tab[0] == 'R'){
        affichage2 = affichage2 + ROUGE + "             ";
    }
    if(tab[2] == 'B'){
        affichage2 = affichage2   + BLEU + "    ";
    }
    if(tab[2] == 'G'){
        affichage2 = affichage2  + VERT + "    ";
    }
    if(tab[2] == 'R'){
        affichage2 = affichage2 + ROUGE + "    ";
    }
    if(tab[3] == 'B'){
        affichage3 = affichage3 +  "       " + BLEU + "           ";
    }
    if(tab[3] == 'G'){
        affichage3 = affichage3 + "       " + VERT + "           ";
    }
    if(tab[3] == 'R'){
        affichage3 = affichage3 + "       " + ROUGE + "           ";
    }
}
char *Tuile::get_tab() {
    return this->tab;
}

