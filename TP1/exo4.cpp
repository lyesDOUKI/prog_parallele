#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m;

void affiche_inpair(int &n, int fin)
{
    
    while (n <= fin)
    {
        
        if (n % 2 != 0)
        {
            m.lock();
            cout << n << endl;
            n++;
            m.unlock();
        }
    }
    
}

void affiche_pair(int &n, int fin)
{
   while (n <= fin)
    {
        
        if (n % 2 == 0)
        {
            m.lock();
            cout << n << endl;
            n++;
            m.unlock();
        }
    }
}

int main()
{
    int n = 0;
    int fin = 10;
    /*part sequentielle
    cout << "Affichage des nombres impairs entre " << debut << " et " << fin << endl;
    affiche_inpair(debut, fin);
    cout << "Affichage des nombres pairs entre " << debut << " et " << fin << endl;
    affiche_pair(debut, fin);
    */
   //part avec threads
    thread t1(affiche_pair, ref(n), fin);
    thread t2(affiche_inpair, ref(n), fin);
    t1.join();
    t2.join();
    return 0;
}