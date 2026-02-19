#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cctype>
#include <cstdlib>
#include <unordered_map>

int main() {

    std::string fileName = "bfpps/add.bfpp";
    std::string name = fileName.substr(0, fileName.find_last_of('.'));






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

    const std::string inputFile = fileName;
    std::ifstream inputIn(inputFile);
    if (!inputIn) {
        std::cerr << "Error opening file: " << inputFile << "\n";
        return 1;
    }
    std::string s((std::istreambuf_iterator<char>(inputIn)),
                  std::istreambuf_iterator<char>());

    std::string out;

    const char numbers[] = {'1','2','3','4','5','6','7','8','9','0'};
    std::unordered_map<std::string, std::string> definitions;

    // First pass: Extract all definitions from |def:rep| patterns
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '|') {
            size_t end = s.find('|', i + 1);
            if (end != std::string::npos) {
                std::string content = s.substr(i + 1, end - i - 1);
                size_t colonPos = content.find(':');
                if (colonPos != std::string::npos) {
                    std::string def = content.substr(0, colonPos);
                    std::string rep = content.substr(colonPos + 1);
                    definitions[def] = rep;
                }
                i = end; 
            }
        }
    }

    // Second pass: Replace all |def| with their definitions and remove |def:rep| patterns
    std::string processed;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '|') {
            size_t end = s.find('|', i + 1);
            if (end != std::string::npos) {
                std::string content = s.substr(i + 1, end - i - 1);
                size_t colonPos = content.find(':');
                if (colonPos != std::string::npos) {
                } else {
                    if (definitions.find(content) != definitions.end()) {
                        processed += definitions[content];
                    } else {
                        processed += s.substr(i, end - i + 1);
                    }
                }
                i = end; 
            } else {
                processed += s[i];
            }
        } else {
            processed += s[i];
        }
    }
    s = processed; 



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
            case '^':
                out += "save();\n";
                break;
            case 'v':
                out += "load();\n";
                break;
            case 'o':
                out += "output();\n";
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
            case '\'':
                out += "a[p] = " + std::to_string(static_cast<int>(s[i+1])) + ";\n";
                i++;
                break;
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
    std::cout << "********* STARTING " + name + " *********"<< std::endl;

    std::system(cmd.c_str());

    std::system(("./" + name).c_str());

    std::remove((name + ".cpp").c_str());
    std::remove(name.c_str());
    std::cout << "\n********* FINISHED " + name + " *********"<< std::endl;
    return 0;
}
