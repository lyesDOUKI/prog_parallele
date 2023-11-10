#include <iostream>
#include <string>
#include <vector>
#include "./utils/readfile.h"
#include "./classes/matrice.cpp"
#include <chrono> 
#include <thread>
#include <atomic>
#include <mutex>
using namespace std;

mutex m;

bool resolu = false;
void lancer_thread(Matrix* plateau, vector<Tuile *> vector_tuile, bool& resolu, bool& result)
{
    int i = 0;
    int j = 0;
    plateau->shuffle_vector_tuile(vector_tuile);
    result = plateau->backtracking_algorithm(vector_tuile, i, j, resolu);
}
int main(int argc, char *argv[]) {
    cout << "Le nom du fichier en entré : " << argv[1] << endl;
    cout <<"Récuperation de la taille de la matrice ..." << endl;
    int taille_matrice = get_taille_matrice(argv[1]);
    cout << "La taille de la matrice : " << taille_matrice << endl;
    //creer la matrice
    Matrix *plateau = new Matrix(taille_matrice);
    Matrix* clone = new Matrix(taille_matrice);
    vector<Tuile *> vector_tuile;
    vector<Tuile *> vector_tuile_clone;
    vector_tuile = get_vector_tuile(argv[1]);
    vector_tuile_clone = get_vector_tuile(argv[1]);
    //int i = 0;
    //int j = 0;
    /*clock_t temps;
	temps = clock(); 
    bool result;
    cout << "Début de l'algorithme de backtracking ..." << endl;
    result = plateau->backtracking_algorithm(vector_tuile, i, j);
    temps = clock() - temps;
    cout << "temps d'execution : " << (float)temps/CLOCKS_PER_SEC << "sec"<< endl;*/
    bool retour1 = false;
    bool retour2 = false;
    //creer un thread num1 avec i et j en variable local
    /*m.unlock();
    thread thread_num1([&]() {
        int i = 0;
        int j = 0;
        plateau->shuffle_vector_tuile(vector_tuile);
        retour1 = plateau->backtracking_algorithm(vector_tuile, i, j, resolu);
        //gérer avec un mutex
        if(retour1)
        {
            cout << "le thread 1 a terminé en premier" << endl;
            m.lock();
            plateau->print_matrix();
            m.unlock();
        } 
    });

    //creer un thread num2 avec i et j en variable local

    thread thread_num2([&]() {
        int i = 0;
        int j = 0;
        clone->shuffle_vector_tuile(vector_tuile_clone);
        retour2 = clone->backtracking_algorithm(vector_tuile_clone, i, j, resolu);
        if(retour2)
        {
            cout << "le thread 2 a terminé en premier" << endl;
            m.lock();
            clone->print_matrix();
            m.unlock();

        }
       
    });
    cout << "lancement des threads ..." << endl;

    thread_num1.join();
    thread_num2.join();*/

    thread t1(lancer_thread, plateau, vector_tuile, ref(resolu), ref(retour1));
    thread t2(lancer_thread, clone, vector_tuile_clone, ref(resolu), ref(retour2));
    cout << "lancement des threads ..." << endl;
    t1.join();
    t2.join();
    if(retour1)
    {
        cout << "le thread 1 a terminé en premier" << endl;
        plateau->print_matrix();
    }
    if(retour2)
    {
        cout << "le thread 2 a terminé en premier" << endl;
        clone->print_matrix();
    }

    
    
    delete plateau;
    destroy_vector_tuile(vector_tuile);
    return 0;
}
