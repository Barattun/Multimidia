#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cabecalho
{
	char *VetOp = NULL;
};

typedef struct EntradaTipo
{
	char *ArquivoEntrada=NULL;
	char *ArquivoSaida=NULL;
	char *AllExec=NULL;
	unsigned int txtblck;
};

void ClassificaEntrada(int argc, char **argv);

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		ClassificaEntrada(argc, argv);
	}
	else
	{
		printf("\nEntrada Invalida\nExit!\n");
	}

	printf("\n");
	return 0;
}

void ClassificaEntrada(int argc, char **argv)
{
	int i, TamanhoPalavraEntrada;
	const char* OperacaoTipo[] = {"decode", "encode", "-i", "-o", "--bwt=", "--txtblck=", "--huffman=", "--runl="};
	char *AuxVarEntradaOp=NULL;

	for (i = 0; i < argc; ++i)
	{
		TamanhoPalavraEntrada = strlen(argv[i]);

		AuxVarEntradaOp=(char*)malloc((TamanhoPalavraEntrada+1)*sizeof(char));

		strcpy(AuxVarEntradaOp, argv[i]);
		strlwr(AuxVarEntradaOp);

		switch(AuxVarEntradaOp)
		{
			case OperacaoTipo[0]:
				/*Inserir diretivas para o DECODE*/

			case OperacaoTipo[1]:
				/*Inserir diretivas para o ENCODE*/

			case OperacaoTipo[2]:
				/*Inserir diretivas para ENTRADA (INPUT)*/

			case OperacaoTipo[3]:
				/*Inserir diretivas para SAIDA (OUTPUT)*/

			case OperacaoTipo[4]:
				/*Inserir diretivas para o Algoritmo BWT*/

			case OperacaoTipo[6]:
				/*Inserir diretivas para o Algoritmo HUFFMAN*/

			case OperacaoTipo[7]:
				/*Inserir diretivas para o Algoritmo RUN-LENGHT*/

		}
		
		free(AuxVarEntradaOp);
	}

	/*Fim da função Classifica*/
}

/*Parte retirada 1*/
/*if (stricmp(Decode, argv[0]) == 0)
		{
			//Rotina para o DECODE
			for (l = 1; l < argc; ++l)
			{
				if (strcmp(i, argv[l]) == 0)
				{
					if (l+1 >= argc-1 && strncmp(argv[l+1], "-XX", 1) != 0)
					{
						strcpy(inputName, argv[2]);
					}
					else
					{
						printf("\nErro! Formato de entrada invalido");
						exit(1);
					}
				}
				else if (strcmp(o, argv[l]) == 0)
				{
					/* code */
				/*}
			}
		}*/

/*printf("\n%s", argv[0]);
		/*Parte retirada 1*/

/*		if (strcasecmp(argv[1], OperacaoTipo[1]) == 0)
		{
			/*Toda a parte do Encode vai aqui*/
/*			printf("\nEncode deu Certo");


		}
		else if (strcasecmp(argv[1], OperacaoTipo[0]) == 0)
		{
			/*Toda a parte do Decode vai aqui*/
/*			printf("\nDecode deu Certo");
		}*/