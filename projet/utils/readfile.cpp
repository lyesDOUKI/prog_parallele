#include "readfile.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../classes/tuile.h"

using namespace std;

string readfile_ligneone(string filename) {
    ifstream fichier(filename.c_str(), ios::in);
    string ligne;
    getline(fichier, ligne);
    return ligne;
}

int get_taille_matrice(string filename) {
    string ligne = readfile_ligneone(filename);
    int espace = ligne.find(" ");
    return stoi(ligne.substr(0, espace));
}

vector<Tuile *> get_vector_tuile(string filename) {
    ifstream fichier(filename.c_str(), ios::in);
    string ligne;
    getline(fichier, ligne);
    vector<Tuile *> vector_tuile;

    while (getline(fichier, ligne)) {
        char *tab = new char[4];
        Tuile *t = new Tuile(tab);
        t->remplir(ligne);
        vector_tuile.push_back(t);
    }
    return vector_tuile;
}

void affiche_vector_tuile(vector<Tuile *> vector_tuile) {
    for (int i = 0; i < vector_tuile.size(); i++) {
        //vector_tuile[i]->affiche_tuile();
    }
}

void destroy_vector_tuile(vector<Tuile *> vector_tuile) {
    cout << "destruction du vector_tuile ..." << endl;
    vector_tuile.clear();
    cout << "fin de la destruction du vector_tuile" << endl;
}