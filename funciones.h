#ifndef FUNCIONES_H
#define FUNCIONES_H

size_t AnadirExtensiones(string **infoExtensiones, size_t dim);
void ImprimirExtensiones(string *extensiones, size_t tam);
void resize_str(string **array, size_t tamAntiguo, size_t tamNuevo);
string IntroducirExtension(string *extensiones, size_t tamExtensiones);
bool ComprobarExtension(string arr, string *extensiones, size_t tam);
string *malloc_str(size_t dim);
void free_str(string **str);

#endif
