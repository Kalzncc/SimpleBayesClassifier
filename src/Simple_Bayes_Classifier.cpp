#include "Simple_Bayes_Classifier.h"
Simple_Bayes_Classifier::Simple_Bayes_Classifier() {}
Simple_Bayes_Classifier::Simple_Bayes_Classifier(Info info) {
    this->info = info;
}
void Simple_Bayes_Classifier::add_sample(Sample s) {
    for (int i = 0; i < info.sample_size; i++) {
        
        if (s.parameters[i].discrete_flag) {
            int val = s.parameters[i].int_value;
            likelihood[s.belong_to][i].add(val);
        } else {
            double val = s.parameters[i].double_value;
            likelihood[s.belong_to][i].add(val);
        }
    }
    prior_count[s.belong_to]++;
}

void Simple_Bayes_Classifier::train(const char *path) {
    Sample_Reader  reader;
    reader.set_header(info.header);
    reader.open(path);
    prior_count = std::vector<int>(info.class_num, 0);
    likelihood = std::vector<std::vector<Likelihood> >(info.class_num);
    for (int i = 0; i < info.class_num; i++) {
        likelihood[i] = std::vector<Likelihood>(info.sample_size);
        for (int j = 0; j < info.sample_size; j++) {
            likelihood[i][j] = Likelihood(info.header[j]);
        }
    }
    for (int i = 0; i <info.sample_num; i++) {
        Sample s;
        reader.get(s);
        add_sample(s);
    }
    reader.close();
}
void Simple_Bayes_Classifier::classify(Sample &sample) {
    double mx = -1;
    int mx_arg = 0;
    for (int c = 0; c < info.class_num; c++) {
        double h = 1.0;
        for (int i = 0; i < info.sample_size; i++) {
            if (sample.parameters[i].discrete_flag) {
                int val = sample.parameters[i].int_value;
                h *= likelihood[c][i].query(val);
            } else {
                double val = sample.parameters[i].double_value;
                h *= likelihood[c][i].query(val);
            }
        }
        h *= 1.0* ( prior_count[c] + 1 ) / (info.sample_num + info.class_num); // 拉普拉斯修正
        if (h > mx) {
            mx = h;
            mx_arg = c;
        }
    }
    sample.belong_to = mx_arg;
}