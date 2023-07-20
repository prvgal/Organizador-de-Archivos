#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

#include "extensiones.h"
#include "organizar.h"

int main(){
    int op = 0;
    string ruta;
    std::vector<fs::path> extensiones;

    do{
        system("cls");

        if(op < 0 || op > 3){
            system("cls");
            std::cout << "Elige una opcion correcta." << endl;
        }

        std::cout << "------MENU PRINCIPAL------" << endl;

        std::cout << "<1> Organizar" << endl;
        std::cout << "<2> Anadir extensiones" << endl;
        std::cout << "<3> Ver mis extensiones anadidas" << endl;
        std::cout << "<0> Salir" << endl;

        std::cout << "Ingresa una opcion: ";
        std::cin >> op;

        switch(op){
            case 0: break;
            case 1: OrganizarArchivos(extensiones); break;
            case 2: AnadirExtensiones(extensiones); break;
            case 3: ImprimirExtensiones(extensiones); break;
        }

    } while(op != 0);

    system("pause");
    
    return EXIT_SUCCESS;
}