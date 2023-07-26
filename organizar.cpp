#include "organizar.h"

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
