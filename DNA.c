/*
Data: 09/10/2017
Projeto Bioinformática
*/

//bibliotecas utilizadas no programa.
#include <stdio.h> 
#include <stdlib.h>
#include <locale.h>

//declaração do tipo STRUCT.
typedef struct dna{
	
	char mol[10];
	int leitpos[3][9];
}tipdna;

//função declaradando os caracteres que podem ser validados(A,T,C,G).
int testadna(tipdna *dna){
	
	int i;

	for (i = 0;i < 10;i++){
		if ((dna[0].mol[i] != 'A') && (dna[0].mol[i] != 'T') && (dna[0].mol[i] != 'C') && (dna[0].mol[i] != 'G')){
			return 0;
		}
	}
	return 1;
}

//função para ler a entrada de caracteres de uma fita do DNA.
void lerdna(tipdna *dna){
	
	do{
		printf("Informe a sequência de DNA | ");
		scanf("%s", dna[0].mol);
	} while ((testadna(dna)) != 1);

}

//função para pegar a fita definida pelo usuário e inverte-lá.
void invert(tipdna *dna){
	
	int i;
	
	for (i = 0;i < 10;i++){

		switch (dna[0].mol[i]){
			
		case 'A':
			dna[1].mol[i] = 'T';
			break;
		case 'T':
			dna[1].mol[i] = 'A';
			break;
		case 'C':
			dna[1].mol[i] = 'G';
			break;
		case 'G':
			dna[1].mol[i] = 'C';
			break;
		default:
			break;
		}
	}
}

//função para exibir a fita invertida em relação a informada pelo usuario(C-G, A-T).
void exibir(tipdna *dna){
	
	int i;
	
	printf("\n\t\t\t/**********\\ DNA INVERTIDO /**********\\\n\n\t\t\t\t");
	
	for (i = 0; i < 10; i++){
		printf("%c", dna[1].mol[i]);
	}
}

//função para correr pelas fitas e devolver a quantidade e posição em relação ao CODON indentificado.
void leitura(tipdna *dna, char *codon){
	
	int i, j = 0, t, z, y;

	for (t = 0;t < 2;t++){
		dna[t].leitpos[0][0] = dna[t].leitpos[1][0] = dna[t].leitpos[2][0] = 0;

		for (j = 0; j < 3;j++){
			for (i = 0; i < 10; i += 3){
				if ((codon[0] == dna[t].mol[i + j]) && (codon[1] == dna[t].mol[i + j + 1]) && (codon[2] == dna[t].mol[i + j + 2])){
					switch (j){
						
					case 0:
						dna[t].leitpos[0][0]++;
						dna[t].leitpos[0][dna[t].leitpos[0][0]] = i;
						break;
					case 1:
						dna[t].leitpos[1][0]++;
						dna[t].leitpos[1][dna[t].leitpos[1][0]] = i;
						break;
					case 2:
						dna[t].leitpos[2][0]++;
						dna[t].leitpos[2][dna[t].leitpos[2][0]] = i;
						break;
					default:
						break;
					}
				}
			}
		}
		
		//mostra as quantidades e posições da primeira fita(SENSE) e da segunda fita(ANTI-SENSE).
		(t==0) ? printf("\n\t\t\t\t --------------------------\n\t\t\t\t\t+ (Sense)\n\t\t\t\t --------------------------") : printf("\n\n\t\t\t\t --------------------------\n\t\t\t\t\t– (Antisense)\n\t\t\t\t --------------------------");

		for (z = 0; z < 3; z++){
			printf("\n\n\t\t\t\tLeitura +%d\n", z + 1);
			printf("\n\t\t\t\t- Quantidade encontrada: %d", dna[t].leitpos[z][0]);
			printf("\n\t\t\t\t- Posições: ");
			for (y = 0; y < dna[t].leitpos[z][0]; y++){
				printf(" %d ", (dna[t].leitpos[z][y + 1]) + 1);
			}
		}
	}
}

//função principal do programa.
int main(){
	
	system("color F0");
	system("mode con:cols=95 lines=43");
	setlocale(LC_ALL, "");

	char codon[4];
	tipdna dna[2];
	int op;

	while (1){
		
		lerdna(dna);
		invert(dna);
		exibir(dna);
		
		//ler o CODON informado pelo usuário(3 caracteres).
		printf("\n\nInforme o CODON do DNA | ");
		scanf("%s", codon);

		leitura(dna, codon);
		
		//pergunta ao usuário se ele deseja informar uma nova sequencia de DNA e realizar as buscas.
		printf("\n\n\n\t\t\t    DESEJA INFORMAR UMA NOVA SEQUÊNCIA?\n\t\t\t\t[1 - SIM]     [2 - NAO]\n\t\t\t\t\t  -> ");
		scanf("%d", &op);
		(op != 2) ? : exit(0);

		system("cls");
	}

	system("pause");
	return 0;
}