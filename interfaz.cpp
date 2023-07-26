#include "interfaz.h"

Interfaz::Interfaz(const wxString& titulo) : wxFrame(nullptr, wxID_ANY, titulo) {
	CrearControles();
	BindEventHandlers();
}

void Interfaz::CrearControles() {
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)).Bold());
	wxFont rutaFont(wxFontInfo(wxSize(0, 14)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	cabecera = new wxStaticText(panel, wxID_ANY, "Organizador", wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	cabecera->SetFont(headlineFont);

	input = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 80), wxSize(495, 35), wxTE_PROCESS_ENTER);
	addBoton = new wxButton(panel, wxID_ANY, "Añadir", wxPoint(600, 80), wxSize(100, 35));
	lista = new wxListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
	clearBoton = new wxButton(panel, wxID_ANY, "Borrar todo", wxPoint(100, 525), wxSize(150, 35));

	titutoRuta = new wxStaticText(panel, wxID_ANY, "Ingrese la ruta del directorio que desea organizar", wxPoint(100, 570), wxDefaultSize, wxALIGN_LEFT);
	titutoRuta->SetFont(rutaFont);

	inputRuta = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 600), wxSize(495, 35), wxTE_PROCESS_ENTER);
	startBoton = new wxButton(panel, wxID_ANY, "Organizar", wxPoint(600, 600), wxSize(150, 35));

	// Ponemos los colores
	SetColors();

	// Creamos la barra de estado
	CreateStatusBar();
	SetStatusBarBackground(panel->GetBackgroundColour());	
}

// Función para establecer el color de fondo de la barra de estado
void Interfaz::SetStatusBarBackground(const wxColour& color) {
	wxStatusBar* statusBar = GetStatusBar();

	if (statusBar) {
		statusBar->SetBackgroundColour(color);
	}
}

void Interfaz::SetColors() {
	// Configuración de colores para el modo oscuro
	wxColour darkGrayBackground(56, 56, 56); // RGB: (56, 56, 56) representa el gris oscuro
	wxColour whiteText(255, 255, 255); // RGB: (255, 255, 255) representa el color blanco

	// Configuración del fondo
	panel->SetBackgroundColour(darkGrayBackground);
	input->SetBackgroundColour(darkGrayBackground);
	addBoton->SetBackgroundColour(darkGrayBackground);
	lista->SetBackgroundColour(darkGrayBackground);
	clearBoton->SetBackgroundColour(darkGrayBackground);
	inputRuta->SetBackgroundColour(darkGrayBackground);
	startBoton->SetBackgroundColour(darkGrayBackground);

	// Configuración de las letras
	panel->SetForegroundColour(whiteText);
	cabecera->SetForegroundColour(whiteText);
	input->SetForegroundColour(whiteText);
	addBoton->SetForegroundColour(whiteText);
	lista->SetForegroundColour(whiteText);
	clearBoton->SetForegroundColour(whiteText);
	titutoRuta->SetForegroundColour(whiteText);
	inputRuta->SetForegroundColour(whiteText);
	startBoton->SetForegroundColour(whiteText);
}

void Interfaz::BindEventHandlers() {
	addBoton->Bind(wxEVT_BUTTON, &Interfaz::ClickEnBotonAnadir, this);
	input->Bind(wxEVT_TEXT_ENTER, &Interfaz::InputEnter, this);
	lista->Bind(wxEVT_KEY_DOWN, &Interfaz::OnListKeyDown, this);
	clearBoton->Bind(wxEVT_BUTTON, &Interfaz::ClickEnBotonClear, this);
	inputRuta->Bind(wxEVT_TEXT_ENTER, &Interfaz::InputRutaEnter, this);
	startBoton->Bind(wxEVT_BUTTON, &Interfaz::ClickEnBotonStart, this);
}

void Interfaz::ClickEnBotonAnadir(wxCommandEvent& event) {
	AnadirExtensionDesdeInput();
}

void Interfaz::InputEnter(wxCommandEvent& event) {
	AnadirExtensionDesdeInput();
}

void Interfaz::AnadirExtensionDesdeInput() {
	wxString extension = input->GetValue();

	// Para almacenar las extensiones, transformamos wxString a string
	std::string conversion = extension.ToStdString();

	bool esRepetido;
	std::string aux = GuardarExtension(extensiones, conversion, esRepetido);	// aux tendrá la extension con el punto añadido

	wxString myExtension(aux);	// De std::string a wxString

	if (!extension.IsEmpty() && !esRepetido)
		lista->Insert(myExtension, lista->GetCount());
	else {
		wxMessageDialog dialog(this, "No puede añadir dos extensiones iguales", "Error");
		dialog.ShowModal();
	}

	input->Clear();
	input->SetFocus();
}

void Interfaz::OnListKeyDown(wxKeyEvent& event) {
	EliminarExtensionSeleccionada();
}

void Interfaz::EliminarExtensionSeleccionada() {
	int indexSeleccionado = lista->GetSelection();

	if (indexSeleccionado != wxNOT_FOUND) {
		lista->Delete(indexSeleccionado);
		EliminarExtensionDeLaLista(extensiones, indexSeleccionado);
	}
}

void Interfaz::ClickEnBotonClear(wxCommandEvent& event) {
	if (!lista->IsEmpty()) {
		wxMessageDialog dialog(this, "¿Seguro que desea eliminar todas las extensiones añadidas?", "Borrar todo", wxYES_NO | wxCANCEL);

		int op = dialog.ShowModal();

		if (op == wxID_YES) {
			lista->Clear();			// Eliminamos los elementos de la lista
			extensiones.clear();	// Eliminamos los elementos del vector
			extensiones.shrink_to_fit();	// Liberamos memoria no usada
		}
	}
}

void Interfaz::InputRutaEnter(wxCommandEvent& event) {
	wxString getRuta = inputRuta->GetValue();

	std::string ruta = getRuta.ToStdString();

	if(!extensiones.empty())
		OrganizarDirectorioPorExtension(fs::path(ruta));
	else {
		wxMessageDialog dialog(this, "Si no añade ninguna extensión, se organizará todas las extensiones que haya en el directorio", "Sin extensiones", wxYES_NO | wxCANCEL);

		int op = dialog.ShowModal();

		if (op == wxID_YES) {
			OrganizarDirectorioCompleto(fs::path(ruta));
		}
	}

	inputRuta->Clear();
	inputRuta->SetFocus();
}

void Interfaz::ClickEnBotonStart(wxCommandEvent& event) {
	wxString getRuta = inputRuta->GetValue();

	std::string ruta = getRuta.ToStdString();

	if (!extensiones.empty())
		OrganizarDirectorioPorExtension(fs::path(ruta));
	else {
		wxMessageDialog dialog(this, "Si no añade ninguna extensión, se organizará todas las extensiones que haya en el directorio", "Sin extensiones", wxYES_NO | wxCANCEL);

		int op = dialog.ShowModal();

		if (op == wxID_YES) {
			OrganizarDirectorioCompleto(fs::path(ruta));
		}
	}

	inputRuta->Clear();
	inputRuta->SetFocus();
}

void Interfaz::OrganizarDirectorioPorExtension(const fs::path& ruta) {
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

				// Mostramos en la barra de estado la ruta de los archivos que vamos a organizar
				SetStatusText("../" + dirOrigen.filename().string(), 0);

				CopiarArchivo(dirOrigen, dirGuardar);

				if (!fs::remove(dirOrigen)) {
					wxString msjError = wxString::Format("El archivo %s no ha podido eliminarse de su direccion original", dirOrigen.filename().string());
					wxMessageBox(msjError, "Error", wxOK);
				}
			}
		}

		// Informamos en la barra de estado que el proceso ha terminado
		SetStatusText("Se ha terminado de organizar");
	}
}

void Interfaz::OrganizarDirectorioCompleto(const fs::path& ruta) {
	if (!fs::is_directory(ruta))	// Comprobamos si la ruta es correcta
		wxMessageBox("La ruta no es correcta", "Error", wxOK);
	else {
		fs::path extension;
		std::vector<fs::path> listaExtns;

		for (const auto& iter : fs::directory_iterator(ruta)) {
			if (!fs::is_directory(iter)) {
				extension = iter.path().extension();
				listaExtns.push_back(extension);

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

				// Mostramos en la barra de estado la ruta de los archivos que vamos a organizar
				SetStatusText("../" + dirOrigen.filename().string(), 0);

				CopiarArchivo(dirOrigen, dirGuardar);

				if (!fs::remove(dirOrigen)) {
					wxString msjError = wxString::Format("El archivo %s no ha podido eliminarse de su direccion original", dirOrigen.filename().string());
					wxMessageBox(msjError, "Error", wxOK);
				}
			}
		}

		// Informamos en la barra de estado que el proceso ha terminado
		SetStatusText("Se ha terminado de organizar");
	}
}

// Constructor de la aplicacion
bool App::OnInit() {
	Interfaz* interfazPpal = new Interfaz("Organizador de Archivos");	// Titulo de la app

	// Configuraciones iniciales de la ventana
	interfazPpal->SetClientSize(800, 700);
	interfazPpal->Center();
	interfazPpal->Show();

	return true;
}