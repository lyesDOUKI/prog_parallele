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

void Tuile::affiche_tuile() {
    for (int i = 0; i < 4; i++) {
        cout << this->tab[i] << " ";
    }
    cout << endl;
}


