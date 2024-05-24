#include <stdio.h>

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define	DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43
#define DEBUG 50
// #define STAY 51

int command(int instruction, int frist_bit)
{
	return (instruction - frist_bit)/100;
}

int where(int instruction)
{
	return instruction % 100;
}

void split(int instruction, int* codigoOperacao, int* operando)
{
	*operando = where(instruction);
	*codigoOperacao = command(instruction, *operando);
}

int main() 
{
	// int programa[100]; 
	int memoria[100];
	// for (int i = 0; i < 100; i++)
	//	memoria[i] = 0;
	int acumulador = 0;
	int contadorInstrucao = 0;
	int codigoOperacao = 0;
	int operando = 0;
	int registroInstrucao = 0;
	int err_status = 0;

	int leitura = 0;
	int contador = 0;
	while (leitura != -9999)
	{
		printf("%i - ", contador);
		scanf("%i", &leitura);
		if (contador < 100)
			memoria[contador] = leitura;
		contador++;
	}

	while (contadorInstrucao < 100)
	{

		registroInstrucao = memoria[contadorInstrucao];
		split(registroInstrucao, &codigoOperacao, &operando);

		/*
		codigoOperacao = registroInstrucao/100;
		operando = registroInstrucao - codigoOperacao;
		*/

		
		switch (codigoOperacao)
		{
		case READ: printf("?"); scanf("%i", &memoria[operando]); break;
		case WRITE: printf("%i", memoria[operando]); break;
		case LOAD: acumulador = memoria[operando]; break;
		case STORE: memoria[operando] = acumulador; break;
		case ADD: acumulador += memoria[operando]; break;
		case SUBTRACT: acumulador -= memoria[operando]; break;
		case DIVIDE: acumulador /= memoria[operando]; break;  
		case MULTIPLY: acumulador *= memoria[operando]; break;
		case BRANCH: contadorInstrucao = operando; err_status = 2; break;
		case BRANCHNEG: if (acumulador < 0) {contadorInstrucao = operando; err_status = 2;} break;
		case BRANCHZERO: if (acumulador == 0) {contadorInstrucao = operando; err_status = 2;} break;
		case HALT: printf("Seu programa acabou de executar!"); return operando;
		case DEBUG: printf("acumulador :%i contadorInstrucao:%i eodigoOperacao:%i operando:%i registroInstrucao:%i err_status:%i", acumulador, contadorInstrucao, codigoOperacao, operando, registroInstrucao ,err_status); break;
		default: err_status = 1; break;
		}
		switch (err_status)
		{
		case 0: contadorInstrucao++; break;
		case 1: printf("A instrução da linha %i não foi entendida e por tanto não foi computada. ERRO.", contadorInstrucao); contadorInstrucao = 100; break;
		case 2: err_status = 0; break;
		}
	}
	printf("seu programa não finalizou corretamente. como não virá mais nenhuma instrução o finalizamos."); return 0;
}



