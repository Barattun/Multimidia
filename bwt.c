#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>

// Define a funcao de comparacao para a chamada a funcao qsort()
// Conforme sugerido por B&W, o final da string contem um caracter EOF
// distinto dos demais caracteres e com valor inferior.
// Na pratica, compara apenas ate o ultimo caracter da string.
int compare( const unsigned int *i1, const unsigned int *i2, unsigned char *buffer)
{
    unsigned int l1 = ( unsigned int ) ( length - *i1 );
    unsigned int l2 = ( unsigned int ) ( length - *i2 );
    int result = memcmp( buffer + *i1, buffer + *i2, l1 < l2 ? l1 : l2 );
    return ( result == 0 ? l1 - l2 : result );
}


// Considera a entrada padrao como fonte de dados.
// Joga os dados transformados pelo algoritmo BWT na saida padrao
// Apos os dados, grava o indice da linha que contem a string original
int BWT( int TAM_BLOCO,char *name_input, char *name_output)
{
    // Tamanho do ultimo bloco lido
    unsigned int length;
    // Vetor para armazenar o bloco de dados lido
    unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char) *TAM_BLOCO);
    // Vetor de indices, usado como substituto da matriz N x N
    int indices[ TAM_BLOCO + 1 ];
    unsigned int k, i;
    FILE *fpin  = NULL;
    FILE *fpout = NULL;
    fpin = fopen(name_input,"r");
    if (!fpin)
    {
        printf("ERRO AO ABRIR O ARQUIVO DE ENTRADA 
            \nconfira se o mesmo existe no diretorio do codigo\n");
        exit(1);
    }
    fpout = fopen(name_output, "wb");
    if (!fpout)
    {
        printf("ERRO AO CRIAR O ARQUIVO DE SAIDA 
            \nconfira se o mesmo existe no diretorio do codigo\n");
    }if
    //while( 42 ) {
    do {
        // Le o bloco de dados da entrada padrao
        length = fread( ( char * )buffer, 1, TAM_BLOCO, fpin);
        if ( length == 0 )
            break;
        // Salva o tamanho do bloco. Soma 1 para o caracter EOF
        i = length + 1;
        fwrite( ( char * )&i, sizeof( unsigned int ), 1, fpout );

        // Ordena as strings na matriz
        for ( i = 0 ; i <= length ; ++i )
            indices[ i ] = i;
        qsort( indices, ( int )( length + 1 ), sizeof( int ), ( int ( * )( const void *, const void * ) )compare, buffer );

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
        fwrite( ( char * )&k, 1, sizeof( unsigned int ), fpout );
    }while(length == 0);
    free(buffer);
    return 0;
}
