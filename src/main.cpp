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
    
    while (file.get(ch))
    {
        if (ch == '\n')
        {
            line_number++;
            continue; // Skip newline characters
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
            ans += "STAR * null\n"; // Changed from std::cout to ans
        else if (ch == '.')
            ans += "DOT . null\n"; // Changed from std::cout to ans
        else if (ch == ',')
            ans += "COMMA , null\n"; // Changed from std::cout to ans
        else if (ch == ';')
            ans += "SEMICOLON ; null\n"; // Changed from std::cout to ans
        else if (ch == '+')
            ans += "PLUS + null\n"; // Changed from std::cout to ans
        else if (ch == '-')
            ans += "MINUS - null\n"; // Changed from std::cout to ans
        else if (ch == '/')
            ans += "SLASH / null\n"; // Changed from std::cout to ans

        else{
            ans = "[line " + std::to_string(line_number) + "] Error: Unexpected character: " + ch + "\n" + ans;
            exit_code = 65;
            
        }// Handle unexpected characters
    }
    std::cout << ans; // Print the result to standard output
    std::cout << "EOF  null" << std::endl; // End of file marker

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
