#include <iostream>

int main()
{
	int cinco = 5;
	int n;
	double a[25];
	double inv[25];
	double b[5];
	double x[5];
	double temp;
	double det;
	double max;
	int aux;
	int aux1;
	int imax;
	double factor;
	int i;
	int j;
	int k;

	std::cout << "Ingrese n: ";
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("a[%d][%d] = ", i + 1, j + 1);
			std::cin >> a[i * 5 + j];
		}
		printf("b[%d] = ", i + 1);
		std::cin >> b[i];
	}

	_asm {
		finit
		mov ecx, n					;Iniciando el primer loop
		mov esi, 0					;Índice i (recorre pivotes)
		loopRecorrerPivote:			;Inicio a recorrer los pivotes
			mov i, ecx				; Muevo ecx a un contador auxiliar i
			mov ecx, n				; Para crear mi contador(i + 1 to n)
			sub ecx, esi			; Creo mi contador n - i - 1 (i = esi, en este caso)
			sub ecx, 1				; Creo mi contador n - i - 1
			mov eax, esi			; Índice k(recorre filas)
			inc eax					; Incremento mi índice en 1, pues (i + 1 to n)
			mov imax, esi			; Inicializo imax = i
			mov edx, 0
			loopBuscarMaximo:
				mov eax, edx
				mul cinco				; eax * 5 = edx * 5, k * 5
				add eax, esi			; eax = edx * 5 + esi, k * 5 + i.
				mov edx, eax			; Muevo mi nuevo índice
				mov aux, edx
				mov aux1, ecx


	}
	std::cout << aux << "\n";
	std::cout << aux1;
}

	/*
				loopBuscarMaximo:
				mov eax, edx
				mul cinco				; eax * 5 = edx * 5, k * 5
				add eax, esi			; eax = edx * 5 + esi, k * 5 + i.
				mov edx, eax			; Muevo mi nuevo índice
				fld max					; Meto el max en el stack.st: max
				fld a[edx]				; Meto a[k][i](a[k * 5 + i]) en el stack.st: a[k][i], max
				fabs					; Valor absoluto de a[k][i].st: a[k][i], max
				fsub 					; max - a[k][i]. st: max-a[k][i]
				ftst					; Compara st con 0.0
				fstsw ax				; Registro bandera
				sahf					; Registro bandera
				fstp st					; Limpia el stack
				fld max
				fld a[edx]
					jb cambiar				;Si max < a[k][i] then: max = st(0)
					fstp st					; else: no cambiar max.Pop todo el stack
					fstp st					; Pops stack
					jmp finIfMaxAbs			; Salta al final del if

					cambiar:
					fstp max				; then: max = st(0).st : max
					fstp st					; Pops st. st vacío.
					mov imax, eax			; Guarda la posición donde se encontró

				finIfMaxAbs :			; Fin del if.
				add edx, cinco					; Incrementa edx (k) una posición
			loop loopBuscarMaximo	
	*/