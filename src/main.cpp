#include <iostream>
#include <ctime>
#include "Simple_Bayes_Classifier.h"
#define DATA_PATH "../data/1.txt"

class Simple_Bayes_Classifier::Info info;

void make_sample() {
    auto fp = fopen(DATA_PATH, "w");
    for (int i = 0; i < info.sample_num; i++) {
        int x = rand() % 100;
        int y = rand() % 100;
        fprintf(fp, "%d %d", x, y);
        if (x > 50 && y > 50) {
            fprintf(fp, " %d\n", 0);
        } else {
            fprintf(fp, " %d\n", 1);
        }
    }    
    fclose(fp);
}
void test_classifier() {
    Simple_Bayes_Classifier model(info);
    model.train(DATA_PATH);
    for (int i = 0; i < 100; i++) {
        int x = rand() % 100;
        int y = rand() % 100;
        std::cout << "( " << x << " " << y << ")\n";
        Sample s;
        s.add_parameter(x); s.add_parameter(y);
        if (x > 50 && y > 50) {
            std::cout << "ex : " << 0 << "\n";
        } else {
            std::cout << "ex : " << 1 << "\n";
        }
        model.classify(s);
        std::cout <<"ot : " << s.belong_to << "\n";
    }  
}












void before_all() {
    srand(time(NULL));
    info.sample_num = 500;
    info.class_num = 2;
    info.sample_size = 2;
    info.header = {100, 100};
}

void before_each() {

}
void after_each() {

}
void add_test_func(void (* a)() ) {
    static int flag = 0;
    if (flag == 0) {
        before_all();
        flag = 1;
    }
    before_each();
    printf("Test start\n");
    int start_time = clock();
    a();
    int end_time = clock();
    after_each();
    printf("Test end in : %dms\n", end_time - start_time);
}
int main(int, char**) {
    
    add_test_func(make_sample);
    add_test_func(test_classifier);
}
