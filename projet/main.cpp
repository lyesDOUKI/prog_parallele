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
void lancer_thread(Matrix* plateau, vector<Tuile *> vector_tuile,
bool& resolu, bool& result, string thread_name)
{
    int i = 0;
    int j = 0;
    plateau->shuffle_vector_tuile(vector_tuile);
    result = plateau->backtracking_algorithm(vector_tuile, i, j, resolu, thread_name);
    if(result)
    {
        cout << "le thread : " << thread_name << " a terminé en premier" << endl;
        m.lock();
        plateau->print_matrix();
        m.unlock();
    }
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
    bool retour1 = false;
    bool retour2 = false;
    cout << "création et lancement des threads ..." << endl;
    clock_t temps = clock();
    clock_t temps_thread1 = clock();
    clock_t temps_thread2 = clock();
    thread t1(lancer_thread, plateau, vector_tuile, ref(resolu), ref(retour1), "thread1");
    thread t2(lancer_thread, clone, vector_tuile_clone, ref(resolu), ref(retour2), "thread2");
    
    t1.join();
    temps_thread1 = clock() - temps_thread1;
    cout << "temps d'execution du thread 1 : " << (float)temps_thread1/CLOCKS_PER_SEC << " secondes" << endl;
    t2.join();
    temps_thread2 = clock() - temps_thread2;
    cout << "temps d'execution du thread 2 : " << (float)temps_thread2/CLOCKS_PER_SEC << " secondes" << endl;

    temps = clock() - temps;
    cout << "temps d'execution total : " << (float)temps/CLOCKS_PER_SEC << " secondes" << endl;
    delete plateau;
    destroy_vector_tuile(vector_tuile);
    return 0;
}
