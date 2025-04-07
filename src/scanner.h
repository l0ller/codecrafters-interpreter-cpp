#ifndef SCANNER_H
#define SCANNER_H

#include <string>

extern std::string output_after_tokenize;
extern int exit_code;

std::string read_file_contents(const std::string &filename);
void to_upper(std::string &str);
void to_lower(std::string &str);

#endif // SCANNER_H
