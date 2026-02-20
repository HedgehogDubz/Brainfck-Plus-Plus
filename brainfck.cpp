#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cctype>
#include <cstdlib>
#include <unordered_map>
#include <filesystem>

std::string processIncludes(const std::string& filePath) {
    std::ifstream inputIn(filePath);
    if (!inputIn) {
        std::cerr << "Error opening file: " << filePath << "\n";
        exit(1);
    }
    std::string content((std::istreambuf_iterator<char>(inputIn)),
                        std::istreambuf_iterator<char>());

    std::filesystem::path currentFilePath = std::filesystem::absolute(filePath);
    std::filesystem::path currentDir = currentFilePath.parent_path();

    for (size_t i = 0; i < content.size(); i++) {
        if (content[i] == '@') {
            size_t end = content.find_first_of(" \n", i + 1);
            if (end == std::string::npos) {
                end = content.size();
            }

            std::string relativeFileName = content.substr(i + 1, end - i - 1);

            // Use filesystem to properly resolve the path relative to current file's directory
            std::filesystem::path includePath = currentDir / relativeFileName;
            std::string includePathStr = includePath.string();

            std::string includedContent = processIncludes(includePathStr);

            content.erase(i, end - i);
            content.insert(i, includedContent);

            i += includedContent.length() - 1;
        }
    }

    return content;
}

int main(int argc, char* argv[]) {
    // Check if a filename was provided as a command-line argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.bfpp>" << std::endl;
        std::cerr << "Example: " << argv[0] << " bfpps/test.bfpp" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    std::string name = fileName.substr(0, fileName.find_last_of('.'));
    std::filesystem::path p = std::filesystem::absolute(fileName);
    std::string fullPath = p.string();





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

    // Process the main file and all its includes recursively
    std::string s = processIncludes(fileName);

    std::string out;

    const char numbers[] = {'1','2','3','4','5','6','7','8','9','0'};
    std::unordered_map<std::string, std::string> definitions;

    std::cout << s << std::endl;




    // Helper function to expand definitions in a string
    // Definitions are referenced using {def} syntax
    auto expandDefinitions = [&definitions](const std::string& text) -> std::string {
        std::string result;
        for (size_t i = 0; i < text.size(); i++) {
            if (text[i] == '{') {
                size_t end = text.find('}', i + 1);
                if (end != std::string::npos) {
                    std::string defName = text.substr(i + 1, end - i - 1);
                    // Replace with definition if it exists
                    if (definitions.find(defName) != definitions.end()) {
                        result += definitions[defName];
                    } else {
                        // Keep original if not found
                        result += text.substr(i, end - i + 1);
                    }
                    i = end;
                } else {
                    result += text[i];
                }
            } else {
                result += text[i];
            }
        }
        return result;
    };

    // First pass: Extract all definitions from |def:rep| patterns
    // References use {def} syntax, so we just need to count brace depth
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '|') {
            size_t colonCheck = i + 1;
            while (colonCheck < s.size() && s[colonCheck] != '|' && s[colonCheck] != ':') {
                colonCheck++;
            }

            if (colonCheck < s.size() && s[colonCheck] == ':') {
                // This is a definition: |def:rep|
                std::string def = s.substr(i + 1, colonCheck - i - 1);

                size_t repStart = colonCheck + 1;
                size_t end = repStart;
                int braceDepth = 0;

                while (end < s.size()) {
                    if (s[end] == '{') {
                        braceDepth++;
                    } else if (s[end] == '}') {
                        braceDepth--;
                    } else if (s[end] == '|' && braceDepth == 0) {
                        break;
                    }
                    end++;
                }

                if (end < s.size()) {
                    std::string rep = s.substr(repStart, end - repStart);
                    // Expand any nested definitions in the replacement text
                    std::string expandedRep = expandDefinitions(rep);
                    definitions[def] = expandedRep;
                    i = end;
                }
            }
        }
    }

    // Second pass: Replace all {def} with their definitions and remove |def:rep| patterns
    std::string processed;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '|') {
            size_t end = s.find('|', i + 1);
            if (end != std::string::npos) {
                std::string content = s.substr(i + 1, end - i - 1);
                size_t colonPos = content.find(':');
                if (colonPos != std::string::npos) {
                    i = end;
                } else {
                    processed += s[i];
                }
            } else {
                processed += s[i];
            }
        } else if (s[i] == '{') {
            size_t end = s.find('}', i + 1);
            if (end != std::string::npos) {
                std::string defName = s.substr(i + 1, end - i - 1);
                if (definitions.find(defName) != definitions.end()) {
                    processed += definitions[defName];
                } else {
                    processed += s.substr(i, end - i + 1);
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
            case '~':
                out += "input_int();\n";
                break;
            case '_':
                out += "input_str();\n";
                break;
            case '!':
                out += "notz();\n";
                break;
            case '\"':
                for(int j = i+1; j < s.size(); j++){
                    if (s[j] == '\"'){
                        i = j;
                        break;
                    }
                    out += "a[p] = " + std::to_string(static_cast<int>(s[j])) + ";\n";
                    out += "mov_right();\n";
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
    std::cout << "********* STARTING " + name + " *********"<< std::endl;

    std::system(cmd.c_str());

    std::system(("./" + name).c_str());

    std::remove((name + ".cpp").c_str());
    std::remove(name.c_str());
    std::cout << "\n********* FINISHED " + name + " *********"<< std::endl;
    return 0;
}
