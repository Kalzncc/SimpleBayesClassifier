#include "Sample_Reader.h"
void Sample_Reader::set_header(std::vector<int> header) {
    this->header = header;
}
int Sample_Reader::open(const char *fileDir) {
    if ( (fp = fopen(fileDir, "r")) <= 0) {
        return -1;
    }
    return 0;
}
int Sample_Reader::get(Sample &s, bool classify_flag) {
    s = Sample();
    for (int i = 0; i < header.size(); i++) {
        if (header[i] != 0) {
            int value; fscanf(fp, "%d", &value);
            s.add_parameter(value);
        } else {
            double value; fscanf(fp, "%lf", &value);
            s.add_parameter(value);
        }            
    }
    if (classify_flag) {
        int belong_to; fscanf(fp, "%d", &belong_to);
        s.belong_to = belong_to;
    }
    return 0;
}
void Sample_Reader::close() {
    fclose(fp);
}
