#include <iostream>

int main()
{
	bool solucion = true;
	int cinco = 5;
	int ocho = 8;
	int n;
	double a[25];
	double inv[25];
	double b[5];
	double x[5];
	double temp;
	double det = 1;
	double max;
	int aux;
	int aux1;
	double prueba;
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

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << a[i * 5 + j] << " | ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	_asm {
		finit
		mov ecx, n					; Iniciando el primer loop
		mov esi, 0					; Índice i (recorre pivotes)

		; ------------------- INICIALIZAR MATRIZ INV (IDENTIDAD) PLS----------------- 

		loopRecorrerPivote:			; Inicio a recorrer los pivotes

			mov aux, ecx			; Muevo ecx a un contador auxiliar i
			mov ecx, n				; Para crear mi contador(i to n)
			sub ecx, esi			; Creo mi contador n - i - 1 (i = esi, en este caso)
			mov i, esi				; Guardo esi en un auxiliar i
			fldz
			fstp max				; Inicializo max = 0
			mov eax, esi			; k empieza en i
			mul cinco				; eax * 40 para acceder al a[k][i] = a[k * 5 + i]
			mul ocho
			add eax, esi			; eax = eax * 5 + i
			mov imax, esi			;Inicializo el imax(índice donde está el max)

			loopBuscarMaximoAbs:		;ENCUENTRA LA ENTRADA MÁXIMA ABSOLUTA EN UNA COLUMNA

				fld max				; Meto a max en el stack para comparar
				fld a[eax]			; Meto a a[k][i] en el stack para comparar

				fcomi st, st(1)		; Compara a[k][i] con max
				jna noCambiarMax	;

					fstp max			; Hace max = a[k][i]
					fstp st				; Limpia el stack
					mov imax, esi		; Hace el indice imax = esi, donde se encontró el max
					jmp finSiMaxAbs

					noCambiarMax:
					fstp st
					fstp st				;Pop el stack
					jmp finSiMaxAbs			

				finSiMaxAbs:

				inc esi					;Cambia de fila (virtualmente)
				add eax, 40				;Sume 5*8bytes a esi (k) (avance una fila)
			loop loopBuscarMaximoAbs

			fld max
			fldz
			fcomip st, st(1) 			;Si hay una columna de 0s, no hay sol
			fstp st						;Limpio el stack
			je noTieneSolucion			

			mov esi, i					;Restablezco esi a su valor original (el índice del for exterior)
			mov ecx, aux				;Restablezco el contador del for exterior
			
			cmp imax, esi				;Veo si imax != i
			je noCambiarFila			;Si son iguales, no cambie la fila
				mov aux, ecx			;Else: Cambie fila
				mov i, esi				;Guardo contadores externos
				mov ecx, n				;Inicio el nuevo contador 
				sub ecx, esi			;k <- i to n - 1 = n - i veces
				mov esi, i

					loopCambioFila:			;CAMBIA LA FILA PIVOTE i, CON LA FILA DE MAX(ABS) EN ESA COLUMNA
						
						mov eax, imax			;Meto imax en
						mul cinco				;eax = imax*5 (inicio de fila imax)
						add eax, esi			;eax = imax*5 + esi
						mul ocho				;eax = (imax*5 + esi)*8 = imax*40 + esi*8
						mov edx, eax			;edx = eax
						fld a[edx]				;imax*40 es constante. esi*8 indica la columna
						fstp temp				;temp = a[imax * 40 + k * 8]
						mov eax, i				;eax = i 
						mul cinco				;eax = i*5
						add eax, esi			;eax = i*5 + esi
						mul ocho				;eax = (i*5 + esi)*8
						fld a[eax]				;st: a[i*40 + k*8]
						fstp a[edx]				;a[imax*40 + k*8] = a[i*40 + k*8]
						fld temp				;st: temp
						fstp a[eax]				;a[i * 40 + k * 8] = temp
						fld a[0]
						fstp prueba

						inc esi					;Pase a sig columna

					loop loopCambioFila

						mov esi, i				;Restablezco contadores e indices
						mov ecx, aux
						fld det
						fchs
						fstp det				;det = - det (pues se hizo una permutación de filas
			noCambiarFila:
				jmp finProvicional

			noTieneSolucion:
				mov solucion, 0

			finProvicional:
		}

	if (solucion == true) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << a[i * 5 + j] << " | ";
			}
			std::cout << "\n";
		}
	}
	else {
		std::cout << "No tiene solucion";
	}
	std::cout << prueba;
}

	/*
					
					mov eax, edx				;Inicializo eax con edx. i.e., eax = k 
					mul cinco					;eax*5 = edx*5, k*5
					add eax, esi				;eax = edx*5+esi, k*5 + i.
					fld max						;Meto el max en el stack. st: max
					------fld a[eax]					;Meto a[k][i] (a[k*5+i]) en el stack. st: a[k][i], max
					fabs						;Valor absoluto de a[k][i]. st: a[k][i], max
					fcomi st, st(1)				;Compara
					fwait						;Espera a que se haga la comparación
						ja cambiar					;then: max = st(0)
							fstp st						;else: no cambiar max. Pop todo el stack
							fstp st						;Pops stack
							jmp finIfMaxAbs				;Salta al final del if
						cambiar:
							fstp max					;then: max = st(0). st : max
							fstp st						;Pops st. st vacío.
							mov imax, eax				;Guarda la posición donde se encontró
					finIfMaxAbs:						;Fin del if.
					inc edx								;Incrementa edx (k) una posición
					loop loopBuscarMaximo
	*/