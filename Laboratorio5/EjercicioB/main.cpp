#include <iostream>
#include <string>
#include <cctype>

bool isValidVariableName(const std::string& input) {
    int transitions[4][3] = {
        {3, 2, 0},
        {0, 0, 0},
        {3, 3, 0},
        {3, 3, 3}
    };

    int state = 1;
    size_t i = 0;
    while (i < input.size()) {
        char currentSymbol = input[i];
        int symbolType = 0;
        if (isalpha(currentSymbol)) {
            symbolType = 0;
        } else if (isdigit(currentSymbol)) {
            symbolType = 1;
        } else {
            symbolType = 2;
        }

        state = transitions[state - 1][symbolType];
        if (state == 0) {
            return false;
        }

        i++;
    }

    return state == 3;
}

int main() {
    std::string input;
    std::cout << "Ingreso tu codigo: ";
    std::cin >> input;

    if (isValidVariableName(input)) {
        std::cout << "Codigo Aceptado." << std::endl;
    } else {
        std::cout << "Error: En la Linea (:) ." << std::endl;
    }

    return 0;
}
