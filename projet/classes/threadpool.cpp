#include<iostream>
#include<random>
#include<thread>
#include <vector>
#include "tuile.h"
#include <cstring>
using namespace std;

class ThreadPoolManager
{
    public:
    int nb_thread;
    int taille_matrice; //taille de la matrice pour initialiser les plateaux du bassin de thread
    vector<thread> vector_thread;
    vector<Matrix*> vector_matrix;
    vector<Tuile*> vector_tuile;
    vector<bool> tuile_placement;
    //constructeur
    public:
    ThreadPoolManager(int nb_thread, int taille, vector<Tuile*> vector_tuile)
    {
        this->nb_thread = nb_thread;
        this->taille_matrice = taille;
        this->vector_tuile = vector_tuile;
    }
    //creer des matrice en placant la premier tuiles à chaque fois
    public:
    void create_vector_of_matrix()
    {
        cout << "creation du vecteur contenant les matrices initialiser..." << endl;
        for(int i=0; i<this->vector_tuile.size(); i++)
        {
            Matrix* matrix = new Matrix(taille_matrice);

            matrix->init_matrix_with_tuile(this->vector_tuile[i]);
            if(matrix->get_matrix()[0][0].get_tab() == this->vector_tuile[i]->get_tab())
            {

                vector_matrix.push_back(matrix);
            }
            
        }
        cout << "la taille du vecteur matrix : " << vector_matrix.size() << endl;
        cout << "Fin de la création du vecteur matrices" << endl;
    }
    public : 
    void vecteur_a_lancer(vector<Tuile*> vector_tuile_a_lancer, char* tab)
    {
        int b = 0;
        bool trouve = false;
        while(b<vector_tuile_a_lancer.size())
        {
            vector_tuile_a_lancer[b]->isPlaced = false;
            if(strcmp(tab,
            vector_tuile_a_lancer[b]->get_tab())==0 && trouve == false)
            {
                vector_tuile_a_lancer[b]->isPlaced = true;
                trouve = true;
                b = b + 1;
            }
            else
            {
                vector_tuile_a_lancer[b]->isPlaced = false;
                b++;
            }
        }
    }
    
};