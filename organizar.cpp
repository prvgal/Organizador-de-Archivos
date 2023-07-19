#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

#include "organizar.h"

void CopiarArchivo(string archivoOrigen, string archivoDestino){
    std::ifstream origen(archivoOrigen, std::ios::binary);
    
    if(!origen){
        std::cerr << "No se pudo abrir el archivo." << endl;
        exit(EXIT_FAILURE);
    }

    string nombre = fs::path(archivoOrigen).filename().string();
    string rutaDestino = archivoDestino + "\\" + nombre;
    std::ofstream destino(rutaDestino, std::ios::binary);

    if(!destino){
        std::cerr << "No se pudo abrir el archivo." << endl;
        exit(EXIT_FAILURE);
    }

    destino << origen.rdbuf();

    origen.close();
    destino.close();
}

void OrganizarArchivos(string* extensiones, size_t numExtensiones){
    system("cls");
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(numExtensiones == 0){
        std::cout << "Debes tener extensiones anadidas previamente." << endl;
        std::cout << "Presione ENTER para continuar...";
        std::cin.get();
    } else{
        string ruta = getRuta();

        for(size_t i = 0; i < numExtensiones; i++){
            string dir = ruta + "\\" + extensiones[i];

            if(!fs::create_directory(dir)){
                std::cerr << "Error en creacion de directorio." << endl;
                exit(EXIT_FAILURE);
            } 
            
            // TODO: recorrer todos los archivos de la ruta
        
        }
    }
}

string getRuta(void){
    system("cls");

    string ruta;
    int op = PreguntarCrearDirectorio();

    if(op == 0)
        ruta = PedirRuta(op);
    else if(op == 1)
        ruta = CrearDirectorio(op);
    else{
        std::cerr << "Error en eleccion de directorio." << endl;
        exit(EXIT_FAILURE);
    }

    system("cls");
    std::cout << "Ruta a organizar: " << ruta << endl;

    // Pausamos para que pueda ver por pantalla la ruta
    std::cout << "Presione ENTER para continuar...";
    std::cin.get();

    return ruta;
}

string PedirRuta(int op){
    string dir;

    do{
        if(op == 0)
            std::cout << "Ingrese la ruta donde deseas organizar tus archivos: ";
        else
            std::cout << "Para crear el directorio, ingrese la ruta donde quieres crearlo: ";

        std::getline(std::cin, dir);

        if(!fs::exists(dir) || !fs::is_directory(dir))  
            std::cout << "El directorio no existe, o no es valido." << endl;

    } while(!fs::exists(dir) || !fs::is_directory(dir));

    return dir;
}

string CrearDirectorio(int op){
    string nomDir;
    string dondeCrear = PedirRuta(op);

    std::cout << "Ingrese el nombre del directorio a crear: ";
    std::getline(std::cin, nomDir);

    string ruta = dondeCrear + "\\" + nomDir;

    if(!fs::create_directory(ruta)){
        std::cerr << "Error en creacion de directorio." << endl;
        exit(EXIT_FAILURE);
    }

    return ruta;    // Devolvemos la direccion de la ruta del directorio que hemos creado
}

int PreguntarCrearDirectorio(void){
    int op;

    do{
        std::cout << "Desea crear un directorio nuevo (1) o en uno ya existente (0): ";
        std::cin >> op;

        if(op != 0 && op != 1)
            std::cout << "Recuerde, (1) para crear un nuevo directorio o (0) para uno ya existente." << endl;

        // Evitamos problemas de buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar el carácter de nueva línea

    } while(op != 0 && op != 1);

    return op;
}
