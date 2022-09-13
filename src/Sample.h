#ifndef SAMPLE_H
#define SAMPLE_H

#include "global_config.h"

class Parameter {
public:
    Parameter();
    Parameter(int x);
    Parameter(double x);
    int int_value;
    double double_value;
    bool discrete_flag;
};

class Sample {
public:
    Sample();
    std::vector<Parameter> parameters;
    int belong_to;
    void add_parameter(int x);
    void add_parameter(double y);    
    
};

#endif