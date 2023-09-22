#include<iostream>
#include<random>
#include "./classes/matrice.cpp"
using namespace std;



int main(int argc, char *argv[]) {
    int size_matrix;
    cout << "Entrez la taille de la matrice : " << endl;
    cin >> size_matrix;
    Matrix *matrix_one = new Matrix(size_matrix); // tableau de pointeurs où chaque element pointe vers un tableau
    Matrix *matrix_two = new Matrix(size_matrix);
    Matrix *result_of_production = new Matrix(size_matrix);
    cout << "================================ matrice Num 1 ================================"<< endl;
    matrix_one->create_matrix();
    cout << "================================"<< endl;
    matrix_one->print_matrix();
    cout << "================================"<< endl;
    cout << "================================ matrice Num 2 ================================"<< endl;
    matrix_two->create_matrix();
    cout << "================================"<< endl;
    matrix_two->print_matrix();
    cout << "================================ Multiplication ==============================="<< endl;
    result_of_production->produce_matrixV3(matrix_one, matrix_two, result_of_production);
    cout << "================================"<< endl;
    result_of_production->print_matrix();
    cout << "================================ FREE ================================ "<< endl;
    delete matrix_one;
    delete matrix_two;
    delete result_of_production;
    cout << "================================ END FREE ================================ "<< endl;

    /*Matrix * m1 = new Matrix(4);
    m1->create_matrix();
    m1->print_matrix();*/
    return 0;
}