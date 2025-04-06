#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <bits/stdc++.h>
int exit_code = 0;
std::string output_after_tokenize = "";
void parse_tokens();
std::string read_file_contents(const std::string &filename);
void to_upper(std::string &str);
void to_lower(std::string &str);
int main(int argc, char *argv[])
{
    // Disable output buffering
   // std::cout << std::unitbuf;
   // std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3)
    {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return 1;
    }

    const std::string command = argv[1];

    if (command == "tokenize")
    {
        std::string file_contents = read_file_contents(argv[2]);

        // Uncomment this block to pass the first stage
        //
        if (!file_contents.empty())
        {
            std::cerr << "Scanner not implemented" << std::endl;
            return 1;
        }
        // git commit -am "[any message]" std::cout << "EOF  null" << std::endl; // Placeholder, remove this line when implementing the scanner
    } 
    else if(command == "parse"){
        std::string file_contents = read_file_contents(argv[2]);
        void parse_tokens();

    }
    else
    {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return exit_code;
}

std::string read_file_contents(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }
    int line_number = 1;
    char ch;
    
    std::string err = "";
    char prev;
    char next_ch;

while (file.get(ch)) {
    // Peek at the next character
    if (file.peek() != EOF)
        next_ch = file.peek();
    else
        next_ch = '\0';  // Indicate end of file

    if (ch == '\n') {
        line_number++;
        continue;
    }

    if (ch == '(')
        output_after_tokenize += "LEFT_PAREN ( null\n";
    else if (ch == ')')
        output_after_tokenize += "RIGHT_PAREN ) null\n";
    else if (ch == '{')
        output_after_tokenize += "LEFT_BRACE { null\n";
    else if (ch == '}')
        output_after_tokenize += "RIGHT_BRACE } null\n";
    else if (ch == '*')
        output_after_tokenize += "STAR * null\n";
    else if (ch == '.')
        output_after_tokenize += "DOT . null\n";
    else if (ch == ',')
        output_after_tokenize += "COMMA , null\n";
    else if (ch == ';')
        output_after_tokenize += "SEMICOLON ; null\n";
    else if (ch == '+')
        output_after_tokenize += "PLUS + null\n";
    else if (ch == '-')
        output_after_tokenize += "MINUS - null\n";
    else if (ch == '/'){
        if(next_ch == '/'){
            while (file.get(ch) && ch != '\n') {
                // Skip the rest of the line
            }
            line_number++;
        } 
        else if (next_ch == '*'){
            file.get(ch);  // Consume the '*'
            while (file.get(ch)) {
                if (ch == '*' && file.peek() == '/') {
                    file.get(ch);  // Consume the '/'
                    break;
                }
                if (ch == '\n') {
                    line_number++;
                }
            }
        } 
        else
            output_after_tokenize += "SLASH / null\n";
        }
    
    else if (ch == '=') {
        if (next_ch == '=') {
            output_after_tokenize += "EQUAL_EQUAL == null\n";
            file.get(ch);  // Consume the next '='
        } else {
            output_after_tokenize += "EQUAL = null\n";
        }
    }
    else if (ch == '!'){
        if (next_ch == '=') {
            output_after_tokenize += "BANG_EQUAL != null\n";
            file.get(ch);  // Consume the next '!'
        } else {
            output_after_tokenize += "BANG ! null\n";
        }
    }
    else if (ch == '-'){
        if (next_ch == '>') {
            output_after_tokenize += "ARROW -> null\n";
            file.get(ch);  // Consume the next '>'
        } else {
            output_after_tokenize += "MINUS - null\n";
        }
    }
    //string
    else if (ch == '"') {
        std::string str = "";
        int temp = 0;
        int terminated = 0;
        while (file.get(ch)) {
                       
            if (ch == '\n') {
                temp++;
            }
            if(ch == '"'){
                terminated = 1;
                break;
            }
            str += ch;
        }
        if (terminated == 0) {
            err += "[line " + std::to_string(line_number) + "] Error: Unterminated string.\n";
            exit_code = 65;
            line_number+=temp;
        }
        else
        output_after_tokenize += "STRING \"" + str + "\" " + str + "\n";
    }
    //literal no.
    else if (isdigit(ch)) {
        int dotflag = 0;
        std::string num_str(1, ch);
        if(next_ch == '.'){
            dotflag = 1;
            num_str += '.';
            file.get(ch);  // Consume the '.'
        }
        while (isdigit(next_ch)) {
            file.get(ch);
            num_str += ch;
            next_ch = file.peek();
            if(next_ch == '.'&& dotflag == 0){
                dotflag = 1;
                num_str += '.';
                file.get(ch);  // Consume the '.'
            }
            next_ch = file.peek();
        }

        if(dotflag == 1){
            output_after_tokenize += "NUMBER " + num_str ;
            while (num_str.back() == '0'){
                num_str.pop_back();
            }
            if(num_str.back() == '.'){
                num_str.push_back('0');
            }
            output_after_tokenize +=  " " + num_str + "\n";
        }
        else
        output_after_tokenize += "NUMBER " + num_str + " " + num_str + ".0\n";
    }
    //identifier
    else if (isalpha(ch) || ch == '_') {
        std::string id = "";
        id += ch;
        while (isalnum(next_ch) || next_ch == '_') {
            file.get(ch);
            id += ch;
            next_ch = file.peek();
        }

        if(id == "and" || id == "class" ||id == "else"||id == "false"||id == "for"||id == "fun"||id == "if"||id == "nil"||id == "or"||id == "print"||id == "return"||id == "super"||id == "this"||id == "true"||id == "var"||id == "while"){
            to_upper(id);
            output_after_tokenize+= id + " ";
            to_lower(id);
            output_after_tokenize += id + " null\n";
        }
        else
        output_after_tokenize += "IDENTIFIER " + id + " null\n";
    }
    else if (ch == '<'){
        if (next_ch == '='){
            output_after_tokenize+= "LESS_EQUAL <= null\n";
            file.get(ch);  // Consume the next '='
        }
      
        else
        output_after_tokenize += "LESS < null\n";
    }
        
    else if (ch == '>'){
        if (next_ch == '='){
            output_after_tokenize+= "GREATER_EQUAL >= null\n";
            file.get(ch);  // Consume the next '='
        }

        else
        output_after_tokenize += "GREATER > null\n";
        
    }
    else if (ch == ' '|| ch == '\t'){

    }
    else {
        err += "[line " + std::to_string(line_number) + "] Error: Unexpected character: " + ch + "\n";
        exit_code = 65;
    }
}

    std::cerr << err;
    //std::cout << output_after_tokenize; 
    //std::cout << "EOF  null" << std::endl; 

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

// Function to convert a string to uppercase
void to_upper(std::string &str) {
    for (char &c : str) {
        c = std::toupper(c);
    }
    
}
// Function to convert a string to lowercase
void to_lower(std::string &str) {
    for (char &c : str) {
        c = std::tolower(c);
    }
    
}


void parse_tokens(){
    std::vector<std::string> token;
    std::stringstream ss(output_after_tokenize);
    std::string line;
    std::string ans = "";
    while(std::getline(ss, line)){
        token.push_back(line);
    }
    for(int i = 0; i < token.size(); i++){

        std::cerr << token[i] << std::endl;
        if (token[i] == "TRUE true null"){
            ans += "true/n";
        }
        if (token[i] == "FALSE false null"){
            ans += "false/n";
        }
        if (token[i] == "NIL nil null"){
            ans += "nil/n";
        }

    }
    std::cerr<< ans << std::endl;
   // std::cout << "EOF  null" << std::endl;
    
}
