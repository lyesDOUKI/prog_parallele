#include<iostream>
#include<random>

using namespace std;

random_device rd;
mt19937 gen(rd());

int get_random_int(){
    uniform_int_distribution<int> dist(1, 9);
    return dist(gen);
}
void create_matrix(int **matrix, int n) {
    cout << "creation de la matrice..."<< endl;
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n]; // allouer de la memoire pour la ligne i de la matrice
        for (int j = 0; j < n; j++) {
            matrix[i][j] = get_random_int();
        }
    }
    cout << "fin de la creation de la matrice" << endl;
}

void produce_matrix(int **matrix1, int **matrix2, int **matrix3, int n) {
    cout << "multiplication des deux matrices..." << endl;
    for (int i = 0; i < n; i++)
    { 
        matrix3[i] = new int[n];
        for(int j = 0; j < n; j++)
        {
            
            matrix3[i][j] = 0;
            for(int k = 0; k < n; k++)
            {
                matrix3[i][j] = matrix3[i][j] + matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    cout << "fin de la multiplication des deux matrices" << endl;
}

void display_matrix(int **matrix, int n) {
    cout << "Affichage de la matrice..." << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout<<endl;
    }
    cout << "fin de l'affichage de la matrice" << endl;
    
}
void free_matrix(int **matrix, int n) {
    cout << "destruction de la matrice... "<<endl;
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    cout << "fin de la destruction de la matrice" << endl;
}

int main(int argc, char *argv[]) {
    int size_matrix;
    cout << "Entrez la taille de la matrice : " << endl;
    cin >> size_matrix;
    int **matrix_one = new int *[size_matrix]; // tableau de pointeurs où chaque element pointe vers un tableau
    int **matrix_two = new int *[size_matrix];
    int **result_of_production = new int *[size_matrix];
    cout << "================================ matrice Num 1 ================================"<< endl;
    create_matrix(matrix_one, size_matrix);
    cout << "================================"<< endl;
    display_matrix(matrix_one, size_matrix);
    cout << "================================"<< endl;
    cout << "================================ matrice Num 2 ================================"<< endl;
    create_matrix(matrix_two, size_matrix);
    cout << "================================"<< endl;
    display_matrix(matrix_two, size_matrix);
    cout << "================================ Multiplication ==============================="<< endl;
    produce_matrix(matrix_one, matrix_two, result_of_production, size_matrix);
    cout << "================================"<< endl;
    display_matrix(result_of_production, size_matrix);
    cout << "================================ FREE ================================ "<< endl;
    free_matrix(matrix_one, size_matrix);
    free_matrix(matrix_two, size_matrix);
    free_matrix(result_of_production, size_matrix);
    cout << "================================ END FREE ================================ "<< endl;
    return 0;
}