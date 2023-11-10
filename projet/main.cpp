#include <iostream>
#include <string>
#include <vector>
#include "./utils/readfile.h"
#include "./classes/matrice.cpp"
#include "./classes/threadpool.cpp"
#include <chrono> 
#include <thread>
#include <atomic>
#include <mutex>
#include <cstring>
using namespace std;

mutex m;

bool resolu = false;
void lancer_thread(Matrix* plateau, vector<Tuile *> vector_tuile,
bool& resolu, bool& result, string thread_name)
{
    int i = 0;
    int j = 0;
    result = plateau->backtracking_algorithm_thread_one(vector_tuile, i, j, resolu, thread_name);
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
   
    cout << "Quelles méthode de thread voulez vous appliquer ? " << endl;
    cout << "Tapez R pour thread Random, tapez P pour threadPool ou tapez une autre lettre pour résoudre le problème séquentiellement" << endl;
    string choix = "";
    cin >> choix;
    if(choix == "R" || choix == "r")
    {
        //on va lancer 3 threads, 1 avec le vecteur lu, 2 autres avec des vecteurs mélanger
        cout << "Vous avez choisi le thread simple" << endl;
        cout << endl;
        Matrix *plateau = new Matrix(taille_matrice);
        Matrix* clone_one = new Matrix(taille_matrice);
        Matrix* clone_two = new Matrix(taille_matrice);
        vector<Tuile *> vector_tuile;
        vector<Tuile *> vector_tuile_clone_one;
        vector<Tuile *> vector_tuile_clone_two;
        vector_tuile = get_vector_tuile(argv[1]);
        vector_tuile_clone_one = get_vector_tuile(argv[1]);
        vector_tuile_clone_two = get_vector_tuile(argv[1]);

        //on mélange les deux vecteurs qu'on a clone
        clone_one->shuffle_vector_tuile(vector_tuile_clone_one);
        clone_two->shuffle_vector_tuile(vector_tuile_clone_two);
        bool retour1 = false;
        bool retour2 = false;
        bool retour3 = false;
        cout << "création et lancement des threads ..." << endl;
        clock_t temps = clock();
        clock_t temps_thread1 = clock();
        clock_t temps_thread2 = clock();
        clock_t temps_thread3 = clock();
        thread t1(lancer_thread, plateau, vector_tuile, ref(resolu), ref(retour1), "thread1:vecteur-de-base");
        thread t2(lancer_thread, clone_one, vector_tuile_clone_one, ref(resolu), ref(retour2), "thread2:vecteur-random-1");
        thread t3(lancer_thread, clone_two, vector_tuile_clone_two, ref(resolu), ref(retour3), "thread3:vecteur-random-2");
        t1.join();
        temps_thread1 = clock() - temps_thread1;
        t2.join();
        temps_thread2 = clock() - temps_thread2;
        t3.join();
        temps_thread3 = clock() - temps_thread3;
        if(retour1)
        {   
            cout << endl;
            cout << "THREAD 1 SUCCESS : temps d'execution du 'thread1:vecteur-de-base' : " << (float)temps_thread1/CLOCKS_PER_SEC << " secondes" << endl;
        }
        else if(retour2)
        {
            cout << endl;
            cout << "THREAD 2 SUCCESS : temps d'execution du 'thread2:vecteur-random-1' : " << (float)temps_thread2/CLOCKS_PER_SEC << " secondes" << endl;
        }
        else if (retour3)
        {
            cout << endl;
            cout << "THREAD 3 SUCCESS : temps d'execution du 'thread3:vecteur-random-2' : " << (float)temps_thread3/CLOCKS_PER_SEC << " secondes" << endl;
        }
        cout << endl;
        cout << "DESTRUCTION DES PLATEAUX ..." << endl;
        delete plateau;
        delete clone_one;
        delete clone_two;
        cout << endl;
        cout << "DESTRUCTION DES VECTEURS ..." << endl;
        destroy_vector_tuile(vector_tuile);
        destroy_vector_tuile(vector_tuile_clone_one);
        destroy_vector_tuile(vector_tuile_clone_two);
    }
    else if(choix == "P" || choix == "p")
    {
        cout << "Vous avez choisi le threadPool" << endl;
        cout << endl;
        vector<Tuile *> vector_tuile;
        vector_tuile = get_vector_tuile(argv[1]);
        vector<Tuile *> vector_tuile_a_lancer;
        vector_tuile_a_lancer = get_vector_tuile(argv[1]);
        ThreadPoolManager* thread_pool = new ThreadPoolManager(3, taille_matrice, vector_tuile);  
        thread_pool->create_vector_of_matrix();

        cout << "on parcours le vecteurs et on lance séquentiellement " << endl;
        for(int a=0; a<thread_pool->vector_matrix.size(); a++)
        {
            cout << "matrice : " << a + 1 << endl;
            char *tuile_placer = thread_pool->vector_matrix[a]->get_matrix()[0][0].get_tab();
            thread_pool->vecteur_a_lancer(vector_tuile_a_lancer, tuile_placer);
            int i = 0;
            int j = 1;
            bool retour = false;
            retour = thread_pool->vector_matrix[a]->backtracking_algorithm(
                vector_tuile_a_lancer,i,j);
            if(retour)
            {
                cout << "solution trouver pour la matrice " << a + 1 << endl;
                thread_pool->vector_matrix[a]->print_matrix();
            }else
            {
                cout << "KO pour a = " << a + 1 << endl;
            }
            
        }
    }
    else
    {
        cout << "Vous avez choisi la maniére séquentielle" << endl;
        cout << endl;
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
        plateau->print_matrix();
        temps = clock() - temps;
        cout << "END SUCCESS : temps d'execution : " << (float)temps/CLOCKS_PER_SEC << " secondes"<< endl;
        delete plateau;
        destroy_vector_tuile(vector_tuile);
    }
    

   
    return 0;
}
