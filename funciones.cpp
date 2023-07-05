#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

#include "funciones.h"

// TODO: hacer funcion escalable
size_t AnadirExtensiones(string **infoExtensiones, size_t dim){
    system("cls");

    char op;
    size_t i = 1;
    string arr;
    string *extensiones = new string[1];   // Por defecto, solo habra un string
    dim += 1;

    *infoExtensiones = malloc_str(dim);

    if(extensiones == nullptr){
        std::cout << "Error en asignacion de memoria." << endl;
        std::exit(EXIT_FAILURE);
    }

    std::cout << "MENU ANADIR EXTENSIONES" << endl;
    std::cout << "A continuacion, debera poner el nombre de las extensiones. Por ejemplo, jpg." << endl;
    
    do{
        extensiones[i-1] = IntroducirExtension(extensiones, i);

        do{
            std::cout << "\nDesea seguir anadiendo extensiones? (S/n): ";
            std::cin >> op;
        
            if(op != 'S' && op != 'n')
                std::cout << "Por favor, ingrese una opcion correcta." << endl;

        } while(op != 'S' && op != 'n');

        if(op == 'S'){
            i += 1;
            resize_str(&extensiones, i-1, i);
        }

    } while(op == 'S');

    ImprimirExtensiones(extensiones, i);
    system("pause");

    delete[] extensiones;

    return dim;
}

void ImprimirExtensiones(string *extensiones, size_t tam){
    system("cls");

    std::cout << "Sus extensiones: " << endl;

    for(size_t i = 0; i < tam; i++)
        std::cout << i+1 << ". " << extensiones[i] << endl;
}

void resize_str(string **array, size_t tamAntiguo, size_t tamNuevo){
    size_t tam = tamAntiguo + tamNuevo;

    string *nuevoArray = new string[tam];

    if(nuevoArray == nullptr){
        std::cout << "Error en asignacion de memoria";
        std::exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < tamAntiguo; i++)
        nuevoArray[i] = (*array)[i];

    delete[] *array;

    *array = nuevoArray;
}

string IntroducirExtension(string *extensiones, size_t tamExtensiones){
    string arr;

    do{
        std::cout << "\nIngrese extension: ";
        std::cin >> arr;

        if(ComprobarExtension(arr, extensiones, tamExtensiones) == true)
            std::cout << "La extension ya fue anadida anteriormente." << endl;

    } while(ComprobarExtension(arr, extensiones, tamExtensiones) == true);

    return arr;
}

bool ComprobarExtension(string arr, string *extensiones, size_t tam){
    bool igual = false;

    for(size_t i = 0; i < tam && igual == false; i++){
        if(arr.compare(extensiones[i]) == 0)
            igual = true;
    }

    return igual;
}

string *malloc_str(size_t dim){
    string *str = new string[dim];

    if(str == nullptr){
        std::cout << "Error en asignacion de memoria";
        std::exit(EXIT_FAILURE);
    }

    return str;
}

void free_str(string **str){
    delete[] *str;
    *str = nullptr;
}
