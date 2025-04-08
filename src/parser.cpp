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
        std::istringstream line_stream(line); // stream for current line
        std::string token;
        std::vector<std::string> tokens; // to hold tokens for this line
        while (line_stream >> token) {
            tokens.push_back(token);
        }
    

        if(line == "");
        else if(tokens[0] == "TRUE"){
            output_after_parse += "true\n";
        }
        else if(tokens[0] == "FALSE"){
            output_after_parse += "false\n";
        }
        else if(tokens[0] == "NIL"){
            output_after_parse += "nil\n";
        }
        else if(tokens[0] == "ELSE" || tokens[0] == "IF"|| line =="VAR" || tokens[0] == "WHILE"|| tokens[0] == "FOR"|| tokens[0] == "FUN"|| tokens[0] == "RETURN" || tokens[0] == "SUPER"|| tokens[0] == "AND"|| tokens[0] == "OR" || tokens[0] == "CLASS" || tokens[0] == "PRINT" || tokens[0] == "THIS"){
            output_after_parse += line + "\n";
        }
        else if(tokens[0] == "NUMBER"){
            output_after_parse += tokens[1] + "\n";
        }
        else if(tokens[0] == "IDENTIFIER"  || tokens[0] == "STRING"){
            output_after_parse += line + "\n";
        }
        else if(tokens[0] == "LEFT_PAREN (" || tokens[0] == "RIGHT_PAREN )" || tokens[0] == "LEFT_BRACE {" || tokens[0] == "RIGHT_BRACE }" || tokens[0] == "STAR *" || tokens[0] == "DOT ." || tokens[0] == "COMMA ," || tokens[0] == "SEMICOLON ;" || tokens[0] == "PLUS +" || tokens[0] == "MINUS -" || tokens[0] == "ARROW ->"){
            output_after_parse += line + "\n";
        }
        
    }

    std::cerr << "Parser not implemented." << std::endl;

}
