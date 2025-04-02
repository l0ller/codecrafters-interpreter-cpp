#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string read_file_contents(const std::string& filename);

int main(int argc, char *argv[]) {
    // Disable output buffering
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return 1;
    }

    const std::string command = argv[1];

    if (command == "tokenize") {
        std::string file_contents = read_file_contents(argv[2]);
        
        // Uncomment this block to pass the first stage
        // 
         if (!file_contents.empty()) {
             std::cerr << "Scanner not implemented" << std::endl;
             return 1;
         }
        // git commit -am "[any message]" std::cout << "EOF  null" << std::endl; // Placeholder, remove this line when implementing the scanner
        
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}



std::string read_file_contents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }
    int line_number = 1;
    char ch;
    while (file.get(ch)) { 
        if (ch == 'EOL') 
            line_number++;

        if(ch == '(') 
        std::cout<<"LEFT_PAREN ( null"<<std::endl;
        else if(ch == ')')
        std::cout<<"RIGHT_PAREN ) null"<<std::endl;  
        else if(ch == '{')
        std::cout<<"LEFT_BRACE { null"<<std::endl;  
        else if(ch == '}')
        std::cout<<"RIGHT_BRACE } null"<<std::endl;  
        else if(ch == '*')
        std::cout<<"STAR * null"<<std::endl;  
        else if(ch == '.')
        std::cout<<"DOT . null"<<std::endl;  
        else if(ch == ',')
        std::cout<<"COMMA , null"<<std::endl;  
        else if(ch == ';')
        std::cout<<"SEMICOLON ; null"<<std::endl;  
        else if(ch == '+')
        std::cout<<"PLUS + null"<<std::endl;  
        else if(ch == '-')
        std::cout<<"MINUS - null"<<std::endl;  
        else if(ch == '/')
        std::cout<<"SLASH / null"<<std::endl;  
        else 
        std::cout<<"[line "<<line_number<<"] [error] Unexpected character: "<<ch<<std::endl; // Handle unexpected characters
        
        
    }
    std::cout<<"EOF  null"<<std::endl; // End of file marker
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}


