#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
        stringstream ss(line);
        string word;
        while (ss >> word)
        {
            if (isalpha(word[0]))
            {
                cout << "Palabra: " << word << endl;
            }
            else if (isdigit(word[0]))
            {
                cout << "Numero: " << word << endl;
            }
            else
            {
                cout << "Simbolo especial: " << word << endl;
            }
        }
    }

    file.close();

    return 0;
}