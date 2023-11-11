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
//atomic int
atomic<int> compteur(2);
int cpt_premeirs_threads = 0;
atomic<bool> resolu(false);
atomic<bool> fin_thread_pool(false);
void lancer_thread(Matrix* plateau, vector<Tuile *> vector_tuile,
atomic<bool>& resolu, bool& result, string thread_name)
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

void lancer_threadpool(Matrix* plateau, vector<Tuile *> vector_tuile, string thread_name, atomic<int>& compteur)
{
    if(fin_thread_pool)
    {
        m.lock();
        cpt_premeirs_threads++;
        cout << "le thread : " << thread_name << " n'a pas été lancé car le problème a ";
        cout << "été résolu par un autre thread" << endl;
        m.unlock();
        return;
    }
    //m.unlock();
    
    m.lock();
    cpt_premeirs_threads++;
    cout << "lancement du thread : " << thread_name << endl;
    m.unlock();
    int i = 0;
    int j = 1;
    bool result = false;
    result = plateau->backtracking_algorithm_thread_one(vector_tuile, i, j,fin_thread_pool , thread_name);
    m.lock();
    compteur--;
    cout << "Fin du Thread : " << thread_name << " avec le statut : " << result << endl; 
    if(result)
    {
        fin_thread_pool = true;
        //m.lock();
        cout << "le thread : " << thread_name << " a trouvé la solution" << endl;
        plateau->print_matrix();
        //m.unlock();
    }
    delete plateau;
    destroy_vector_tuile(vector_tuile);
    m.unlock();

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
        cout << "Vous avez choisi la méthode thread 'Random'!" << endl;
        cout << "Cette méthode mélange les tuiles et lance trois threads, ";
        cout << "le premier qui termine affiche la solution" << endl;
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
        /*clock_t temps = clock();
        clock_t temps_thread1 = clock();
        clock_t temps_thread2 = clock();
        clock_t temps_thread3 = clock();*/
        auto start_time_thread1 = chrono::high_resolution_clock::now();
        auto start_time_thread2 = chrono::high_resolution_clock::now();
        auto start_time_thread3 = chrono::high_resolution_clock::now();
        thread t1(lancer_thread, plateau, vector_tuile, ref(resolu), ref(retour1), "thread1:vecteur-de-base");
        thread t2(lancer_thread, clone_one, vector_tuile_clone_one, ref(resolu), ref(retour2), "thread2:vecteur-random-1");
        thread t3(lancer_thread, clone_two, vector_tuile_clone_two, ref(resolu), ref(retour3), "thread3:vecteur-random-2");
        t1.join();
        //temps_thread1 = clock() - temps_thread1;

        auto end_time_thread1 = chrono::high_resolution_clock::now();
        auto duration_thread1 = chrono::duration_cast<chrono::milliseconds>(end_time_thread1 - start_time_thread1);
        t2.join();
        //temps_thread2 = clock() - temps_thread2;
        auto end_time_thread2 = chrono::high_resolution_clock::now();
        auto duration_thread2 = chrono::duration_cast<chrono::milliseconds>(end_time_thread2 - start_time_thread2);
        t3.join();
        //temps_thread3 = clock() - temps_thread3;
        auto end_time_thread3 = chrono::high_resolution_clock::now();
        auto duration_thread3 = chrono::duration_cast<chrono::milliseconds>(end_time_thread3 - start_time_thread3);
        if(retour1)
        {   
            cout << endl;
            cout << "THREAD 1 SUCCESS : temps d'execution du 'thread1:vecteur-de-base' : ";
            cout << duration_thread1.count()<< " milliseconds" << endl;
        }
        else if(retour2)
        {
            cout << endl;
            cout << "THREAD 2 SUCCESS : temps d'execution du 'thread1:vecteur-de-base' : ";
            cout << duration_thread2.count()<< " milliseconds" << endl;
        }
        else if (retour3)
        {
            cout << endl;
            cout << "THREAD 3 SUCCESS : temps d'execution du 'thread1:vecteur-de-base' : ";
            cout << duration_thread3.count() << " milliseconds" << endl;
        }
        cout << endl;
        cout << "DESTRUCTION DES PLATEAUX ..." << endl;
        delete plateau;
        delete clone_one;
        delete clone_two;
        cout << "DESTRUCTION DES VECTEURS ..." << endl;
        destroy_vector_tuile(vector_tuile);
        destroy_vector_tuile(vector_tuile_clone_one);
        destroy_vector_tuile(vector_tuile_clone_two);
    }
    else if(choix == "P" || choix == "p")
    {
        cout << "Vous avez choisi la méthode 'threadPool'! "<< endl;
        cout << "cette méthode lance 2 threads simultanément. Dés q'un thread se finit, on relance un autre" << endl;
        cout << "NB : à chaque fin d'un thread, le plateau est détruit et le vecteur de tuiles est détruit" << endl;
        cout << endl;
        vector<Tuile *> vector_tuile;
        vector_tuile = get_vector_tuile(argv[1]);
        vector<Tuile *> vector_tuile_a_lancer;
        vector_tuile_a_lancer = get_vector_tuile(argv[1]);
        ThreadPoolManager* thread_pool = new ThreadPoolManager(2, taille_matrice, vector_tuile);  
        thread_pool->create_vector_of_matrix();
        
        if(thread_pool->vector_matrix.size() < thread_pool->nb_thread)
        {
            cout << "le nombre de threads à lancer est supérieur au nombre de matrice initialiser" << endl;
            cout << "THREAD POOL IMPOSSIBLE" <<endl;
            return 0;
        }
        Matrix *plateau1 = thread_pool->vector_matrix[0];
        Matrix *plateau2 = thread_pool->vector_matrix[1];

        vector<Tuile *> vector_tuile_a_lancer1;
        vector_tuile_a_lancer1 = get_vector_tuile(argv[1]);
        vector<Tuile *> vector_tuile_a_lancer2;
        vector_tuile_a_lancer2 = get_vector_tuile(argv[1]);

        thread_pool->vecteur_a_lancer(vector_tuile_a_lancer1, plateau1->get_matrix()[0][0].get_tab());
        thread_pool->vecteur_a_lancer(vector_tuile_a_lancer2, plateau2->get_matrix()[0][0].get_tab());
        auto start_time = chrono::high_resolution_clock::now();
        thread t1(lancer_threadpool, plateau1, vector_tuile_a_lancer1, "thread1", ref(compteur));
        thread t2(lancer_threadpool, plateau2, vector_tuile_a_lancer2, "thread2", ref(compteur));

        thread_pool->vector_thread.push_back(move(t1));
        thread_pool->vector_thread.push_back(move(t2));

        while(cpt_premeirs_threads < 2)
        {
            //cout << "attente de la création des 2 threads ..." << endl;
        }

        int indice = 2;
        while(indice < thread_pool->vector_matrix.size() && !fin_thread_pool)
        {
            m.lock();
            if(compteur < thread_pool->nb_thread && !fin_thread_pool)
            {
                compteur ++;
                m.unlock();
                    Matrix *plateau = thread_pool->vector_matrix[indice];
                    vector<Tuile *> vector_tuile_a_lancer;
                    vector_tuile_a_lancer = get_vector_tuile(argv[1]);
                    indice++;
                    thread_pool->vecteur_a_lancer(vector_tuile_a_lancer, 
                    plateau->get_matrix()[0][0].get_tab());
                    thread t(lancer_threadpool, plateau, vector_tuile_a_lancer, 
                                "thread" + to_string(indice), ref(compteur));
                    thread_pool->vector_thread.push_back(move(t));
            }else
            {
                m.unlock();
            }
        }
        for(int i=0; i<thread_pool->vector_thread.size(); i++)
        {
            thread_pool->vector_thread[i].join();
        }
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        cout << "Temps d'exécution du threadpool "<< ": " << duration.count() << " milliseconds" << endl;
        
    }
    else
    {
        cout << "Vous avez choisi la méthode 'séquentielle'" << endl;
        cout << endl;
        Matrix *plateau = new Matrix(taille_matrice);
        vector<Tuile *> vector_tuile;
        vector_tuile = get_vector_tuile(argv[1]);
        int i = 0;
        int j = 0;
        bool result;
        auto start_time = chrono::high_resolution_clock::now();
        cout << "Début de l'algorithme de backtracking ..." << endl;
        result = plateau->backtracking_algorithm(vector_tuile, i, j);
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        plateau->print_matrix();
        cout << endl;
        cout << "END SUCCESS : temps d'execution : " << duration.count() << " milliseconds"<< endl;
        cout << endl;
        cout << "DESTRUCTION DU PLATEAU ..." << endl;
        delete plateau;
        cout << "DESTRUCTION DU VECTEUR DE TUILES..." << endl;
        destroy_vector_tuile(vector_tuile);
    }
    

   
    return 0;
}
