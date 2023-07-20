#ifndef EXTENSIONES_H
#define EXTENSIONES_H

void AnadirExtensiones(std::vector<fs::path>& extensiones);
void ImprimirExtensiones(const std::vector<fs::path>& extensiones);
fs::path IntroducirExtension(const std::vector<fs::path>& extensiones);

#endif