#include <iostream>
#include <ctime>

using namespace std;

double BLASS(int size) {
    double **mas1 = new double *[size];
    double **mas2 = new double *[size];
    double **res_mas = new double *[size];

    unsigned int start, stop;
    double result;

    for (int i = 0; i < size; i++) { // выделение
        mas1[i] = new double[size];
        mas2[i] = new double[size];
        res_mas[i] = new double[size];
    }

    for (int i = 0; i < size; i++) { // заполнение
        for (int j = 0; j < size; j++) {
            mas1[i][j] = rand() % 10;
            mas2[i][j] = rand() % 10;
            res_mas[i][j] = 0;
        }
    }

    start = clock();
    for (int i = 0; i < size; i++) { // вычисление
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++){
            res_mas[i][j] += mas1[i][k] * mas2[k][j];
            }
        }
    }
    stop = clock();
    result = (double) (stop - start) / CLOCKS_PER_SEC;
    cout <<"time at default: " << result << endl;
    return result;
}

double BLASS_opt1(int size) {
    double **mas1 = new double *[size];
    double **mas2 = new double *[size];
    double **res_mas = new double *[size];

    unsigned int start, stop;
    double result;

    for (int i = 0; i < size; i++) { // выделение
        mas1[i] = new double[size];
        mas2[i] = new double[size];
        res_mas[i] = new double[size];
    }

    for (int i = 0; i < size; i++) { // заполнение
        for (int j = 0; j < size; j++) {
            mas1[i][j] = rand() % 10;
            mas2[i][j] = rand() % 10;
            res_mas[i][j] = 0;
        }
    }

    start = clock();
    for (int i = 0; i < size; i++) { // вычисление
        for (int k = 0; k < size; k++) {
            for (int j = 0; j < size; j++){
                res_mas[i][j] += mas1[i][k] * mas2[k][j];
            }
        }
    }
    stop = clock();
    result = (double) (stop - start) / CLOCKS_PER_SEC;
    cout <<"time at modified_1: " << result << endl;
    return result;
}


int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc != 2)// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
    {
        return -1;
    }

   // BLASS(atoi(argv[1]));
    BLASS_opt1(atoi(argv[1]));

    return 0;
}
