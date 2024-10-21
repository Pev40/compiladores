#include <iostream>
#include <string>
#include <cctype>

bool isValidVariableName(const std::string& input) {
    int state = 1;
    size_t i = 0;
    while (i < input.size()) {
        char currentSymbol = input[i];
        switch (state) {
            case 1:
                if (isalpha(currentSymbol)) {
                    state = 3;
                } else if (isdigit(currentSymbol)) {
                    state = 2;
                } else {
                    return false;
                }
                break;
            case 2:
                return false; 
            case 3:
                if (isalpha(currentSymbol) || isdigit(currentSymbol)) {
                    state = 3;
                } else {
                    return false; 
                }
                break;
            default:
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
