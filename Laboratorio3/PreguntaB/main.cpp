#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string filename;
    cout << "Ingrese el nombre del archivo: ";
    cin >> filename;

    ifstream file(filename);
    if (!file)
    {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();

    return 0;
}