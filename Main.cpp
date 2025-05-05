#include "FileTape.h"
#include "TapeSorter.h"
#include <iostream>
#include <fstream>

bool loadConfig(const std::string& filename, Config& configData) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Найдем знак '=' в строке
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // Удаляем пробелы
            key.erase(std::remove_if(key.begin(), key.end(), isspace), key.end());
            value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());

            // Преобразуем значение в целое число
            try {
                int intValue = std::stoi(value);
                configData[key] = intValue;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid value for key '" << key << "': " << value << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Value out of range for key '" << key << "': " << value << std::endl;
            }
        }
    }

    file.close();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <config_file> <input_file> <output_file>" << std::endl;
        return 1;
    }

    Config configData = {
    {"readDelay", 0},
    {"writeDelay", 0 },
    {"shiftDelay", 0},
    {"rewindDelay", 0},
    {"memoryLimit", 0}
    };

    std::string configFile = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    loadConfig("config.txt", configData);

    try {
        FileTape inputTape(inputFile, configData);
        FileTape outputTape(outputFile, configData);

        TapeSorter sorter(inputTape, outputTape, configData);

        std::cout << "Start Sorting." << std::endl;
        sorter.sort();
        std::cout << "Sorting completed." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
