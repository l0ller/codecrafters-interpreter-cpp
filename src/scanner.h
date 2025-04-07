#ifndef SCANNER_H
#define SCANNER_H

#include <string>


std::string read_file_contents(const std::string &filename, std::string &output_after_tokenize, int &exit_code);
void to_upper(std::string &str);
void to_lower(std::string &str);

#endif // SCANNER_H
