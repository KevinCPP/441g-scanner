#include "test_regex.h"

namespace { 
    std::vector<std::string> keywords = 
    {
        "as",
        "array",
        "boolean",
        "char",
        "else",
        "float",
        "for",
        "function",
        "if",
        "integer",
        "print",
        "return",
        "string",
        "void",
        "and",
        "not",
        "or",
    };
}

void test_keywords() {
    std::cout << make_header(25, "TEST KEYWORDS") << std::endl;
    test_vec(re_keyword, keywords);
}
