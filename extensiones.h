#pragma once

#include <string>
#include <vector>
#include <filesystem>


namespace fs = std::filesystem;

std::string GuardarExtension(std::vector<fs::path>& extensiones, std::string& extension, bool& encontrado);
bool esRepetido(const std::vector<fs::path>& extensiones, const fs::path& extBuscar);
void EliminarExtensionDeLaLista(std::vector<fs::path>& extensiones, int index);
