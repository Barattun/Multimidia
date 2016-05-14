/*
*TRABALHO MULTIMIDIA
*
*	AUTHOR: WERIK AMARAL FACHIM
* 
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>

#define FALSE 0
#define TRUE 1
#define ENTER 10
#define SPACE 32
#define DOT 46
#define EQUALS 61

unsigned char *buffer;
unsigned int length;

int label_compare(char *str1, char *str2) {
/*Funcao compara strings */
	int i= 0, check = TRUE;
	while(str1[i]!='\0' && str2[i]!='\0'){
		if (str1[i] != str2[i]){
			check = FALSE;
			break;
		}
		i++;
	}
	return check;
}
char *copyString(char *buffer, int size){
	int i;
	char *source = (char*) malloc(sizeof(char)*size);
	if (buffer[0] == ENTER){
		for (i = 0; i < size; i++){
			source[i] = buffer[i+1];
		}
	}else {
		for (i = 0; i < 25; i++){
			source[i] = buffer[i];
		}
	}
	return source;
}
int readLine(int *encode, int *decode, char **name_input, char **name_output, int *btw, 
	int *txt, int *hf, int *rl)
{
	int i, count = 0;	
	char character;
	char name[25], *comand = NULL;
	char *buffer = NULL;
	
	do{
		buffer = (char *) realloc(buffer, sizeof(char) * (count+1));
		character = fgetc(stdin);
		if (character == SPACE || character == EQUALS 	|| character == DOT)
		{	
			if (count > 0)
			{
				buffer[count] = '\0';
				comand = copyString(buffer, count);
				if (label_compare(comand, "-i"))
				{
					i = 0;
					do{
						character=fgetc(stdin);
						name[i] = character;
						i++;
					}while(character != SPACE);
					name[i] = '\0';
					*name_input = copyString (name, i);}
				if (label_compare(comand, "-o"))
				{
					i = 0;
					do{
						character=fgetc(stdin);
						name[i] = character;
						i++;
					}while(character != SPACE);
					name[i] = '\0';
					*name_output = copyString(name, i);}
				if (label_compare(comand,"encode"))  {*encode = TRUE;}
				if (label_compare(comand,"decode"))  {*decode = TRUE;}
				if (label_compare(comand,"--bwt"))    {scanf("%d", btw);}
				if (label_compare(comand,"--txtblck")){scanf("%d", txt);}
				if (label_compare(comand,"--huffman")){scanf("%d", hf);}
				if (label_compare(comand,"--runl"))   {scanf("%d", rl);}
				free(comand);
				count = 0;
			}
		}
		else
		{	
			buffer[count] = character;
			++count;
		}
	}while(!feof(stdin));
	free(buffer);
	return 0;
}
int compare( const unsigned int *i1, const unsigned int *i2)
{
    unsigned int l1 = ( unsigned int ) ( length - *i1 );
    unsigned int l2 = ( unsigned int ) ( length - *i2 );
    int result = memcmp( buffer + *i1, buffer + *i2, l1 < l2 ? l1 : l2 );
    return ( result == 0 ? l1 - l2 : result );
}
int BWT( int TAM_BLOCO,char *name_input, char *name_output)
{
    // Tamanho do ultimo bloco lido
    //unsigned int length;
    // Vetor para armazenar o bloco de dados lido
     buffer = (unsigned char *)malloc(sizeof(unsigned char) *TAM_BLOCO);
    // Vetor de indices, usado como substituto da matriz N x N
    int indices[ TAM_BLOCO + 1 ];
    unsigned int k, i;

    FILE *fpin  = NULL;
    FILE *fpout = NULL;
    printf("name input %s %d\n",name_input,(int)strlen(name_input) );
    fpin = fopen("caso.txt","rb+");
    if (!fpin)
    {
        printf("ERRO AO ABRIR O ARQUIVO DE ENTRADA" 
            "\nconfira se o mesmo existe no diretorio do codigo\n");
        exit(1);
    }
    fpout = fopen("arquivo.bin","wb+");
    if (!fpout)
    {
        printf("ERRO AO CRIAR O ARQUIVO DE SAIDA "
           " \nconfira se o mesmo existe no diretorio do codigo\n");
    }
    //while( 42 ) {
    do {
        // Le o bloco de dados da entrada padrao
        length = fread( ( char * )buffer, 1, TAM_BLOCO, fpin);
        if ( length == 0 )
            break;

        // Salva o tamanho do bloco. Soma 1 para o caracter EOF
        i = length + 1;
        if(fwrite( ( char * )&i, sizeof( unsigned int ), 1, fpout ))

        // Ordena as strings na matriz
        for ( i = 0 ; i <= length ; ++i )
            indices[ i ] = i;
        qsort( indices, ( int )( length + 1 ), sizeof( int ), ( int ( * )( const void *, const void * ) )compare );

        // Salva a ultima coluna da matriz
        for ( i = 0 ; i <= length ; ++i ) {
            // Guarda o indice da linha original
            if ( indices[ i ] == 0 ) {
                k = i;
                fputc( ( char )0, fpout );
            }
            else {
                fputc( buffer[ indices[ i ] - 1 ], fpout );
            }
        }
        fwrite( ( char * )&k, sizeof( unsigned int ),1, fpout );
    }while(length == 0);
    fclose(fpin);
    fclose(fpout);
    return 0;
}

int main(int argc, char const *argv[])
{
	char *name_input, *name_output; 
	int encode = FALSE, decode = FALSE; 
	int bwt = FALSE, txt_block = FALSE, hf = FALSE, rl = FALSE;
	
	readLine(&encode, &decode, &name_input, &name_output, &bwt, &txt_block, &hf, &rl);

	printf("encode %d\n",encode );
	printf("decode %d\n",decode );
	printf("%s\n",name_input);
	printf("%s\n",name_output);
	printf("bwt %d\n",bwt );
	printf("txtblck %d\n",txt_block);
	printf("hf %d\n", hf);
	printf("rl %d\n",rl );
	printf("Hi World =)\n");

	if (encode){
		//Borruos & Whelles Transformation
		if (bwt){
			if (txt_block > 0){
			printf("size block text %d\n",txt_block );
			BWT(txt_block, name_input, name_output);
			}else printf("TAMANHO INVALIDO -> BLOCO DE TEXTO\n");
		}//Huffman
		if (hf){
			/* Huffman(); */
		}//Run Length
		if (rl){
			/* Run Length();*/
		}
		
	}else if (decode)
	{
		
	}

	return 0;
}