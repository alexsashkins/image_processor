#include "Sharpening.h"

const std::array<std::array<float, 3>, 3> SHARP = {{{0, -1, 0}, {-1, 5, -1}, {-0, -1, 0}}};

Sharpenning::Sharpenning() : BaseFilterWMatr(SHARP) {
}
