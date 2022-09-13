#include "Sample.h"

Parameter::Parameter() {
    int_value = 0; double_value = 0.0;
    discrete_flag = true;
}
Parameter::Parameter(int x) {
    discrete_flag = true;
    int_value = x;
} 
Parameter::Parameter(double x) {
    discrete_flag = false;
    double_value = x;
}
Sample::Sample() {
    belong_to = 0;
}
void Sample::add_parameter(int x) {
    Parameter p(x);
    parameters.push_back(p);
}
void Sample::add_parameter(double x) {
    Parameter p(x);
    parameters.push_back(p);
}
