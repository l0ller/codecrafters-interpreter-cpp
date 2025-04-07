#include "scanner.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include<bits/stdc++.h>


std::string read_file_contents(const std::string &filename, std::string &output_after_tokenize, int &exit_code) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }

    int line_number = 1;
    char ch, next_ch;
    std::string err = "";

    while (file.get(ch)) {
        next_ch = file.peek() != EOF ? file.peek() : '\0';

        if (ch == '\n') {
            line_number++;
            continue;
        }

        // Single-character tokens
        switch (ch) {
            case '(': output_after_tokenize += "LEFT_PAREN ( null\n"; break;
            case ')': output_after_tokenize += "RIGHT_PAREN ) null\n"; break;
            case '{': output_after_tokenize += "LEFT_BRACE { null\n"; break;
            case '}': output_after_tokenize += "RIGHT_BRACE } null\n"; break;
            case '*': output_after_tokenize += "STAR * null\n"; break;
            case '.': output_after_tokenize += "DOT . null\n"; break;
            case ',': output_after_tokenize += "COMMA , null\n"; break;
            case ';': output_after_tokenize += "SEMICOLON ; null\n"; break;
            case '+': output_after_tokenize += "PLUS + null\n"; break;
            case '-':
                if (next_ch == '>') {
                    output_after_tokenize += "ARROW -> null\n";
                    file.get(ch);
                } else {
                    output_after_tokenize += "MINUS - null\n";
                }
                break;
            case '/':
                if (next_ch == '/') {
                    while (file.get(ch) && ch != '\n');
                    line_number++;
                } else if (next_ch == '*') {
                    file.get(ch);
                    while (file.get(ch)) {
                        if (ch == '*' && file.peek() == '/') {
                            file.get(ch);
                            break;
                        }
                        if (ch == '\n') line_number++;
                    }
                } else {
                    output_after_tokenize += "SLASH / null\n";
                }
                break;
            case '=':
                if (next_ch == '=') {
                    output_after_tokenize += "EQUAL_EQUAL == null\n";
                    file.get(ch);
                } else {
                    output_after_tokenize += "EQUAL = null\n";
                }
                break;
            case '!':
                if (next_ch == '=') {
                    output_after_tokenize += "BANG_EQUAL != null\n";
                    file.get(ch);
                } else {
                    output_after_tokenize += "BANG ! null\n";
                }
                break;
            case '<':
                if (next_ch == '=') {
                    output_after_tokenize += "LESS_EQUAL <= null\n";
                    file.get(ch);
                } else {
                    output_after_tokenize += "LESS < null\n";
                }
                break;
            case '>':
                if (next_ch == '=') {
                    output_after_tokenize += "GREATER_EQUAL >= null\n";
                    file.get(ch);
                } else {
                    output_after_tokenize += "GREATER > null\n";
                }
                break;
            case '"': {
                std::string str = "";
                int terminated = 0;
                while (file.get(ch)) {
                    if (ch == '\n') line_number++;
                    if (ch == '"') {
                        terminated = 1;
                        break;
                    }
                    str += ch;
                }
                if (!terminated) {
                    err += "[line " + std::to_string(line_number) + "] Error: Unterminated string.\n";
                    exit_code = 65;
                } else {
                    output_after_tokenize += "STRING \"" + str + "\" " + str + "\n";
                }
                break;
            }
            case ' ':
            case '\t':
                break;
            default:
                if (isdigit(ch)) {
                    int dotflag = 0;
                    std::string num_str(1, ch);
                    if (next_ch == '.') {
                        dotflag = 1;
                        num_str += '.';
                        file.get(ch);
                    }
                    while (isdigit(file.peek())) {
                        file.get(ch);
                        num_str += ch;
                    }
                    if (dotflag) {
                        output_after_tokenize += "NUMBER " + num_str + " " + num_str + "\n";
                    } else {
                        output_after_tokenize += "NUMBER " + num_str + " " + num_str + ".0\n";
                    }
                } else if (isalpha(ch) || ch == '_') {
                    std::string id(1, ch);
                    while (isalnum(file.peek()) || file.peek() == '_') {
                        file.get(ch);
                        id += ch;
                    }

                    std::string kw = id;
                    to_lower(kw);
                    if (kw == "and" || kw == "class" || kw == "else" || kw == "false" || kw == "for" ||
                        kw == "fun" || kw == "if" || kw == "nil" || kw == "or" || kw == "print" ||
                        kw == "return" || kw == "super" || kw == "this" || kw == "true" ||
                        kw == "var" || kw == "while") {
                        std::string upper_id = id;
                        to_upper(upper_id);
                        output_after_tokenize += upper_id + " " + kw + " null\n";
                    } else {
                        output_after_tokenize += "IDENTIFIER " + id + " null\n";
                    }
                } else {
                    err += "[line " + std::to_string(line_number) + "] Error: Unexpected character: " + ch + "\n";
                    exit_code = 65;
                }
        }
    }

    std::cerr << err;
    file.close();
    return "";
}

void to_upper(std::string &str) {
    for (char &c : str)
        c = std::toupper(c);
}

void to_lower(std::string &str) {
    for (char &c : str)
        c = std::tolower(c);
}
