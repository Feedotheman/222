#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    // Check if at least one argument (file path) is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_file1> [path_to_file2] ..." << std::endl;
        return 1;
    }

    // Iterate through all provided file paths
    for (int i = 1; i < argc; ++i) {
        std::string filePath = argv[i];
        std::ifstream file(filePath);

        if (!file) {
            std::cerr << "Error: Cannot open file " << filePath << std::endl;
            continue;
        }

        std::cout << "Processing file: " << filePath << std::endl;
        // Example: Read and display the first line of each file
        std::string line;
        if (std::getline(file, line)) {
            std::cout << line << "\n";
            while (std::getline(file, line)){
                std::cout << line << "\n";
            }
        } else {
            std::cout << "File is empty." << std::endl;
        }

        file.close();
    }

    return 0;
}