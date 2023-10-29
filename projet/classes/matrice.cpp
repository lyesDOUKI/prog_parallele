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
    public : 
    bool backtraking_algorithm(vector<Tuile *> vector_tuile, int i, int j){
        cout << " i = " << i << " j = " << j << endl;
        cout << "backtraking_algorithm ..." << endl;
        if(i == matrix_size){
            cout << "fin de backtraking_algorithm en true" << endl;
            return true;
        }
        for(int k = 0; k < vector_tuile.size() -1; k++){
            cout << "size : " << vector_tuile.size() << endl;
            cout << "indice k debut : " << k << endl;
            cout << "lecture de la tuile : " << endl;
            //vector_tuile[k]->affiche_tuile();
            if(vector_tuile[k]->isPlaced == false){
                cout << "condition place ok " << endl;
                matrix[i][j] = *vector_tuile[k];
                cout << "set tuile ok " << endl;
                vector_tuile[k]->isPlaced = true;
                Tuile t = *vector_tuile[k+1];
                cout << "recup tuile suivante ok " << endl;
                cout << "avant appel verif haut : " << i  << " " << j << endl;
                if(verif_haut(matrix[i][j], t, i, j)){
                    if(j == matrix_size-1)
                    {
                        cout << "j complet" << endl;
                        i = i+1;
                        j = -1;
                    }
                   
                    if(backtraking_algorithm(vector_tuile, i, j+1)){
                        cout << "fin de backtraking_algorithm en true" << endl;
                        return true;
                    }
                }
                if(j == matrix_size-1)
                    {
                        cout << "j complet" << endl;
                        i = i+1;
                        j = -1;
                    }
                j = j+1;
                cout << "indice k : " << k << endl;

                vector_tuile[k]->isPlaced = false;
            }
        }
        cout << "fin de backtraking_algorithm en false" << endl;
        return false;
    }

    public : 
    bool canPlaceTile(Tuile* tile, int i, int j) {
    
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
    bool backtracking_algorithmV2(vector<Tuile*>& vector_tuile, int& i, int& j) {
        if (i == matrix_size) {
            cout << "####fin####" << endl;
            return true;
        }

        for (int k = 0; k < vector_tuile.size(); k++) {
            if (!vector_tuile[k]->isPlaced) {
                if (canPlaceTile(vector_tuile[k], i, j)) {
                    matrix[i][j] = *vector_tuile[k];
                    vector_tuile[k]->isPlaced = true;
                    int nextI = i;
                    int nextJ = j + 1;
                    if (nextJ == matrix_size) {
                        nextI = i + 1;
                        nextJ = 0;
                    }

                    if (backtracking_algorithmV2(vector_tuile, nextI, nextJ)) {
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
        }
        cout << "fin de l'affichage de la matrice" << endl;
    }
    public :
    Tuile ** get_matrix()
    {
        return this->matrix;
    }
   public :
    bool verif_extremiter_gauche(Tuile t1, Tuile t2)
    {
        cout << "verif_extremiter_gauche ..." << endl;
        char c1 = t1.get_tab()[0];
        char c2 = t2.get_tab()[0];
        if(c1 != c2)
        {
            cout << "fin de verif_extremiter_gauche en false" << endl;
            return false;
        }
        cout << "fin de verif_extremiter_gauche en true" << endl;
        return true;
    }
    public :
    bool verif_haut(Tuile t1, Tuile t2, int i, int j)
    {
        if(i == 0)
        {
            if((t1.get_tab()[1] == t2.get_tab()[1])
                && (t1.get_tab()[2] == t2.get_tab()[0]))
            {
                cout << "return true 1" << endl;
                return true;
            }
        }else
        {
            if((t1.get_tab()[2] == t2.get_tab()[0]))
            {
                cout << "return true 2 " << endl;
                return true;
            }
        }
        cout << "return false" << endl;
        return false;
    }
    public :
    bool verif_bas(Tuile t1, Tuile t2)
    {
        
        cout << "verif_bas ..." << endl;
        char c1 = t1.get_tab()[3];
        char c2 = t2.get_tab()[3];
        if(c1 != c2)
        {
            cout << "fin de verif_bas en false" << endl;
            return false;
        }
        cout << "fin de verif_bas en true" << endl;
        return true;
    }
    public :
    bool verif_extremiter_droite(Tuile t1, Tuile t2)
    {
        cout << "verif_extremiter_droite ..." << endl;
        char c1 = t1.get_tab()[2];
        char c2 = t2.get_tab()[2];
        if(c1 != c2)
        {
            cout << "fin de verif_extremiter_droite en false" << endl;
            return false;
        }
        cout << "fin de verif_extremiter_droite en true" << endl;
        return true;
    }
};