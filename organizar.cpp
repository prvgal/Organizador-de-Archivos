#include <iostream>
#include <string>
#include <filesystem>
#include <cstring>

using namespace std;
namespace fs = std::filesystem;

#include "organizar.h"

string getRuta(void){
    string dir;
    string ruta;
    short op = PreguntarCrearDirectorio();

    if(op == 0){
        do{
            //system("cls");

            std::cout << "Ingrese la ruta donde deseas organizar tus archivos: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignorar \n
            std::getline(std::cin, dir);
            std::replace(dir.begin(), dir.end(), '\\', '/');    // Por si el usuario ingresa la direccion con (/) en lugar de (\)
            ruta = AnadirBarra(dir);

            std::cout << "RUTA: " << dir;

            if(!fs::exists(dir) || !fs::is_directory(dir))
                std::cout << "El directorio no existe, o no es valido." << endl;

        } while(!fs::exists(dir) || !fs::is_directory(dir));

    } else if(op == 1){
        /* aun no desarrollado */
    } else{
        std::cout << "Error en eleccion de directorio." << endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "RUTA: " << dir;

    return dir;
}

short PreguntarCrearDirectorio(void){
    int op;

    do{
        std::cout << "Desea crear un directorio nuevo (1) o en uno ya existente (0): ";
        std::cin >> op;

        if(op != 0 && op != 1)
            std::cout << "Recuerde, (1) para crear un nuevo directorio o (0) para uno ya existente." << endl;

    } while(op != 0 && op != 1);

    return op;
}

string AnadirBarra(const string& dir){
    string cambio;

    for(size_t i = 0; i < dir.length(); i++){
        if(dir[i] == '\\')  // '\\' = \ en c++
            cambio += "\\";

        cambio += dir[i];
    }

    return cambio;
}
