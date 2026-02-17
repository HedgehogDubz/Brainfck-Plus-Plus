#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

int main() {
    const std::string topFile = "template_top.txt";
    std::ifstream topIn(topFile);
    if (!topIn) {
        std::cerr << "Error opening file: " << topFile << "\n";
        return 1;
    }
    std::string t((std::istreambuf_iterator<char>(topIn)),
                  std::istreambuf_iterator<char>());

    const std::string bottomFile = "template_bottom.txt";
    std::ifstream bottomIn(bottomFile);
    if (!bottomIn) {
        std::cerr << "Error opening file: " << bottomFile << "\n";
        return 1;
    }
    std::string b((std::istreambuf_iterator<char>(bottomIn)),
                  std::istreambuf_iterator<char>());

    const std::string inputFile = "test.bfpp";
    std::ifstream inputIn(inputFile);
    if (!inputIn) {
        std::cerr << "Error opening file: " << inputFile << "\n";
        return 1;
    }
    std::string s((std::istreambuf_iterator<char>(inputIn)),
                  std::istreambuf_iterator<char>());

    std::string out;
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        switch (c) {
            case '+':
                // TODO
                break;
            case '-':
                // TODO
                break;
            default:
                break;
        }
    }

    std::ofstream outputFile("example.txt");
    if (!outputFile) {
        std::cerr << "Error opening output file example.txt\n";
        return 1;
    }

    // If you want to write the combined templates + generated output:
    outputFile << t << "\n" << out << "\n" << b;

    std::cout << t << "\n";
    std::cout << s << "\n";
    std::cout << b << "\n";

    return 0;
}
