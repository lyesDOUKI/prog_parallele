#include <iostream>
#include <string>
#include <vector>
#include "./utils/readfile.h"
#include "./classes/matrice.cpp"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Hello World!" << endl;
    cout << "Le nom du fichier en entré : " << argv[1] << endl;
    int taille_matrice = get_taille_matrice(argv[1]);
    cout << "La taille de la matrice : " << taille_matrice << endl;
    //creer la matrice
    Matrix *plateau = new Matrix(taille_matrice);
    plateau->create_matrix();
    plateau->print_matrix();
    vector<Tuile *> vector_tuile;
    vector_tuile = get_vector_tuile(argv[1]);
    affiche_vector_tuile(vector_tuile);
    destroy_vector_tuile(vector_tuile);
    delete plateau;
    return 0;
}
