#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

#include "funciones.h"

size_t AnadirExtensiones(string** infoExtensiones, size_t dim){
    system("cls");

    char op;
    dim += 1;
    string* extensionesAntiguas = *infoExtensiones;

    *infoExtensiones = malloc_str(dim);

    if(*infoExtensiones == nullptr){
        std::cerr << "Error en asignacion de memoria." << endl;
        std::exit(EXIT_FAILURE);
    }

    // Copiamos las extensiones antiguas en el nuevo array
    for(size_t i = 0; i < dim-1; i++)
        (*infoExtensiones)[i] = extensionesAntiguas[i];

    delete[] extensionesAntiguas; // Liberamos memoria, las extensiones antiguas ya estan en infoExtensiones

    std::cout << "MENU ANADIR EXTENSIONES" << endl;
    std::cout << "A continuacion, debera poner el nombre de las extensiones. Por ejemplo, jpg." << endl;
    
    do{
        (*infoExtensiones)[dim-1] = IntroducirExtension(*infoExtensiones, dim);

        do{
            std::cout << "\nDesea seguir anadiendo extensiones? (S/n): ";
            std::cin >> op;
        
            if(op != 'S' && op != 'n')
                std::cout << "Por favor, ingrese una opcion correcta." << endl;

        } while(op != 'S' && op != 'n');

        if(op == 'S'){
            dim += 1;
            resize_str(infoExtensiones, dim-1, dim);
        }

    } while(op == 'S');

    ImprimirExtensiones(*infoExtensiones, dim);

    return dim;
}

void ImprimirExtensiones(string* extensiones, size_t tam){
    system("cls");

    if(tam == 0)
        std::cout << "Aun no ha anadido ninguna extension. Para ello, en el menu principal, use la opcion 2." << endl; 
    else{
        std::cout << "Sus extensiones: " << endl;

        for(size_t i = 0; i < tam; i++)
            std::cout << i+1 << ". " << extensiones[i] << endl;
    }

    // Evitamos problemas de buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar el carácter de nueva línea

    // Pausamos para que pueda ver las extensiones
    std::cout << "Presione ENTER para continuar...";
    std::cin.get();
}

void resize_str(string** array, size_t tamAntiguo, size_t tamNuevo){
    size_t tam = tamAntiguo + tamNuevo;

    string* nuevoArray = new string[tam];

    if(nuevoArray == nullptr){
        std::cerr << "Error en asignacion de memoria";
        std::exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < tamAntiguo; i++)
        nuevoArray[i] = (*array)[i];

    delete[] *array;

    *array = nuevoArray;
}

string IntroducirExtension(string* extensiones, size_t tamExtensiones){
    string arr;

    do{
        std::cout << "\nIngrese extension: ";
        std::cin >> arr;

        if(ComprobarExtension(arr, extensiones, tamExtensiones) == true)
            std::cout << "La extension ya fue anadida anteriormente." << endl;

    } while(ComprobarExtension(arr, extensiones, tamExtensiones) == true);

    return arr;
}

bool ComprobarExtension(string arr, string* extensiones, size_t tam){
    bool igual = false;

    for(size_t i = 0; i < tam && igual == false; i++){
        if(arr.compare(extensiones[i]) == 0)
            igual = true;
    }

    return igual;
}

string* malloc_str(size_t dim){
    string* str = new string[dim];

    if(str == nullptr){
        std::cerr << "Error en asignacion de memoria";
        std::exit(EXIT_FAILURE);
    }

    return str;
}

void free_str(string** str){
    delete[] *str;
    *str = nullptr;
}
