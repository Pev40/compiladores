#include <iostream>
#include <istream>

using namespace std;

int main()
{

    string input;
    cout << "Ingrese sentencia: ";
    getline(cin, input);

    for (char c : input)
    {
        cout << c << endl;
    }
}