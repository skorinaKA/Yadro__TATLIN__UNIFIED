#ifndef TAPE_SORTER_H
#define TAPE_SORTER_H

#include "TapeInterface.h"
#include <vector>
#include <algorithm>

class TapeSorter {
private:
    TapeInterface& inputTape;
    TapeInterface& outputTape;
    Config config;

public:
    TapeSorter(TapeInterface& input, TapeInterface& output, Config &cfg)
        : inputTape(input), outputTape(output), config(cfg) {}

    void sort() {
        std::vector<int> buffer;
        std::vector<FileTape> tapes;

        while (inputTape.hasMoreData()) {
            buffer.clear();
            // Чтение данных в буфер с учетом ограничения по памяти
            while (buffer.size() < config["memoryLimit"] && inputTape.hasMoreData()) {
                buffer.push_back(inputTape.read());
            }
            // Сортировка буфера
            std::sort(buffer.begin(), buffer.end());
            tapes.emplace_back("tmp\\" + std::to_string(tapes.size() + 1) + ".txt", config);
            // Запись отсортированных данных в выходную ленту
            for (int value : buffer) {
                tapes.back().write(value);
            }
            tapes.back().rewind();
        }

        int tmp, min;
        while (true) {
            min = INT_MAX;
            auto minIt = tapes.begin();
            bool end_of_all_tapes = true;

            for (auto it = tapes.begin(); it != tapes.end(); ++it) {
                if (it->hasMoreData()) {
                    tmp = it->read();
                    if (tmp <= min) {
                        min = tmp;
                        minIt = it;
                    }
                    end_of_all_tapes = false;
                }
            }
            if (end_of_all_tapes) {
                break;
            }
            else {
                outputTape.write(min);
            }
        }

    }
};

#endif // TAPE_SORTER_H
