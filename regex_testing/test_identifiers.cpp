#include "test_regex.h"

void test_identifiers() {
    std::cout << make_header(25, "TEST IDENTIFIERS") << std::endl;

    std::vector<std::string> identifiers = {
        "valid_identifier1",
        "v4l1d_1d3n71f13r",
        "valid_identifier",
        "v",
        "_invalid",
        "0invalid",
        "0_invalid",
        "_0invalid",
        "invalid*identifier",
        "invalid#",
        "invalid!",
        "invalid@",
        "invalid$",
    };

    test_vec(re_identifier, identifiers);
}
