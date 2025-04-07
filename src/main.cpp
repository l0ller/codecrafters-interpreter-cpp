#include <iostream>
#include <string>
#include "scanner.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program <command> <filename>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string file_contents = read_file_contents(argv[2]);

    if (command == "tokenize") {
        if (!file_contents.empty()) {
            std::cout << output_after_tokenize;
            std::cout << "EOF  null" << std::endl;
        }
    } else if (command == "parse") {
        parse_tokens();
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return exit_code;
}
