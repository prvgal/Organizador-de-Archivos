#include "interfaz.h"

Interfaz::Interfaz(const wxString& titulo) : wxFrame(nullptr, wxID_ANY, titulo){ 
	CrearControles(); 
	BindEventHandlers();
}

void Interfaz::CrearControles(){
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)).Bold());
	wxFont rutaFont(wxFontInfo(wxSize(0, 14)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	cabecera = new wxStaticText(panel, wxID_ANY, "Organizador", 
		wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
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
}

void Interfaz::SetColors(){
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

void Interfaz::BindEventHandlers(){
	addBoton->Bind(wxEVT_BUTTON, &Interfaz::ClickEnBotonAnadir, this);
	input->Bind(wxEVT_TEXT_ENTER, &Interfaz::InputEnter, this);
	lista->Bind(wxEVT_KEY_DOWN, &Interfaz::OnListKeyDown, this);
	clearBoton->Bind(wxEVT_BUTTON, &Interfaz::ClickEnBotonClear, this);
	inputRuta->Bind(wxEVT_TEXT_ENTER, &Interfaz::InputRutaEnter, this);
	startBoton->Bind(wxEVT_BUTTON, &Interfaz::ClickEnBotonStart, this);
}

void Interfaz::ClickEnBotonAnadir(wxCommandEvent& event){
	AnadirExtensionDesdeInput();
}

void Interfaz::InputEnter(wxCommandEvent& event) {
	AnadirExtensionDesdeInput();
}

void Interfaz::AnadirExtensionDesdeInput(){
	wxString extension = input->GetValue();
	
	// Para almacenar las extensiones, transformamos wxString a string
	std::string conversion = extension.ToStdString();

	bool esRepetido;
	std::string aux = GuardarExtension(extensiones, conversion, esRepetido);	// aux tendrá la extension con el punto añadido

	wxString myExtension(aux);	// De std::string a wxString

	if(!extension.IsEmpty() && !esRepetido) 
		lista->Insert(myExtension, lista->GetCount());
	else{
		wxMessageDialog dialog(this, "No puede añadir dos extensiones iguales", "Error");
		dialog.ShowModal();
	}

	input->Clear();
	input->SetFocus();
}

void Interfaz::OnListKeyDown(wxKeyEvent& event){
	EliminarExtensionSeleccionada();
}

void Interfaz::EliminarExtensionSeleccionada(){
	int indexSeleccionado = lista->GetSelection();

	if (indexSeleccionado != wxNOT_FOUND){
		lista->Delete(indexSeleccionado);
		EliminarExtensionDeLaLista(extensiones, indexSeleccionado);
	}
}

void Interfaz::ClickEnBotonClear(wxCommandEvent& event){
	if(!lista->IsEmpty()){
		wxMessageDialog dialog(this, "¿Seguro que desea eliminar todas las extensiones añadidas?", "Borrar todo", wxYES_NO | wxCANCEL);
		
		int op = dialog.ShowModal();

		if(op == wxID_YES){
			lista->Clear();			// Eliminamos los elementos de la lista
			extensiones.clear();	// Eliminamos los elementos del vector
			extensiones.shrink_to_fit();	// Liberamos memoria no usada
		}
	}
}

void Interfaz::InputRutaEnter(wxCommandEvent& event){
	wxString getRuta = inputRuta->GetValue();

	std::string ruta = getRuta.ToStdString();

	SeleccionarTipo(extensiones, fs::path(ruta));
}

void Interfaz::ClickEnBotonStart(wxCommandEvent& event){
	wxString getRuta = inputRuta->GetValue();

	std::string ruta = getRuta.ToStdString();

	SeleccionarTipo(extensiones, fs::path(ruta));
}

// Constructor de la aplicacion
bool App::OnInit(){
	Interfaz* interfazPpal = new Interfaz("Organizador de Archivos");	// Titulo de la app

	// Configuraciones iniciales de la ventana
	interfazPpal->SetClientSize(800, 700);	
	interfazPpal->Center();
	interfazPpal->Show();
	
	return true;
}
