#ifndef ORGANIZAR_H
#define ORGANIZAR_H

void CopiarArchivo(const fs::path& archivoOrigen, const fs::path& archivoDestino);
void OrganizarArchivos(const std::vector<fs::path>& extensiones);
bool ComprobarExtension(const fs::path& archivo, const std::vector<fs::path>& extensiones);
fs::path getRuta(void);
fs::path PedirRuta(int op);
fs::path CrearDirectorio(int op);
int PreguntarCrearDirectorio(void);

#endif