#include <iostream>
#include <ctime>
#include <pthread.h>
#include <omp.h>

using namespace std;

struct data{
    double** arr1;
    double** arr2;
    double** arr_res;
    int min;
    int max;
    int size;
};

void* posixt_BLASS(void* strukt){

    data *my = (struct data*) strukt;

    for (int i = my->min; i < my->max; i++) { // вычисление
        for (int j = 0; j < my->size; j++) {
            for (int k = 0; k < my->size; k++){
                my->arr_res[i][j] += my->arr1[i][k] * my->arr2[k][j];
            }
        }
    }

    return nullptr;
}

void openmp_BLASS(int size, double** mas1, double** mas2, double** res_mas){
    int i, j, k;
#pragma omp parallel for private(i, j, k) shared (mas1, mas2, res_mas)
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            for (k = 0; k < size; ++k) {
                res_mas[i][j] += mas1[i][k] * mas2[k][j];
            }
        }
    }
}


int main(int argc, char *argv[]) {

    srand(time(NULL));

    if (argc != 3)// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
    {
        return -1;
    }

    int size = atoi(argv[1]); // размер матриццы
    int thread_num = atoi(argv[2]); // количество потоков

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

    int size_per_thread;

    if (size >= thread_num){
        size_per_thread = size / thread_num; // элементов на поток  TODO:(если чисел меньше потоков - гг)
    }else{
        return -1;
    }

    data *arr_forthread = new data[thread_num];

    int temp = 0;
    for (int i = 0; i < thread_num; i++){
        arr_forthread[i].size = size;
        arr_forthread[i].arr1 = mas1;
        arr_forthread[i].arr2 = mas2;
        arr_forthread[i].arr_res = res_mas;
        arr_forthread[i].min = temp;
        temp += size_per_thread;
        arr_forthread[i].max = temp;
        if (i == (thread_num - 1)){
            arr_forthread[i].max = size;
        }
    }

//    pthread_t *thread_arr = new pthread_t[size];
//
//    for (int i = 0; i < thread_num; ++i) {
//        pthread_create(&thread_arr[i], nullptr, posixt_BLASS, &arr_forthread[i]);
//    }
//
//    for (int i = 0; i < thread_num; ++i) {
//        pthread_join(thread_arr[i], nullptr);
//    }

    omp_set_dynamic(0);
    omp_set_num_threads(thread_num);

    openmp_BLASS(size, mas1, mas2, res_mas);


//    for (int i = 0; i < size; i++) { // заполнение
//        for (int j = 0; j < size; j++) {
//            cout << mas1[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//    cout << endl;
//
//    for (int i = 0; i < size; i++) { // заполнение
//        for (int j = 0; j < size; j++) {
//            cout << mas2[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//
//    for (int i = 0; i < size; i++) { // заполнение
//        for (int j = 0; j < size; j++) {
//            cout << res_mas[i][j] << " ";
//        }
//        cout << endl;
//    }

    return 0;
}
