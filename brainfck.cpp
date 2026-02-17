#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cctype>

int main() {


    std::string name = "multiplication";






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

    const std::string inputFile = "bfpps/" + name + ".bfpp";
    std::ifstream inputIn(inputFile);
    if (!inputIn) {
        std::cerr << "Error opening file: " << inputFile << "\n";
        return 1;
    }
    std::string s((std::istreambuf_iterator<char>(inputIn)),
                  std::istreambuf_iterator<char>());

    std::string out;

    const char numbers[] = {'1','2','3','4','5','6','7','8','9','0'};

    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        switch (c) {
            case '>':
                out += "mov_right();\n";
                break;
            case '<':
                out += "if(mov_left()){return 1;}\n";
                break;
            case '+':
                out += "add();\n";
                break;
            case '-':
                out += "sub();\n";
                break;
            case 's':
                out += "save();\n";
                break;
            case 'l':
                out += "load();\n";
                break;
            case 'p':
                out += "print();\n";
                break;
            case '(':
                out += "if (a[p] != 0) {\n";
                break;
            case ')':
                out += "}\n";
                break;
            case '[':
                out += "while (a[p] != 0) {\n";
                break;
            case ']':
                out += "}\n";
                break;
            case '#': {
                int num = 0;
                for(int j = i+1; j < s.size(); j++){
                    if (!std::isdigit(static_cast<unsigned char>(s[j]))){
                        const std::string numString = s.substr(i+1, j-i-1);
                        if(numString.empty()){
                            out += "a[p] = 0;\n";
                        } else {
                            out += "a[p] = " + numString + ";\n";
                        }
                        break;
                    }
                }
                break;
            }
            default:
                break;
        }
    }

    std::ofstream outputFile(name + ".cpp");

    if (!outputFile) {
        std::cerr << "Error opening output file example.txt\n";
        return 1;
    }

    outputFile << t << "\n" << out << "\n" << b;
    outputFile.close();

    std::string cmd = "g++ " + name + ".cpp -o " + name;
    if (std::system(cmd.c_str()) != 0) return 1;
    return std::system(("./" + name).c_str());

    return 0;
}
