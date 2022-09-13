#include "Likelihood.h"
Likelihood::Likelihood() {
    parameter_size = 0;
}
Likelihood::Likelihood(int parameter_size) {
    this->parameter_size = parameter_size;
    total_size = 0;
    miu = sqrt_sigma = 0.0;
    under_root_2_pie = sqrt(2 * acos(-1));
}
void Likelihood::add(int val) {
    total_size++;
    count[val]++;
}

void Likelihood::add(double val) {
    double old_sum = miu * total_size;
    double old_miu = miu;
    miu = (old_sum + val) / (total_size+1);
    double d_miu = miu - old_miu;
    sqrt_sigma = ((sqrt_sigma * total_size) + 2 * total_size * old_miu * d_miu + total_size * d_miu *d_miu - 2 * old_sum * d_miu) / (total_size + 1);
    total_size++;
}

double Likelihood::query(int val) {
    return (1.0*(count[val] + 1)) / (total_size + parameter_size);
}

double Likelihood::query(double val) {
    return exp(- ( ((val - miu) * (val - miu)) / (2 * sqrt_sigma) ) ) / (under_root_2_pie * sqrt(sqrt_sigma) );
}