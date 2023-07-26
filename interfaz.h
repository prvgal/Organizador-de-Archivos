#pragma once

#include <wx/wx.h>

#include "extensiones.h"
#include "organizar.h"

class Interfaz : public wxFrame {
	public:
		Interfaz(const wxString& titulo);
	private:
		void CrearControles();
		void BindEventHandlers();

		void ClickEnBotonAnadir(wxCommandEvent& event);
		void InputEnter(wxCommandEvent& event);
		void OnListKeyDown(wxKeyEvent& event);
		void ClickEnBotonClear(wxCommandEvent& event);
		void InputRutaEnter(wxCommandEvent& event);
		void ClickEnBotonStart(wxCommandEvent& event);

		void AnadirExtensionDesdeInput();
		void EliminarExtensionSeleccionada();

		void SetColors();
		
		wxPanel* panel;
		wxStaticText* cabecera;
		wxTextCtrl* input;
		wxButton* addBoton;
		wxListBox* lista;
		wxButton* clearBoton;
		wxStaticText* titutoRuta;
		wxTextCtrl* inputRuta;
		wxButton* startBoton;

		std::vector<fs::path> extensiones;
};

class App : public wxApp {
	public:
		virtual bool OnInit();
};