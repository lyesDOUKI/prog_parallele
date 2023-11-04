#include <iostream>
#include <string>
#include <vector>
#include "./utils/readfile.h"
#include "./classes/matrice.cpp"
#include <chrono> 
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Le nom du fichier en entré : " << argv[1] << endl;
    cout <<"Récuperation de la taille de la matrice ..." << endl;
    int taille_matrice = get_taille_matrice(argv[1]);
    cout << "La taille de la matrice : " << taille_matrice << endl;
    //creer la matrice
    Matrix *plateau = new Matrix(taille_matrice);
    vector<Tuile *> vector_tuile;
    vector_tuile = get_vector_tuile(argv[1]);
    int i = 0;
    int j = 0;
    clock_t temps;
	temps = clock(); 
    bool result;
    cout << "Début de l'algorithme de backtracking ..." << endl;
    result = plateau->backtracking_algorithm(vector_tuile, i, j);
    temps = clock() - temps;
    cout << "temps d'execution : " << (float)temps/CLOCKS_PER_SEC << endl;
    plateau->print_matrix();
    delete plateau;
    destroy_vector_tuile(vector_tuile);
    return 0;
}
