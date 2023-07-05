#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

#include "organizar.h"

string getRuta(void){
    system("cls");

    string dir;

    do{
        std::cout << "Ingrese la ruta donde deseas organizar tus archivos: ";
        std::getline(std::cin, dir);

        if(std::filesystem::exists(dir) == false)
            std::cout << "La ruta indicada no existe, indique una existente." << endl;

    } while(std::filesystem::exists(dir) == false);

    return dir;
}