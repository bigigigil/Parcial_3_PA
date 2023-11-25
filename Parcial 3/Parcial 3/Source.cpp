/* = PARCIAL 3 = */
/* - Roxanna Abigail Mendoza González || Grupo 64 -*/
#include <windows.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include "resource.h"

char eventos[10][10] = {"LUCY","DAY6","EXO "};
int boletos;
char precio[100];
char num[20];
float gasto;
HWND g_login;
HWND g_edit1;
HWND g_edit2;
HINSTANCE H_LOGIN;
HINSTANCE H_INICIO;
HINSTANCE H_PROMO;
HINSTANCE H_COBRO;
HINSTANCE H_COMPRAS;



BOOL CALLBACK call_inicio(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK call_promo(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK call_cobro(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK call_compras(HWND, UINT, WPARAM, LPARAM);
//Ventana principal
BOOL CALLBACK call_login(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d) {
	DialogBox(H_LOGIN, MAKEINTRESOURCE(IDD_LOGIN), 0, call_login);
	return 0;
}

BOOL CALLBACK call_login(HWND handler, UINT message, WPARAM wPARAM, LPARAM lPARAM) {
	g_login = handler;
	g_edit1 = GetDlgItem(handler, IDC_EDIT1);
	g_edit2 = GetDlgItem(handler, IDC_EDIT2);
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wPARAM))
		{
		case IDC_BUTTON1:
			char usuario[100];
			char contrasena[100];
			GetWindowText(g_edit1, usuario, sizeof(usuario));
			GetWindowText(g_edit2, contrasena, sizeof(contrasena));

			if (strcmp(usuario, "roxanna") == 0 && strcmp(contrasena, "12345") == 0) {
				EndDialog(handler, IDOK);  // Cerrar el cuadro de diálogo con resultado IDOK (éxito)
				MessageBox(NULL, "Inicio de sesión exitoso", "Éxito", MB_OK | MB_ICONINFORMATION);
				
				DialogBox(H_INICIO, MAKEINTRESOURCE(IDD_INICIO), 0, call_inicio);
			}
			else {
				MessageBoxA(handler, "Ingreso incorrecto. Inténtalo de nuevo.", "Error", MB_OK | MB_ICONERROR);
			}
			
			break;
		}
		break;

	}

	return FALSE;
}

BOOL CALLBACK call_inicio(HWND handler, UINT message, WPARAM wPARAM, LPARAM lPARAM)
{
	
	switch (message){
	
	case WM_INITDIALOG: 
	

		SetDlgItemText(handler, IDC_stEVENTO1, eventos[0]);
		SetDlgItemText(handler, IDC_stEVENTO2, eventos[1]);
		SetDlgItemText(handler, IDC_stEVENTO3, eventos[2]);

		break;
	
	case WM_COMMAND:
		switch (LOWORD(wPARAM))
		{
		case IDC_BUTTON1:
			
			GetDlgItemText(handler, IDC_EDIT1, num, 20);
			boletos = atoi(num);
			EndDialog(handler, IDD_INICIO);

			DialogBox(H_PROMO, MAKEINTRESOURCE(IDD_PROMO), 0, call_promo);

			break;
		}
	}

	return FALSE;
}
BOOL CALLBACK call_promo(HWND handler, UINT message, WPARAM wPARAM, LPARAM lPARAM) {
	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wPARAM))
		{
		case IDC_BUTTON1:
			int cantid;
			cantid= boletos / 2;
				gasto = cantid * 55;
				EndDialog(handler, IDD_PROMO);

				DialogBox(H_COBRO, MAKEINTRESOURCE(IDD_COBRO), 0, call_cobro);

				break;
			case IDC_BUTTON2:
				int cantidad;
				cantidad = boletos;
				gasto=cantidad*49.5;
				EndDialog(handler, IDD_PROMO);

				DialogBox(H_COBRO, MAKEINTRESOURCE(IDD_COBRO), 0, call_cobro);
				break;
		}
	}
	return FALSE;

}
BOOL CALLBACK call_cobro(HWND handler, UINT message, WPARAM wPARAM, LPARAM lPARAM){
	switch (message)
	{
	case WM_INITDIALOG:
		float precioIVA;
		precioIVA = gasto * 1.16;
		sprintf_s(precio, "%.2f", precioIVA);
		SetDlgItemText(handler, IDC_stCOBRO, precio);
		break;
	case WM_COMMAND:
		switch (LOWORD(wPARAM)){
		case IDC_PAGAR:
			EndDialog(handler, IDD_COBRO);
			DialogBox(H_COMPRAS, MAKEINTRESOURCE(IDD_COMPRAS), 0, call_compras);
			break;
		}
	
	}
	return FALSE;
}
BOOL CALLBACK call_compras(HWND handler, UINT message, WPARAM wPARAM, LPARAM lPARAM) {

	switch (message)
	{
	case WM_INITDIALOG:

		SetDlgItemText(handler, IDC_stGASTO, precio);
		SetDlgItemText(handler, IDC_stBOLETOS, num);
		break;

	case WM_COMMAND:
		switch (LOWORD(wPARAM)) {
		case IDC_BUTTON1:
			DestroyWindow(handler);
			PostQuitMessage(0);
			break;
		}
	}
	return FALSE;

	
}