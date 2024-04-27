#include "image.h"
#include "parse.h"
int main(int argc, char** argv) {
    ParsedRes argument = Parse(argc, argv);
    Image image(0, 0);
    image.Read(argument.input_path);
    auto filters = Filters(static_cast<int32_t>(argument.filters.size()), argument.filters);
    for (size_t i = 0; i < filters.size(); ++i) {
        filters[i]->Apply(image);
    }
    image.Export(argument.output_path);
}
