#include "parser.h"
#include <iostream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>

void bang(std::istringstream& iss, std::string& output_after_parse);
void minus(std::istringstream& iss, std::string& output_after_parse);
void parse_group(std::istringstream& iss, std::string& output_after_parse) {
    output_after_parse += "(group ";
    std::string content;
    std::string line;

    while (std::getline(iss, line)) {
        std::istringstream inner_line_stream(line);
        std::string inner_token;
        std::vector<std::string> inner_tokens;

        while (inner_line_stream >> inner_token) {
            inner_tokens.push_back(inner_token);
        }

        if (inner_tokens.empty()) {
            continue;
        }

        if (inner_tokens[0] == "RIGHT_PAREN") {
            break;
        } 
        else  if(line == "");
        else if(inner_tokens[0] == "TRUE"){
            content += "true";
            content += " ";}
        else if(inner_tokens[0] == "FALSE"){
            content += "false";
            content += " ";}
        else if(inner_tokens[0] == "NIL"){
            content += "nil";
            content += " ";}
        else if(inner_tokens[0] == "ELSE" || inner_tokens[0] == "IF"|| inner_tokens[0] =="VAR" || inner_tokens[0] == "WHILE"|| inner_tokens[0] == "FOR"|| inner_tokens[0] == "FUN"|| inner_tokens[0] == "RETURN" || inner_tokens[0] == "SUPER"|| inner_tokens[0] == "AND"|| inner_tokens[0] == "OR" || inner_tokens[0] == "CLASS" || inner_tokens[0] == "PRINT" || inner_tokens[0] == "THIS"){
            content += line ;
            content += " ";}
        else if(inner_tokens[0] == "NUMBER"){
            content += inner_tokens[2] ;
            content += " ";}
        else if (inner_tokens[0] == "STRING"){
            std::string str = line.substr(line.find('"') + 1, line.rfind('"') - line.find('"') - 1);
            content += str ;
            content += " ";}
        else if(inner_tokens[0] == "IDENTIFIER"){
            content += inner_tokens[2] ;
            content += " ";}
        else if(inner_tokens[0] == "IDENTIFIER"  || inner_tokens[0] == "STRING"){
            content += line ;
            content += " ";}
        else if (inner_tokens[0] == "LEFT_PAREN") {
            parse_group(iss, content);
            content += " ";}
        else if(inner_tokens[0] == "BANG"){
            bang(iss, content);
            content += " ";}
        else if(inner_tokens[0] == "MINUS"){
            minus(iss, content);            
            content += " ";}
        else if(inner_tokens[0] == "LEFT_PAREN" || inner_tokens[0] == "RIGHT_PAREN" || inner_tokens[0] == "LEFT_BRACE" || inner_tokens[0] == "RIGHT_BRACE" || inner_tokens[0] == "STAR" || inner_tokens[0] == "DOT" || inner_tokens[0] == "COMMA" || inner_tokens[0] == "SEMICOLON" || inner_tokens[0] == "PLUS" || inner_tokens[0] == "MINUS" || inner_tokens[0] == "ARROW ->"){
            content += line;
            content += " ";
        }
    }

    content = content.substr(0, content.size() - 1); // Remove trailing space
    output_after_parse += content + ")";
}


void bang(std::istringstream& iss, std::string& output_after_parse) {
    output_after_parse += "(! "; // Start the BANG group
    std::string innerline;

    while (std::getline(iss, innerline)) {
        std::istringstream inner_line_stream(innerline);
        std::string inner_token;
        std::vector<std::string> inner_tokens;

        while (inner_line_stream >> inner_token) {
            inner_tokens.push_back(inner_token);
        }

        if (inner_tokens.empty()) {
            continue;
        }

        if (inner_tokens[0] == "TRUE") {
            output_after_parse += "true";
            break;
        } else if (inner_tokens[0] == "FALSE") {
            output_after_parse += "false";
            break;
        } else if (inner_tokens[0] == "BANG") {
            bang(iss, output_after_parse); // Recursively handle nested BANG
            break;
        } else if (inner_tokens[0] == "LEFT_PAREN") {
            parse_group(iss, output_after_parse); // Handle nested group
            break;
        }
    }

    output_after_parse += ")"; // Close the BANG group
}

void minus(std::istringstream& iss, std::string& output_after_parse){
    std::string innercontent;
    std::string innerline;
  
    getline(iss, innerline);
    std::istringstream inner_line_stream(innerline);
    std::string inner_token;
    std::vector<std::string> inner_tokens;

    while (inner_line_stream >> inner_token) {
        inner_tokens.push_back(inner_token);
    }
    if(inner_tokens[0] == "NUMBER") 
        innercontent += "(- " + inner_tokens[2] + ")";
    // else if(inner_tokens[0] == "IDENTIFIER") 
    //     innercontent += "(- " + inner_tokens[2] + ")";
    else if(inner_tokens[0] == "MINUS"){
        innercontent += "(- ";
        minus(iss, innercontent);    
        innercontent += ")";
    }
    else if (inner_tokens[0] == "LEFT_PAREN") {
        parse_group(iss, innercontent);
        innercontent += " ";}
    // else {
    //     innercontent += "MINUS -";
    // }
    output_after_parse += innercontent;
}



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
            output_after_parse += tokens[2] + "\n";
        }
        else if (tokens[0] == "STRING"){
            std::string str = line.substr(line.find('"') + 1, line.rfind('"') - line.find('"') - 1);
            output_after_parse += str + "\n";
        }
        else if(tokens[0] == "IDENTIFIER"){
            output_after_parse += tokens[2] + "\n";
        }
        else if(tokens[0] == "IDENTIFIER"  || tokens[0] == "STRING"){
            output_after_parse += line + "\n";
        }
        else if (tokens[0] == "LEFT_PAREN") {
            parse_group(iss, output_after_parse);
            output_after_parse += "\n";
        }
        else if(tokens[0] == "BANG"){
            bang(iss, output_after_parse);
            output_after_parse += "\n";
            
        }
        else if(tokens[0] == "MINUS"){
            minus(iss, output_after_parse);
            output_after_parse += "\n";            
        }

        else if(tokens[0] == "STAR" || tokens[0] == "DOT" || tokens[0] == "PLUS"){
            output_after_parse += line + "\n";
        }

        else if(tokens[0] == "LEFT_PAREN (" || tokens[0] == "RIGHT_PAREN )" || tokens[0] == "LEFT_BRACE {" || tokens[0] == "RIGHT_BRACE }" || tokens[0] == "STAR *" || tokens[0] == "DOT ." || tokens[0] == "COMMA ," || tokens[0] == "SEMICOLON ;" || tokens[0] == "PLUS +" || tokens[0] == "MINUS -" || tokens[0] == "ARROW ->"){
            output_after_parse += line + "\n";
        }
        

    }


    std::cerr << "Parser not implemented." << std::endl;

}
