#include <iostream>
#include <regex>
#include <ctime>
#include <fstream>

using namespace std;

void ram_fun(string size, string count);
void hd_fun(string size, string count);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    // ./memory_test –m RAM –b 1024||1Kb –l 10
    if (argc != 7)// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
    {
        return -1;
    }

    const regex i1(R"(-m)");
    const regex i2(R"((RAM|HD|flash))");
    const regex i3(R"(-b)");
    const regex i4(R"((\d{1,4}Kb|\d{1,4}Mb)|(\d+))");
    const regex i5(R"(-l)");
    const regex i6(R"(\d+)");

//    if (!regex_match((string) argv[1], i1)) { //проверки на верный ввод
//       cout << "НЕВЕРНЫЙ ВВОД" << endl;
//       cout << argv[1] << endl;
//    }

    if (!regex_match((string) argv[2], i2)) { //проверки на верный ввод
        cout << "НЕВЕРНЫЙ ВВОД" << endl;
    }

    if ((string) argv[2] == "RAM")
        ram_fun((string) argv[4], (string) argv[6]);
    else if((string) argv[2] == "HDD")
        hd_fun((string) argv[4], (string) argv[6]);

    return 0;
}

void ram_fun(string size, string count) {
    unsigned int start, stop;
    double result = 0;
    cmatch parts;
    const regex regex(R"((\d+)(Kb|Mb){0,1})");
    if (!regex_match(size.c_str(), parts, regex)) {
        cout << "error input" << endl;
        exit(-1);
    }
    int size_num = stoi(parts[1]);
    if (parts[2] == "Kb"){
        size_num *= 1024;
    }
    else if (parts[2] == "Mb") {
        size_num = size_num * 1024 * 1024;
    }

    cout << "size_num: " << size_num << endl;

    for (int j = 0; j < stoi(count); j++) {
        start = clock();
        char *test_arr = new char[size_num];
        for (int i = 0; i < size_num; i++) {
            test_arr[i] = rand();
        }
        stop = clock();
        cout  << "sizeof array: "<< sizeof(test_arr) << endl;
        result += stop - start;
    }
    cout <<"time at all: " << result / CLOCKS_PER_SEC << endl;
    result = result / stoi(count) / CLOCKS_PER_SEC;
    cout << "time on count: " << result << endl;
}

void hd_fun(string size, string count) {
    unsigned int start, stop;
    double result = 0;
    cmatch parts;
    const regex regex(R"((\d+)(Kb|Mb){0,1})");
    if (!regex_match(size.c_str(), parts, regex)) {
        cout << "error input" << endl;
        exit(-1);
    }
    int size_num = stoi(parts[1]);
    if (parts[2] == "Kb"){
        size_num *= 1024;
    }
    else if (parts[2] == "Mb") {
        size_num = size_num * 1024 * 1024;
    }
    cout << "size_num: " << size_num << endl;
    FILE *fp;

    for (int j = 0; j < stoi(count); j++) {
        char *test_arr = new char[size_num];
        for (int i = 0; i < size_num; i++) {
            test_arr[i] = rand();
        }
        if ((fp = fopen("testfile", "wb+")) == NULL) {
            printf("Cannot open file.");
            exit(-1);
        }
        start = clock();
        for (int i = 0;i < size_num; i++)
            fwrite(test_arr, sizeof(char), 1, fp);

        stop = clock();
        fclose(fp);
        result += stop - start;
    }
    cout <<"time at all: " << result / CLOCKS_PER_SEC << endl;
    result = result / stoi(count) / CLOCKS_PER_SEC;
    cout << "time on count: " << result << endl;
}
