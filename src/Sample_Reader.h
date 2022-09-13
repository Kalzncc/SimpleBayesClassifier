#ifndef SAMPLE_READER_H
#define SAMPLE_READER_H
#include "global_config.h"
#include "Sample.h"
class Sample_Reader {
private:
    FILE* fp;
    std::vector<int> header; 
public:
    void set_header(std::vector<int> header);    
    int open(const char *fileDir);
    int get(Sample &s, bool classify_flag = true);
    void close();
};   
#endif