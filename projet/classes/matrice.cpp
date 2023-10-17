#include<iostream>
#include<random>
#include<thread>
#include <vector>
#include "tuile.h"
using namespace std;

class Matrix
{
    public :int matrix_size;
    private :Tuile **matrix;

    //constructor
    public:
    Matrix(int size){
        matrix_size = size;
        matrix = new Tuile*[matrix_size];
        for(int i = 0; i < matrix_size; i++){
            matrix[i] = new Tuile[matrix_size];
        }
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

    public: 
    void print_matrix(){
        cout << "affichage de la matrice ..." << endl;
        for(int i = 0; i < matrix_size; i++){
            for(int j = 0; j < matrix_size; j++){
                matrix[i][j].affiche_tuile();
            }
            cout << endl;
        }
        cout << "fin de l'affichage de la matrice" << endl;
    }
    public :
    Tuile ** get_matrix()
    {
        return this->matrix;
    }
};