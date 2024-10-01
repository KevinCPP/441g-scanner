#include "scanner.hpp"
#include "token.hpp"
#include <optional>
#include <stdexcept>
#include <string>

namespace {
    // comments
    // source: https://stackoverflow.com/questions/13014947/regex-to-match-a-c-style-multiline-comment
//    static const std::regex re_comment_ml(R"(/\*[^*]*\*+(?:[^/*][^*]*\*+)*/)");
//    static const std::regex re_comment_sl(R"(//.*)");
//    // operators
//    static const std::regex re_and(R"(&&)");
//    static const std::regex re_or(R"(\|\|)");
//    static const std::regex re_neq(R"(!=)");
//    static const std::regex re_eq(R"(==)");
//    static const std::regex re_geq(R"(>=)");
//    static const std::regex re_gt(R"(>)");
//    static const std::regex re_leq(R"(<=)");
//    static const std::regex re_lt(R"(<)");
//    static const std::regex re_sub(R"(-)");
//    static const std::regex re_add(R"(\+)");
//    static const std::regex re_mod(R"(%)");
//    static const std::regex re_div(R"(/)");
//    static const std::regex re_mul(R"(\*)");
//    static const std::regex re_xor(R"(\^)");
//    static const std::regex re_not(R"(!)");
//    static const std::regex re_dec(R"(--)");
//    static const std::regex re_inc(R"(\+\+)");
//    static const std::regex re_assign(R"(=)");
//    static const std::regex re_semicolon(R"(;)");
//    static const std::regex re_comma(R"(,)");
//    static const std::regex re_colon(R"(:)");
//    static const std::regex re_parenthesis_o(R"(\()");
//    static const std::regex re_parenthesis_c(R"(\))");
//    static const std::regex re_squarebracket_o(R"(\[)");
//    static const std::regex re_squarebracket_c(R"(\])");
//    static const std::regex re_curlybrace_o(R"(\{)");
//    static const std::regex re_curlybrace_c(R"(\})");
    // keywords
    static const std::regex re_keyword(R"(as|array|boolean|char|else|float|for|function|if|integer|print|return|string|void|and|not|or)");
    // identifier
    static const std::regex re_identifier(R"([a-zA-Z]+[a-zA-Z0-9_]*)");
    // literals
    static const std::regex re_literal_bool(R"(true|false)");
    static const std::regex re_literal_int(R"([0-9]+)");
    //static const std::regex re_literal_char(R"('\\[tn'\\]|[^'\\]')");
    static const std::regex re_literal_char(R"('(?:\\[tn'\\]|[^'\\])')");
    // idea: if re_literal_char matches, assume it's valid. If re_literal_char doesn't match but re_invalid_char does, assume it's an invalid char.
    static const std::regex re_invalid_char(R"('.*')");
    static const std::regex re_literal_str(R"("(\\[tn"\\]|[^"\\])*")");
    static const std::regex re_literal_float(R"([0-9]*\.[0-9]+)");
    static const std::regex re_whitespace(R"(\s+)");

    std::vector<std::regex> re_comments = {
        std::regex(R"(/\*[^*]*\*+(?:[^/*][^*]*\*+)*/)"),
        std::regex(R"(//.*)"),
    };

    std::vector<std::regex> re_operators = {
        std::regex(R"(&&)"),
        std::regex(R"(\|\|)"),
        std::regex(R"(!=)"),
        std::regex(R"(==)"),
        std::regex(R"(>=)"),
        std::regex(R"(>)"),
        std::regex(R"(<=)"),
        std::regex(R"(<)"),
        std::regex(R"(-)"),
        std::regex(R"(\+)"),
        std::regex(R"(%)"),
        std::regex(R"(/)"),
        std::regex(R"(\*)"),
        std::regex(R"(\^)"),
        std::regex(R"(!)"),
        std::regex(R"(--)"),
        std::regex(R"(\+\+)"),
        std::regex(R"(=)"),
        std::regex(R"(;)"),
        std::regex(R"(,)"),
        std::regex(R"(:)"),
        std::regex(R"(\()"),
        std::regex(R"(\))"),
        std::regex(R"(\[)"),
        std::regex(R"(\])"),
        std::regex(R"(\{)"),
        std::regex(R"(\})"),
    };
}

/* Public */

Scanner::Scanner(std::istream & stream) {
        read_input(stream);
    };

bool Scanner::has_next() {
    return not input_text.empty();
}

std::smatch re_vec(const std::vector<std::regex>& regexes, const std::string& input, size_t pos) {
    std::smatch res;
    size_t maxl = 0;
    std::string sub_input = input.substr(pos);
    for (const auto& re : regexes) {
        std::smatch cur_match;
        if (std::regex_search(sub_input, cur_match, re) && cur_match.position(0) == 0) {
            if (cur_match.length() > maxl) {
                res = cur_match;
                maxl = cur_match.length();
            }
        }
    }
    return res;
}

std::pair<int, int> newlines_and_cur_col(const std::string& input, size_t start_pos, size_t end_pos) {
    if (start_pos >= input.length() || end_pos > input.length() || end_pos <= start_pos) {
        return {0,0};
    }

    int line = 0;
    int col = 0;

    for (size_t i = start_pos; i < end_pos; i++) {
        if (input[i] == '\n') {
            line += 1;
            col = 0;
        } else {
            col += 1;
        }
    }

    return {line, col};
}

struct bt_info {
    std::pair<int, int> start;
    std::pair<int, int> end;
    std::string val;
};

std::optional<bt_info> get_info(std::smatch& m, const std::string& it, size_t& pos, size_t& cur_line, size_t& cur_col) {
    if (!m.empty()) {
        size_t new_pos = pos + m.length();
        auto lc_offset = newlines_and_cur_col(it, pos, new_pos);
        size_t new_line = cur_line + lc_offset.first;
        size_t new_col = lc_offset.second;

        bt_info bt;
        bt.start = {cur_line, cur_col};
        bt.end = {new_line, new_col};
        bt.val = m.str();

        pos += m.length();
        cur_line = new_line;
        cur_col = new_col;
        return bt;
    }
    return std::nullopt;
}

static size_t pos = 0;
static size_t cur_line = 0;
static size_t cur_col = 0;
// Complete this method
token_ty Scanner::next() {
    // handle whitespace
    std::smatch m = re_vec({re_whitespace}, input_text, pos);
    // this will update the pos, cur_line, and cur_col to consume whitespace
    get_info(m, input_text, pos, cur_line, cur_col);

    // handle comment
    m = re_vec(re_comments, input_text, pos);
    auto t = get_info(m, input_text, pos, cur_line, cur_col);
    if (t)
        return comment_token{t->start, t->end, t->val};
    
    // handle keywords
    m = re_vec({re_keyword}, input_text, pos);
    t = get_info(m, input_text, pos, cur_line, cur_col);
    if (t)
        return keyword_token{t->start, t->end, t->val};

    m = re_vec({re_identifier}, input_text, pos);
    t = get_info(m, input_text, pos, cur_line, cur_col);
    if (t)
        return id_token{t->start, t->end, t->val};

    m = re_vec(re_operators, input_text, pos);
    t = get_info(m, input_text, pos, cur_line, cur_col);
    if (t)
        return symbol_token{t->start, t->end, t->val};

    m = re_vec({re_literal_int}, input_text, pos);
    t = get_info(m, input_text, pos, cur_line, cur_col);
    if (t)
        return int_token{t->start, t->end, std::stoi(t->val)};
    
    m = re_vec({re_literal_float}, input_text, pos);
    t = get_info(m, input_text, pos, cur_line, cur_col);
    if (t)
        return float_token{t->start, t->end, (float)std::stod(t->val)};
    
    m = re_vec({re_literal_str}, input_text, pos);
    t = get_info(m, input_text, pos, cur_line, cur_col);
    if (t)
        return string_token{t->start, t->end, t->val};
    
    m = re_vec({re_literal_char}, input_text, pos);
    t = get_info(m, input_text, pos, cur_line, cur_col);
    if (t) {
        return char_token{t->start, t->end, t->val[t->val.length()-2]};
    } else {
        m = re_vec({re_invalid_char}, input_text, pos);
        t = get_info(m, input_text, pos, cur_line, cur_col);
        if (t) {
            return error_token{t->start, t->end, "invalid char"};
        }
    }

    pos += 1;

    if (pos >= input_text.length()) {
        input_text = "";
        return end_of_input{};
    }

    auto lc_offset = newlines_and_cur_col(input_text, pos-1, pos);
    size_t new_line = cur_line + lc_offset.first;
    size_t new_col = lc_offset.second;
    error_token et = {{cur_line,cur_col}, {new_line,new_col}, input_text.substr(pos-1,pos)};
    cur_line = new_line;
    cur_col = new_col;
    return et;
}


/* Private */
void Scanner::read_input(std::istream & stream) {
   constexpr auto read_size = std::size_t{4096};
   stream.exceptions(std::ios_base::badbit);
   //auto out = std::string{};
   auto buf = std::string(read_size, '\0');
   while (stream.read(& buf[0], read_size)) {
       input_text.append(buf, 0, stream.gcount());
   }
   input_text.append(buf, 0, stream.gcount());
}

Scanner::position Scanner::end_position_of(std::string text) {
    if (text.length() == 0) {
        return current_position;
    }
    auto end_position = current_position;
    for (auto& i : text.substr(0, text.length()-1)) {
        if (i == '\n') {
            end_position.first++;
            end_position.second = 1;
        }
        else {
            end_position.second++;
        }
    }
    return end_position;
} // end_position_of


Scanner::position Scanner::position_after(std::string text) {
    auto new_position = current_position;
    for (auto& i : text) {
        if (i == '\n') {
            new_position.first++;
            new_position.second = 1;
        }
        else {
            new_position.second++;
        }
    }

    return new_position;
} // position_after

// Complete these methods

// Methods to process literal tokens
bool Scanner::process_int_lit   (std::smatch match, token_ty& token) {
    return true;
}

bool Scanner::process_float_lit (std::smatch match, token_ty& token) {
    return true;
}

bool Scanner::process_char_lit  (std::smatch match, token_ty& token) {
    return true;
}

bool Scanner::process_string_lit(std::smatch match, token_ty& token) {
    return true;
}

bool Scanner::process_bool_lit  (std::smatch match, token_ty& token) {
    return true;
}

template<typename TokenType>
bool Scanner::default_rule      (std::smatch match, token_ty& token) {
    return true;
}

bool Scanner::default_ignore    (std::smatch match, token_ty& token) {
    return true;
}
