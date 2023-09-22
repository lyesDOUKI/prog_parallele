#include<iostream>
#include<random>


using namespace std;


random_device rd;
mt19937 gen(rd());

int get_random_int(){
    uniform_int_distribution<int> dist(1, 9);
    return dist(gen);
}

class Matrix
{
    private :int matrix_size;
    private :int **matrix;

    //constructor
    public:
    Matrix(int size){
        matrix_size = size;
        matrix = new int*[matrix_size];
        for(int i = 0; i < matrix_size; i++){
            matrix[i] = new int[matrix_size];
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
    void create_matrix(){
        cout<< "création de la matrice ..." << endl;
        for(int i = 0; i < matrix_size; i++){
            for(int j = 0; j < matrix_size; j++){
                matrix[i][j] = get_random_int();
            }
        }
        cout<< "fin de la création de la matrice" << endl;
    }
    public:
    void print_matrix(){
        cout << "affichage de la matrice ..." << endl;
        for(int i = 0; i < matrix_size; i++){
            for(int j = 0; j < matrix_size; j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "fin de l'affichage de la matrice" << endl;
    }
    public:
    void produce_matrix(Matrix * matrix1, Matrix * matrix2, Matrix * matrix3){
    
    int ** a = matrix1->get_matrix();
    int ** b = matrix2->get_matrix();
    int ** c = matrix3->get_matrix();
    for (int i = 0; i < matrix_size; i++)
    { 
        //matrix3[i] = new int[matrix_size];
        for(int j = 0; j < matrix_size; j++)
        {
            
            c[i][j] = 0;
            for(int k = 0; k < matrix_size; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
        
    }

    }
    public:
    void destroy(int ** result_of_production){

        for(int i = 0; i < matrix_size; i++){
            delete[] result_of_production[i];
        }
        delete[] result_of_production;
    }
    public :
    int ** get_matrix()
    {
        return this->matrix;
    }
};