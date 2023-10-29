#include <iostream>
#include <string>
#include <vector>
#include "./utils/readfile.h"
#include "./classes/matrice.cpp"
#include <chrono> 
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
    int i = 0;
    int j = 0;
    clock_t temps;
	temps = clock(); 
    bool result;
    result = plateau->backtracking_algorithmV2(vector_tuile, i, j);
    temps = clock() - temps;
    cout << "temps d'execution : " << (float)temps/CLOCKS_PER_SEC << endl;
    plateau->print_matrix();


    //affiche la casse 1 1 de la matrice
    /*for (int i = 0; i < taille_matrice; i++) {
        for (int j = 0; j < taille_matrice; j++) {
            cout << "la case " << i << " " << j << " de la matrice" << endl;
            plateau->get_matrix()[i][j].affiche_tuile();
        }
    }
    cout << "fin de l'affichage de la matrice" << endl;
    cout << "test verif extremiter gauche " << endl;
    bool test;
    test = plateau->verif_extremiter_gauche();
    cout << "test : " << test << endl;    
    cout <<"test verif haut" << endl;
    test = plateau->verif_haut();
    cout << "test : " << test << endl;
    cout << "test verif bas" << endl;
    test = plateau->verif_bas();
    cout << "test : " << test << endl;
    cout << "test verif droite" << endl;
    test = plateau->verif_extremiter_droite();
    cout << "test : " << test << endl;
    delete plateau;
    destroy_vector_tuile(vector_tuile);*/
    return 0;
}
