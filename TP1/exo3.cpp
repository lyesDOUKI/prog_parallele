#include<iostream>
#include<vector>
#include<thread>
#include<mutex>

using namespace std;

mutex m;
int sumVector(vector<int> &vec)
{
    int sum=0;
    for(int i=0;i<vec.size();i++)
    {
        sum+=vec[i];
    }
    return sum;
}
void sum_thread(vector<int> &vec,int debut,int fin, int &sum)
{
    //sum=0;
    int sum_thread=0;
    for(int i=debut;i<fin;i++)
    {
        sum_thread+=vec[i];
    }   
    m.lock();
    sum+=sum_thread;
    m.unlock();
}

vector<int> vec;
int main()
{
    cout<<"Enter le nombre d'elements du tableau : ";
    int n;
    cin>>n;
    cout<<"Enter les elements du tableau : ";
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        vec.push_back(x);
    }
    cout<<"combien de threads voulez vous creer ? ";
    int nombre_threads;
    cin>>nombre_threads;
    vector<thread> threads;
    int elements_par_thread=n/nombre_threads;
    
    //part 2
    
    /* 
        vector<int> sum_threads;
        for(int i=0;i<nombre_threads;i++)
        {
            int debut = i*elements_par_thread;
            int fin = (i+1)*elements_par_thread;
            threads.emplace_back(
                thread([&sum_threads,i, debut,fin](){
                    
                    sum_threads.emplace_back(sum_thread(vec,debut,fin));
                })
            );
        }
        //attendre les threads
        for(int i=0;i<nombre_threads;i++)
        {
            threads[i].join();
        }
        //sommer les sommes des threads
        int sum=0;
        for(int i=0;i<nombre_threads;i++)
        {
            sum+=sum_threads[i];
        }
        cout<<"version thread : la somme des elements du tableau est : "<<sum<<endl;*/
    //part3
    int sum=0;
    for(int i=0;i<nombre_threads;i++)
    {
        int debut = i*elements_par_thread;
        int fin = (i+1)*elements_par_thread;
        threads.emplace_back(
            thread(sum_thread,ref(vec),debut,fin, ref(sum))
        );
    }
    for(int i=0;i<nombre_threads;i++)
        {
            threads[i].join();
        }
    cout<<"version thread part 3 : la somme des elements du tableau est : "<<sum<<endl;
    cout<<"version classique : la somme des elements du tableau est : "<<sumVector(vec)<<endl;
    return 0;
}
