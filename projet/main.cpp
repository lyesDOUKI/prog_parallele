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
    vector<Tuile *> vector_tuile;
    vector_tuile = get_vector_tuile(argv[1]);
    //affiche_vector_tuile(vector_tuile);
    plateau->create_matrix_by_tuiles(vector_tuile);
    //affiche la casse 1 1 de la matrice
    cout << "La case 1 1 de la matrice : " << endl;
    Tuile t1 = plateau->get_matrix()[3][3];
    t1.affiche_tuile();
    
    delete plateau;
    destroy_vector_tuile(vector_tuile);
    return 0;
}
