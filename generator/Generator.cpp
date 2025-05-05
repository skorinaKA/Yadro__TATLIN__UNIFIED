#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <sstream>

void main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <count_numbers> <output_file>" << std::endl;
        return;
    }

    int count = atoi(argv[1]);
    std::string path = argv[2];
    
    srand(time(NULL));

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<int> uni;
    auto random_integer = uni(rng);

    std::stringstream buffer;
    std::ofstream file(path, std::ios::trunc);

    for (int index = 0; index < count; index++)
    {
        buffer << uni(rng) << std::endl;
    }
    std::string str = buffer.str();
    str.pop_back();
    file << str;
    file.close();
}