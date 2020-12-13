#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

#define eps 0.00000000000001
#define N 100000
#define M 10

void cos_time(){
    unsigned int start, stop;
    double result = 0;
    for(int i = 0; i < M; i++) {

        start = clock();

        for (int j = 0; j < N; j++)

            cos(5);

        stop = clock();

        result += stop - start;

    }
    double absolute = fabs(((result / M) - (double)(stop - start)) / CLOCKS_PER_SEC);
    double otnosite = fabs((result / M - (double)(stop - start)) / CLOCKS_PER_SEC) / ((double)(stop - start) / CLOCKS_PER_SEC) * 100;
    result = result / M / CLOCKS_PER_SEC;
    cout << result << " "<< absolute << " " << otnosite << endl;
}

void log_time(){
    unsigned int start, stop;
    double result = 0;
    for(int i = 0; i < M; i++) {

        start = clock();

        for (int j = 0; j < N; j++)

            log(5);

        stop = clock();

        result += stop - start;

    }
    double absolute = fabs(((result / M) - (double)(stop - start)) / CLOCKS_PER_SEC);
    double otnosite = fabs((result / M - (double)(stop - start)) / CLOCKS_PER_SEC) / ((double)(stop - start) / CLOCKS_PER_SEC) * 100;
    result = result / M / CLOCKS_PER_SEC;
    cout << result << " "<< absolute << " " << otnosite << endl;
}

void sqrt_time(){
    unsigned int start, stop;
    double result = 0;
    for(int i = 0; i < M; i++) {

        start = clock();

        for (int j = 0; j < N; j++)

            sqrt(5);

        stop = clock();

        result += stop - start;

    }
    double absolute = fabs(((result / M) - (double)(stop - start)) / CLOCKS_PER_SEC);
    double otnosite = fabs((result / M - (double)(stop - start)) / CLOCKS_PER_SEC) / ((double)(stop - start) / CLOCKS_PER_SEC) * 100;
    result = result / M / CLOCKS_PER_SEC;
    cout << result << " "<< absolute << " " << otnosite << endl;
}


int main(){
    cos_time();
    log_time();
    sqrt_time();
    return 0;
}