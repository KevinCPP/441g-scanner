#include "test_regex.h"
#include <sstream>
#include <sstream>

std::string make_header(size_t num_dashes, std::string mid_text) {
    std::stringstream ss;
    for (size_t i = 0; i < num_dashes; i++)
        ss << "-";
    return ss.str() + mid_text + ss.str();
}

void test_vec(const std::regex& re, const std::vector<std::string>& strs) {
    std::smatch match;
    for (int i = 0; i < strs.size(); i++) {
        std::cout << "i=" << i << " | FULL STR: " << strs[i] << std::endl << '\t';
        if (std::regex_search(strs[i], match, re)) {
            std::cout << "Matched: " << match.str() << std::endl;
        } else {
            std::cout << "Didn't Match." << std::endl;
        }
    }
    std::cout << std::endl;
}
