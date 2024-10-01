#ifndef TEST_REGEX_H
#define TEST_REGEX_H

#include <regex>
#include <string>
#include <iostream>

// comments
// source: https://stackoverflow.com/questions/13014947/regex-to-match-a-c-style-multiline-comment
static const std::regex re_comment_ml(R"(/\*[^*]*\*+(?:[^/*][^*]*\*+)*/)");
static const std::regex re_comment_sl(R"(//.*)");
// operators
static const std::regex re_and(R"(&&)");
static const std::regex re_or(R"(\|\|)");
static const std::regex re_neq(R"(!=)");
static const std::regex re_eq(R"(==)");
static const std::regex re_geq(R"(>=)");
static const std::regex re_gt(R"(>)");
static const std::regex re_leq(R"(<=)");
static const std::regex re_lt(R"(<)");
static const std::regex re_sub(R"(-)");
static const std::regex re_add(R"(\+)");
static const std::regex re_mod(R"(%)");
static const std::regex re_div(R"(/)");
static const std::regex re_mul(R"(\*)");
static const std::regex re_xor(R"(\^)");
static const std::regex re_not(R"(!)");
static const std::regex re_dec(R"(--)");
static const std::regex re_inc(R"(\+\+)");
static const std::regex re_assign(R"(=)");
static const std::regex re_semicolon(R"(;)");
static const std::regex re_comma(R"(,)");
static const std::regex re_colon(R"(:)");
static const std::regex re_parenthesis_o(R"(\()");
static const std::regex re_parenthesis_c(R"(\))");
static const std::regex re_squarebracket_o(R"(\[)");
static const std::regex re_squarebracket_c(R"(\])");
static const std::regex re_curlybrace_o(R"(\{)");
static const std::regex re_curlybrace_c(R"(\})");
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

std::string make_header(size_t num_dashes, std::string mid_text);
void test_vec(const std::regex& re, const std::vector<std::string>& strs);
void test_comments();
void test_operators();
void test_keywords();
void test_identifiers();
void test_literals();

#endif
