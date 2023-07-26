#include "extensiones.h"

std::string GuardarExtension(std::vector<fs::path>& extensiones, std::string& extension, bool& encontrado){
	// Si no esta a�adido el punto al principio de la extension, lo a�adimos
	if(extension[0] != '.')
		extension = '.' + extension;

	fs::path ext = fs::path(extension);	// Transformamos a path el string extension

	// Guardamos la extension en el vector
	if(esRepetido(extensiones, ext))
		encontrado = true;
	else{
		extensiones.push_back(ext);
		encontrado = false;
	}

	// Devolvemos el string para que en la interfaz, se muestre con el punto al principio
	return extension;
}

bool esRepetido(const std::vector<fs::path>& extensiones, const fs::path& extBuscar){
	bool devolver = false;
	
	for(const auto& ext : extensiones){
		if(ext == extBuscar)
			devolver = true;
	}

	return devolver;
}

void EliminarExtensionDeLaLista(std::vector<fs::path>& extensiones, int index){
	extensiones.erase(extensiones.begin() + index);	// Eliminamos el elemento en la posici�n index
}
