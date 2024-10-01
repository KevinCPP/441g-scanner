#include "test_regex.h"

void test_comments() {
    std::cout << make_header(25, "TEST COMMENTS") << std::endl;
    std::vector<std::string> single_lines = {
        R"(//hello world)",
        R"(// hello world)",
        R"(   // the quick brown fox jumps over the lazy dog)",
        R"(//)",
        R"(/ the quick brown fox / jumps over the)",
        R"(int c = 10; // initialize the counter to 10)",
    };
    
    std::vector<std::string> multi_lines = {
        R"(
            /* This is a multi-line comment
            * Let's see if it is matched by the regex.
            * Best Games: Persona 4 golden, Final Fantasy 7 */
        )",
        R"(
            /*
            * This is another multi-line comment.
            * Let's see if it is matched by the regex.
            * Ate for Breakfast: "Cheeseburger Omelete"
            */
        )",
        R"(
            /* multi line comment syntax being used         for a single line? */
        )",
        R"(
            /**/
        )",
        R"(
            int c = 10; /* initialize the counter to 10 */
        )",
        R"(
            int c = 10; /* initialize the counter
        * to 10. What is this counter used for?
        * TODO: figure out why changing this variable
        * causes a segmentation fault. */
        )",
    };

    std::cout << "SINGLE LINES:" << std::endl;
    test_vec(re_comment_sl, single_lines);
    std::cout << "MULTI LINES:" << std::endl;
    test_vec(re_comment_ml, multi_lines);
}
