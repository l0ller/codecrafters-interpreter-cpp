#include "parser.h"
#include <iostream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>

// Dummy function for now
void parse_tokens(std::string&output_after_tokenize,std::string&output_after_parse) {
    std::istringstream iss(output_after_tokenize);
    std::string line;

    while (std::getline(iss, line)) {
        if(line == "");
        else if(line == "TRUE true null"){
            output_after_parse += "true\n";
        }
        else if(line == "FALSE false null"){
            output_after_parse += "false\n";
        }
        else if(line == "NIL nil null"){
            output_after_parse += "nil\n";
        }
        else
        output_after_parse += line + "\n";
        
    }

    std::cerr << "Parser not implemented." << std::endl;

}
