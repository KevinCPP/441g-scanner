#include "test_regex.h"

void test_literals() {
    std::cout << make_header(25, "TEST LITERALS") << std::endl;

    std::vector<std::string> bool_literals = {
        "bool a = true;",
        "bool b = false;",
        "true ^ false",
    };

    std::vector<std::string> int_literals = {
        "int x = 10;",
        "int y = 1;",
        "int z = 2147483647 + 1;",
    };

    std::vector<std::string> float_literals = {
        "float d = .75",
        "float d2 = 0.83",
        "float d3 = 101.250",
    };

    std::vector<std::string> char_literals = {
        "'a'",
        "char c1 = 'x';",
        "char c2 = 'y';",
        R"(char newline = '\n')",
        R"(char tab = '\t')",
        R"(char backslash = '\\')",
        R"(char apostrophe = '\'')",
        R"(char invalid = 'aa')",
        R"(char invalid = '\\\\')",
        R"(char invalid = '\n\n')",
    };

    std::vector<std::string> str_literals = {
        R"(string s = "the \n quick \t brown \\ fox \" jumps over the lazy dog";)",
        R"(string s2 = "the \ quick brown fox "")", // should not work due to unescaped `\` and `"`
    };

    test_vec(re_literal_bool, bool_literals);
    test_vec(re_literal_int, int_literals);
    test_vec(re_literal_float, float_literals);
    test_vec(re_literal_char, char_literals);
    test_vec(re_literal_str, str_literals);
    test_vec(re_invalid_char, char_literals);
}
