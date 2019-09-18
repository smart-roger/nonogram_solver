#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>

using val_type = uint16_t;
using input_line_type = std::vector<val_type>;
using CellsLine = std::string;

namespace CellState {
    constexpr uint8_t filled = 'X';
    constexpr uint8_t empty = ' ';
    constexpr uint8_t unknown = '?';
};

class Picture {
public:
    Picture(const val_type rows, const val_type columns) {
        std::string line(columns, CellState::unknown);
        lines.resize(rows, line);
    }

    void print (std::ostream& output) {
        for (auto line: lines)
            output << line << std::endl;
    }

    CellsLine& row(const val_type col){return lines[col];}

private:
    std::vector<std::string> lines;
};

struct input_data {
    std::vector<input_line_type> rows;
    std::vector<input_line_type> columns;
};

bool check_line_intersection (std::vector<val_type> params, CellsLine& line) {
    std:: cout << std::accumulate(params.begin(), params.end(), 0) + params.size() - 1 << ":" << line.size()/2 << std::endl;
    if (std::accumulate(params.begin(), params.end(), 0) + params.size() - 1 > line.size()/2) {
        std::cout << "Try filling" << std::endl;
        return true;
    }
    return false;
}


int main()
{
    std::cout << "Please input rows and columns: " << std::endl;
    uint16_t rows  = 0;
    uint16_t columns = 0;

    std::string line;
    std::cin >> rows >> columns;
    input_data data;

    std::cout << "Input rows." << std::endl;
    while (data.rows.size() < rows) {
        input_line_type row;
        std::string line;
        std::getline(std::cin, line);
        std::stringstream sstream(line);

        val_type input;
        while(sstream >> input) {
            row.push_back(input);
        }
        if (row.empty()) {
            std::cout << "Empty line! Skipped!" << std::endl;
        }
        else data.rows.push_back(row);
    }

    std::cout << "Input columns." << std::endl;
    for (auto idx = 0; idx < columns; ++idx) {
        input_line_type column;
        std::string line;
        std::getline(std::cin, line);
        std::stringstream sstream(line);

        val_type input;
        while(sstream >> input) {
            column.push_back(input);
        }
        if (column.empty()) column.push_back(0);
        data.columns.push_back(column);
    }

    Picture result(rows, columns);
    result.print(std::cout);


    int idx = 0;
    for (const auto& row: data.rows) {
        std::copy(row.begin(), row.end(), std::ostream_iterator<val_type>(std::cout, " "));
        check_line_intersection(row, result.row(idx));
        std::cout << std::endl;
        ++idx;
    }
std::cout << "==============================" << std::endl;
    for (const auto& column: data.columns) {
        std::copy(column.begin(), column.end(), std::ostream_iterator<val_type>(std::cout, " "));
        std::cout << std::endl;
    }
    return 0;
}
