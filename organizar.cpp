#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

#include "organizar.h"

void CopiarArchivo(const fs::path& archivoOrigen, const fs::path& archivoDestino){
    std::ifstream origen(archivoOrigen, std::ios::binary);
    
    if(!origen){
        std::cerr << "No se pudo abrir el archivo." << endl;
        exit(EXIT_FAILURE);
    }

    std::ofstream destino(archivoDestino, std::ios::binary);

    if(!destino){
        std::cerr << "No se pudo abrir el archivo." << endl;
        exit(EXIT_FAILURE);
    }

    destino << origen.rdbuf();

    origen.close();
    destino.close();
}

void OrganizarArchivos(const std::vector<fs::path>& extensiones){
    system("cls");
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(extensiones.empty()){
        int op;

        std::cout << "Debes tener extensiones anadidas previamente (0) o organizar todas las extensiones (1)." << endl;
        std::cin >> op;

        if(op == 1)
            OrganizarDirectorioCompleto();
        else{
            std::cout << "Presione ENTER para continuar...";
            std::cin.get();
        }

    } else{
        fs::path ruta = getRuta();

        // Creamos los directorios correspondientes de cada extension
        for(const fs::path& extension : extensiones){
            string aux = extension.string();
            fs::path dir = ruta / fs::path(aux.substr(1));

            if(!fs::create_directory(dir)){
                std::cerr << "Error en creacion de directorio." << endl;
                exit(EXIT_FAILURE);
            }        
        }

        // Iteramos cada elemento de la ruta
        for(const auto& iter : fs::directory_iterator(ruta)){
            if(!fs::is_directory(iter) && ComprobarExtension(iter.path(), extensiones)){
                fs::path dirOrigen = iter.path();
                string aux = dirOrigen.extension().string().substr(1);    // Eliminamos el . de la extension
                fs::path dirGuardar = ruta / fs::path(aux) / dirOrigen.filename();    // Obtenemos el archivoDestino
                CopiarArchivo(dirOrigen, dirGuardar);

                // Eliminamos el archivo de dirOrigen
                if(!fs::remove(dirOrigen))
                    std::cerr << "El archivo no se ha podido eliminar " << dirOrigen.filename() << "de la ruta original." << endl;
            }
        }
    }
}

void OrganizarDirectorioCompleto() {
    fs::path ruta = getRuta();
    fs::path extension;
    std::vector<fs::path> extensiones;

    for(const auto& iter : fs::directory_iterator(ruta)){
        if(!fs::is_directory(iter)){
            extension = iter.path().extension();
            extensiones.push_back(extension);

            string aux = extension.string().substr(1);
            fs::path dir = ruta / fs::path(aux);

            // Comprobamos si ya se ha creado el directorio previamente
            if(!fs::exists(dir)){
                if(!fs::create_directory(dir)){
                    std::cerr << "Error en creacion de directorio: " << dir << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

            fs::path dirOrigen = iter.path();
            fs::path dirGuardar = dir / dirOrigen.filename();

            CopiarArchivo(dirOrigen, dirGuardar);

            if(!fs::remove(dirOrigen)){
                std::cerr << "El archivo no se ha podido eliminar: " << dirOrigen.filename() << std::endl;
            }
        }
    }
}

bool ComprobarExtension(const fs::path& archivo, const std::vector<fs::path>& extensiones){
    bool esValido = false;

    for(const fs::path& ext : extensiones){
        if(archivo.extension() == ext)
            esValido = true;
    }

    return esValido;
}

fs::path getRuta(void){
    fs::path ruta;
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

fs::path PedirRuta(int op){
    string input;
    fs::path dir;   

    do{
        if(op == 0)
            std::cout << "Ingrese la ruta donde deseas organizar tus archivos: ";
        else
            std::cout << "Para crear el directorio, ingrese la ruta donde quieres crearlo: ";

        std::getline(std::cin, input);
        dir = input;

        if(!fs::exists(dir) || !fs::is_directory(dir))  
            std::cout << "El directorio no existe, o no es valido." << endl;

    } while(!fs::exists(dir) || !fs::is_directory(dir));

    return dir;
}

fs::path CrearDirectorio(int op){
    string nomDir;
    fs::path dondeCrear = PedirRuta(op);

    std::cout << "Ingrese el nombre del directorio a crear: ";
    std::getline(std::cin, nomDir);

    fs::path ruta = dondeCrear / fs::path(nomDir);

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
