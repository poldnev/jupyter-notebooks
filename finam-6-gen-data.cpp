#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>

static constexpr std::time_t START_TIME = 1262304000;

std::string BuildTimeString(std::time_t timestamp) {
    char buffer[32];
    return std::string(buffer, std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", gmtime(&timestamp)));
}

void GenerateSampleStat(int row_count, std::ostream &out_stream = std::cout) {
    std::mt19937 generator;

    out_stream << "Timestamp,Price,Volume\n";
    std::time_t timestamp = START_TIME;
    double price = 200;
    for (int i = 0; i < row_count; ++i) {
        const int volume = std::exponential_distribution<>(0.1)(generator) + 1;
        out_stream
            << BuildTimeString(timestamp) << ","
            << price << ","
            << volume << "\n";
        ++timestamp;
        price = std::max(price + std::normal_distribution<>()(generator) / 10, 10.0);
    }
}

int main(int argc, char **argv) {
    std::ofstream file(argv[1]);
    const int row_count = atoi(argv[2]);

    GenerateSampleStat(row_count, file);

    return 0;
}
