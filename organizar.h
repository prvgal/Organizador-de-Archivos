#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <wx/wx.h>

namespace fs = std::filesystem;

void OrganizarDirectorioPorExtension(const std::vector<fs::path>& extensiones, const fs::path& ruta);
void OrganizarDirectorioCompleto(const fs::path& ruta);
bool ExisteExtension(const fs::path& archivo, const std::vector<fs::path>& extensiones);
void CopiarArchivo(const fs::path& archivoOrigen, const fs::path& archivoDestino);
void SeleccionarTipo(const std::vector<fs::path>& extensiones, const fs::path& ruta);
