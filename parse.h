#pragma once
#include "crop.h"
#include "negative.h"
#include "Sharpening.h"
#include "Grayscale.h"
#include "EdgeDetection.h"

#include <vector>
#include <string>
#include <memory>

struct ParsedRes {
    char* input_path;
    char* output_path;
    std::vector<std::string> filters;
};

ParsedRes Parse(int argc, char** argv);
std::vector<std::unique_ptr<BaseFilter> > Filters(int32_t sz, std::vector<std::string> fil);