#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
int exit_code = 0;
std::string read_file_contents(const std::string &filename);

int main(int argc, char *argv[])
{
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

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
    std::string ans = "";
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
        ans += "LEFT_PAREN ( null\n";
    else if (ch == ')')
        ans += "RIGHT_PAREN ) null\n";
    else if (ch == '{')
        ans += "LEFT_BRACE { null\n";
    else if (ch == '}')
        ans += "RIGHT_BRACE } null\n";
    else if (ch == '*')
        ans += "STAR * null\n";
    else if (ch == '.')
        ans += "DOT . null\n";
    else if (ch == ',')
        ans += "COMMA , null\n";
    else if (ch == ';')
        ans += "SEMICOLON ; null\n";
    else if (ch == '+')
        ans += "PLUS + null\n";
    else if (ch == '-')
        ans += "MINUS - null\n";
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
            ans += "SLASH / null\n";
        }
    
    else if (ch == '=') {
        if (next_ch == '=') {
            ans += "EQUAL_EQUAL == null\n";
            file.get(ch);  // Consume the next '='
        } else {
            ans += "EQUAL = null\n";
        }
    }
    else if (ch == '!'){
        if (next_ch == '=') {
            ans += "BANG_EQUAL != null\n";
            file.get(ch);  // Consume the next '!'
        } else {
            ans += "BANG ! null\n";
        }
    }
    else if (ch == '-'){
        if (next_ch == '>') {
            ans += "ARROW -> null\n";
            file.get(ch);  // Consume the next '>'
        } else {
            ans += "MINUS - null\n";
        }
    }
    else if (ch == '"') {
        std::string str = "";
        while (file.get(ch) && ch != '"') {
            str += ch;
        }
        ans += "STRING " +"\"" + str + "\"" + str + "\n";
    }
    else if (isdigit(ch)) {
        std::string num_str(1, ch);
        while (isdigit(next_ch)) {
            file.get(ch);
            num_str += ch;
            next_ch = file.peek();
        }
        ans += "NUMBER " + num_str + "\n";
    }
    else if (isalpha(ch) || ch == '_') {
        std::string id(1, ch);
        while (isalnum(next_ch) || next_ch == '_') {
            file.get(ch);
            id += ch;
            next_ch = file.peek();
        }
        ans += "IDENTIFIER " + id + "\n";
    }
    else if (ch == '<'){
        if (next_ch == '='){
            ans+= "LESS_EQUAL <= null\n";
            file.get(ch);  // Consume the next '='
        }
 //       else if(next_ch == '<'){
 //           ans+= "LEFT_SHIFT << null\n";
 //           file.get(ch);  // Consume the next '<'
 //       }
        else
        ans += "LESS < null\n";
    }
        
    else if (ch == '>'){
        if (next_ch == '='){
            ans+= "GREATER_EQUAL >= null\n";
            file.get(ch);  // Consume the next '='
        }
//        else if (next_ch == '>'){
//            ans+= "RIGHT_SHIFT >> null\n";
//            file.get(ch);  // Consume the next '>'
//        }
        else
        ans += "GREATER > null\n";
        
    }
    else if (ch == ' '|| ch == '\t'){

    }
    else {
        err += "[line " + std::to_string(line_number) + "] Error: Unexpected character: " + ch + "\n";
        exit_code = 65;
    }
}

    std::cerr << err;
    std::cout << ans; 
    std::cout << "EOF  null" << std::endl; 

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
