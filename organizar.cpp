#include "organizar.h"

void OrganizarDirectorioPorExtension(const std::vector<fs::path>& extensiones, const fs::path& ruta) {
	if (!fs::is_directory(ruta))	// Comprobamos si la ruta es correcta
		wxMessageBox("La ruta no es correcta", "Error", wxOK);
	else {
		// Tenemos que crear los directorios correspondientes para cada extension
		for (const auto& extension : extensiones) {
			std::string aux = extension.string();
			fs::path dir = ruta / fs::path(aux.substr(1));	// Con esto eliminariamos el punto inicial de cada extension

			if (!fs::create_directory(dir)) {
				wxMessageBox("Error al crear un directorio", "Error", wxOK | wxICON_ERROR);
				wxExit();
			}
		}

		// Iteramos cada elemento de la ruta
		for (const auto& iter : fs::directory_iterator(ruta)) {
			if (!fs::is_directory(iter) && ExisteExtension(iter.path(), extensiones)) {
				fs::path dirOrigen = iter.path();
				std::string aux = dirOrigen.extension().string().substr(1);			// Eliminamos el . de la extension
				fs::path dirGuardar = ruta / fs::path(aux) / dirOrigen.filename();	// Obtenemos el archivo destino

				CopiarArchivo(dirOrigen, dirGuardar);

				if (!fs::remove(dirOrigen)) {
					wxString msjError = wxString::Format("El archivo %s no ha podido eliminarse de su direccion original", dirOrigen.filename().string());
					wxMessageBox(msjError, "Error", wxOK);
				}
			}
		}
	}
	
}

void OrganizarDirectorioCompleto(const fs::path& ruta) {
	if (!fs::is_directory(ruta))	// Comprobamos si la ruta es correcta
		wxMessageBox("La ruta no es correcta", "Error", wxOK);
	else {
		fs::path extension;
		std::vector<fs::path> extensiones;

		for (const auto& iter : fs::directory_iterator(ruta)) {
			if (!fs::is_directory(iter)) {
				extension = iter.path().extension();
				extensiones.push_back(extension);

				std::string aux = extension.string().substr(1);
				fs::path dir = ruta / fs::path(aux);

				// Comprobamos si ya se ha creado el directorio previamente
				if (!fs::exists(dir)) {
					if (!fs::create_directory(dir)) {
						wxMessageBox("Error al crear un directorio", "Error", wxOK | wxICON_ERROR);
						wxExit();
					}
				}

				fs::path dirOrigen = iter.path();
				fs::path dirGuardar = dir / dirOrigen.filename();

				CopiarArchivo(dirOrigen, dirGuardar);

				if (!fs::remove(dirOrigen)) {
					wxString msjError = wxString::Format("El archivo %s no ha podido eliminarse de su direccion original", dirOrigen.filename().string());
					wxMessageBox(msjError, "Error", wxOK);
				}
			}
		}
	}
}

// Necesitamos comprobar si el archivo existe dentro del vector de extensiones, en caso de que no exista, devuelve false
bool ExisteExtension(const fs::path& archivo, const std::vector<fs::path>& extensiones) {
	bool esValido = false;

	for (const fs::path& ext : extensiones) {
		if (archivo.extension() == ext)
			esValido = true;
	}

	return esValido;
}

// Copiamos un archivoOrigen a archivoDestino
void CopiarArchivo(const fs::path& archivoOrigen, const fs::path& archivoDestino) {
	std::ifstream origen(archivoOrigen, std::ios::binary);

	if (!origen) {
		wxString msjError = wxString::Format("El archivo %s no se pudo abrir", archivoOrigen.filename().string());
		wxMessageBox(msjError, "Error", wxOK);
		wxExit();
	}

	std::ofstream destino(archivoDestino, std::ios::binary);

	if (!destino) {
		wxString msjError = wxString::Format("El archivo %s no se pudo abrir", archivoOrigen.filename().string());
		wxMessageBox(msjError, "Error", wxOK);
		wxExit();
	}

	destino << origen.rdbuf();

	origen.close();
	destino.close();
}

void SeleccionarTipo(const std::vector<fs::path>& extensiones, const fs::path& ruta) {
	if (extensiones.empty())
		OrganizarDirectorioCompleto(ruta);
	else
		OrganizarDirectorioPorExtension(extensiones, ruta);
}