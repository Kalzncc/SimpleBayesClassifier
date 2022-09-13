#ifndef BAYES_CLASSIFIER_H
#define BAYES_CLASSIFIER_H

#include "global_config.h"
#include "Likelihood.h"
#include "Sample.h"
#include "Sample_Reader.h"
class Simple_Bayes_Classifier {
private:
    void add_sample(Sample s);
    std::vector<int> prior_count;
    std::vector<std::vector<Likelihood> > likelihood;  
public:
    struct Info {
        int sample_num; // 样例数量
        std::vector<int> header;
        int class_num; // 分类数量
        int sample_size; // 样例分量维度大小
    } info;
    Simple_Bayes_Classifier();
    Simple_Bayes_Classifier(Info info);
    void train(const char *path);
    void classify(Sample& sample);
};
#endif