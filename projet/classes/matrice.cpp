#include<iostream>
#include<random>
#include<thread>
#include <vector>
#include "tuile.h"
#include<random>
#include<algorithm>
using namespace std;

class Matrix
{
    public :int matrix_size;
    private :Tuile **matrix;

    //constructor
    public:
    Matrix(int size){
        cout <<"creation de la matrice ..."<< endl;
        matrix_size = size;
        matrix = new Tuile*[matrix_size];
        for(int i = 0; i < matrix_size; i++){
            matrix[i] = new Tuile[matrix_size];
        }
        cout <<"fin de la creation de la matrice"<< endl;
    }
    //destructor
    ~Matrix(){
        cout << "destruction de la matrice ..." << endl;
        for(int i = 0; i < matrix_size; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
        cout << "fin de la destruction de la matrice" << endl;
    }
    public: 
    void create_matrix_by_tuiles(vector<Tuile *> vector_tuile){
        cout<< "création de la matrice ..." << endl;
        for(int i = 0; i < matrix_size; i++){
            for(int j = 0; j < matrix_size; j++){
                matrix[i][j] = *vector_tuile[i*matrix_size+j];
            }
        }
        cout<< "fin de la création de la matrice" << endl;
    }
    public : 
    bool can_place_tuile(Tuile* tile, int i, int j) {
    
    if(i == 0 && j == 0) {
        if(tile->get_tab()[0] != tile->get_tab()[1]) {
           // cout << "false 1 " << endl;
            return false;
        }
    }
    if(j == 0 && i > 0)
    {
        if(tile->get_tab()[0] != matrix[0][0].get_tab()[0])
        {

            //cout << "false 2 " << endl;
            return false;
        }
    }
    if(i == 0 && j > 0)
    {
        if(tile->get_tab()[1] != matrix[0][0].get_tab()[1])
        {
            //cout << "false 3 " << endl;
            return false;
        }
    }
    if(i == matrix_size-1)
    {
        if(tile->get_tab()[3] != matrix[0][0].get_tab()[0])
        {
            //cout << "false 4 " << endl;
            return false;
        }
    }
    if(j == matrix_size-1)
    {
        if(tile->get_tab()[2] != matrix[0][0].get_tab()[1])
        {
            //cout << "false 5 " << endl;
            return false;
        }
    }
    if (i > 0) {
        if (tile->get_tab()[1] != matrix[i - 1][j].get_tab()[3]) {

            //cout << "false 6 " << endl;
            return false;
        }
    }
    if (j > 0) {
        if (tile->get_tab()[0] != matrix[i][j - 1].get_tab()[2]) {
            //cout << "false 7 " << endl;
            return false;
        }
    }

    //cout << "je retourne true" << endl;
    return true;
}
    public : 
    bool backtracking_algorithm(vector<Tuile*>& vector_tuile, int& i, int& j, bool& resolu) {
        
        if (i == matrix_size) {
            cout << "############## Fin Backtracking Algorithm ##############" << endl;
            resolu = true;
            return true;
        }
        if(resolu) {
            return false;
        }

        for (int k = 0; k < vector_tuile.size(); k++) {
            if (!vector_tuile[k]->isPlaced) {
                if (can_place_tuile(vector_tuile[k], i, j)) {
                    matrix[i][j] = *vector_tuile[k];
                    vector_tuile[k]->isPlaced = true;
                    int nextI = i;
                    int nextJ = j + 1;
                    if (nextJ == matrix_size) {
                        nextI = i + 1;
                        nextJ = 0;
                    }

                    if (backtracking_algorithm(vector_tuile, nextI, nextJ, resolu)) {
                        return true;
                    }
                    vector_tuile[k]->isPlaced = false;
                }
            }
        }

        return false; 
    }

    public: 
    void print_matrix(){
        
        cout << "affichage de la matrice ..." << endl;
        cout << endl;
        for(int i = 0; i < matrix_size; i++){
            string display1 = "";
            string display2 = "";
            string display3 = "";
            for(int j = 0; j < matrix_size; j++){
             matrix[i][j].affiche_tuile(display1, display2, display3);
            }
            cout << display1 << endl;
            cout << display2 << endl;
            cout << display3 << endl;
            cout << endl;
            cout << endl;
        }
        cout << "fin de l'affichage de la matrice" << endl;
    }
    public :
    Tuile ** get_matrix()
    {
        return this->matrix;
    }
    public:
    void shuffle_vector_tuile(std::vector<Tuile*>& vector_tuile) {
    std::random_device rd;
    std::mt19937 gen(rd());

    //je mélange trois fois
    for(int i = 0; i < 3; i++) {
        std::shuffle(vector_tuile.begin(), vector_tuile.end(), gen);
    }
}
};