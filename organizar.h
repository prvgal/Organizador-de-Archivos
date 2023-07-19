#ifndef ORGANIZAR_H
#define ORGANIZAR_H

void CopiarArchivo(string archivoOrigen, string archivoDestino);
void OrganizarArchivos(string* extensiones, size_t numExtensiones);
string getRuta(void);
string PedirRuta(int op);
string CrearDirectorio(int op);
int PreguntarCrearDirectorio(void);

#endif
