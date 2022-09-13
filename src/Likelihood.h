#ifndef LIKEHOOD_H
#define LIKEHOOD_H
#include "global_config.h"
class Likelihood {
private:
    int parameter_size;

    int total_size;
    std::map<int, int> count;
    double miu;
    double sqrt_sigma;
    double under_root_2_pie;
public:
    Likelihood();
    Likelihood(int parameter_size);
    void add(int val);
    void add(double val);
    double query(int val);
    double query(double val);
};
#endif