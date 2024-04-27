#include "parse.h"

ParsedRes Parse(int argc, char** argv) {
    ParsedRes answer;
    answer.input_path = argv[1];
    answer.output_path = argv[2];
    answer.filters = {};
    for (int i = 3; i < argc; ++i) {
        answer.filters.push_back(argv[i]);
    }
    return answer;
}

std::vector<std::unique_ptr<BaseFilter>> Filters(int32_t sz, std::vector<std::string> fil) {
    std::vector<std::unique_ptr<BaseFilter>> ans;
    for (int i = 0; i < sz; i++) {
        if (fil[i] == "-gs") {
            ans.push_back(std::make_unique<Grayscale>());
        }
        if (fil[i] == "-neg") {
            ans.push_back(std::make_unique<Negative>());
        }
        if (fil[i] == "-crop") {
            ans.push_back(std::make_unique<Crop>(stoi(fil[i + 1]), stoi(fil[i + 2])));
            i += 2;
            continue;
        }
        if (fil[i] == "-sharp") {
            ans.push_back(std::make_unique<Sharpenning>());
        }
        if (fil[i] == "-edge") {
            ans.push_back(std::make_unique<Grayscale>());
            ans.push_back(std::make_unique<EdgeDet>());
            ans.push_back(std::make_unique<EdgeDetTh>(stod(fil[i + 1])));
            i += 1;
            continue;
        }
    }
    return ans;
}