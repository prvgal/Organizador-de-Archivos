#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

#include "extensiones.h"

void AnadirExtensiones(std::vector<fs::path>& extensiones){
    system("cls");

    char op;
    
    std::cout << "MENU ANADIR EXTENSIONES" << std::endl;
    std::cout << "A continuacion, debera poner el nombre de las extensiones. Por ejemplo, jpg." << std::endl;

    do{
        fs::path extension = IntroducirExtension(extensiones);

        extensiones.push_back(extension);

        do {
            std::cout << "\nDesea seguir anadiendo extensiones? (S/n): ";
            std::cin >> op;

            if (op != 'S' && op != 'n')
                std::cout << "Por favor, ingrese una opcion correcta." << std::endl;

        } while (op != 'S' && op != 'n');

    } while(op == 'S');

    ImprimirExtensiones(extensiones);
}

void ImprimirExtensiones(const std::vector<fs::path>& extensiones){
    system("cls");

    if(extensiones.empty())
        std::cout << "Aun no ha anadido ninguna extension. Para ello, en el menu principal, use la opcion 2." << std::endl;
    else{
        std::cout << "Sus extensiones: " << std::endl;

        for(size_t i = 0; i < extensiones.size(); i++) 
            std::cout << i + 1 << ". " << extensiones[i] << std::endl;
    }

    // Evitamos problemas de buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar el carácter de nueva línea

    // Pausamos para que pueda ver las extensiones
    std::cout << "Presione ENTER para continuar...";
    std::cin.get();
}

fs::path IntroducirExtension(const std::vector<fs::path>& extensiones){
    string extension;
    fs::path devolver;

    do{
        std::cout << "\nIngrese extension: ";
        std::cin >> extension;

        if(std::find(extensiones.begin(), extensiones.end(), extension) != extensiones.end())
            std::cout << "La extension ya fue anadida anteriormente." << endl;

        // Comprobamos si ha puesto el punto
        if(extension[0] != '.')
            extension = '.' + extension;
        
        // Transformamos el string a path
        devolver = fs::path(extension);

    } while(std::find(extensiones.begin(), extensiones.end(), devolver) != extensiones.end());

    return devolver;
}