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
        else if(line == "ELSE else null" || line == "IF if null"|| line =="VAR var null" || line == "WHILE while null"|| line == "FOR for null"|| line == "FUN fun null"|| line == "RETURN return null" || line == "SUPER super null"){
            output_after_parse += line + "\n";
        }
        else if(line == "IDENTIFIER" || line == "NUMBER" || line == "STRING"){
            output_after_parse += line + "\n";
        }
        else if(line == "LEFT_PAREN (" || line == "RIGHT_PAREN )" || line == "LEFT_BRACE {" || line == "RIGHT_BRACE }" || line == "STAR *" || line == "DOT ." || line == "COMMA ," || line == "SEMICOLON ;" || line == "PLUS +" || line == "MINUS -" || line == "ARROW ->"){
            output_after_parse += line + "\n";
        }
        
    }

    std::cerr << "Parser not implemented." << std::endl;

}
