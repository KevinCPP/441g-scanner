#include "test_regex.h"

std::vector<std::string> make_test_ops(std::string op) {
    std::vector<std::string> res;
    res.push_back(op);
    res.push_back("a" + op + "b");
    res.push_back("a " + op + " b");
    if (op.size() > 1) {
        res.push_back(op.substr(0,1) + " " + op.substr(1));
        res.push_back("a" + op.substr(0,1) + " " + op.substr(1) + "b");
    }
    res.push_back("a\t" + op + "\tb");

    return res;
}

void test_operators() {
    std::cout << make_header(30, "TEST OPERATORS") << std::endl;
    test_vec(re_and, make_test_ops("&&"));
    test_vec(re_or, make_test_ops("||"));
    test_vec(re_neq, make_test_ops("!="));
    test_vec(re_eq, make_test_ops("=="));
    test_vec(re_geq, make_test_ops(">="));
    test_vec(re_gt, make_test_ops(">"));
    test_vec(re_leq, make_test_ops("<="));
    test_vec(re_lt, make_test_ops("<"));
    test_vec(re_sub, make_test_ops("-"));
    test_vec(re_add, make_test_ops("+"));
    test_vec(re_mod, make_test_ops("%"));
    test_vec(re_div, make_test_ops("/"));
    test_vec(re_mul, make_test_ops("*"));
    test_vec(re_xor, make_test_ops("^"));
    test_vec(re_not, make_test_ops("!"));
    test_vec(re_dec, make_test_ops("--"));
    test_vec(re_inc, make_test_ops("++"));
    test_vec(re_assign, make_test_ops("="));
    test_vec(re_semicolon, make_test_ops(";"));
    test_vec(re_comma, make_test_ops(","));
    test_vec(re_colon, make_test_ops(":"));
    test_vec(re_parenthesis_o, make_test_ops("("));
    test_vec(re_parenthesis_c, make_test_ops(")"));
    test_vec(re_squarebracket_o, make_test_ops("["));
    test_vec(re_squarebracket_c, make_test_ops("]"));
    test_vec(re_curlybrace_o, make_test_ops("{"));
    test_vec(re_curlybrace_c, make_test_ops("}"));
}
