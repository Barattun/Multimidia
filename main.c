/*
*TRABALHO MULTIMIDIA
*
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <sys/param.h>
#include "huff.h"


#define FALSE 0
#define TRUE 1
#define ENTER 10
#define SPACE 32
#define DOT 46
#define EQUALS 61

unsigned char *buffer;
unsigned int length;
unsigned int *T;
unsigned int buflen;
unsigned int *count;

typedef struct title CABECALHO;
struct title
{
    int bloco_size;
    int bwt;
    int huffman;
    int runlength;
};

typedef struct stream_t stream_t, *stream;
struct stream_t {
    
    int (*get)(stream);
    
    int (*put)(stream, int);
};
 

typedef struct {
    int (*get)(stream);
    int (*put)(stream, int);
    char *string;
    int pos;
} string_stream;
 
typedef struct {
    int (*get)(stream);
    int (*put)(stream, int);
    FILE *fp;
} file_stream;
 

int sget(stream in)
{
    int c;
    string_stream* s = (string_stream*) in;
    c = (unsigned char)(s->string[s->pos]);
    if (c == '\0') return -1;
    s->pos++;
    return c;
}
 
int sput(stream out, int c)
{
    string_stream* s = (string_stream*) out;
    s->string[s->pos++] = (c == -1) ? '\0' : c;
    if (c == -1) s->pos = 0;
    return 0;
}
 
int file_put(stream out, int c)
{
    file_stream *f = (file_stream*) out;
    return fputc(c, f->fp);
}
 

void output(stream out, unsigned char* buf, int len)
{
    int i;
    out->put(out, 128 + len);
    for (i = 0; i < len; i++)
        out->put(out, buf[i]);
}
 

void encode(stream in, stream out)
{
    unsigned char buf[256];
    int len = 0, repeat = 0, end = 0, c;
    int (*get)(stream) = in->get;
    int (*put)(stream, int) = out->put;
 
    while (!end) {
        end = ((c = get(in)) == -1);
        if (!end) {
            buf[len++] = c;
            if (len <= 1) continue;
        }
 
        if (repeat) {
            if (buf[len - 1] != buf[len - 2])
                repeat = 0;
            if (!repeat || len == 129 || end) {
                /* write out repeating bytes */
                put(out, end ? len : len - 1);
                put(out, buf[0]);
                buf[0] = buf[len - 1];
                len = 1;
            }
        } else {
            if (buf[len - 1] == buf[len - 2]) {
                repeat = 1;
                if (len > 2) {
                    output(out, buf, len - 2);
                    buf[0] = buf[1] = buf[len - 1];
                    len = 2;
                }
                continue;
            }
            if (len == 128 || end) {
                output(out, buf, len);
                len = 0;
                repeat = 0;
            }
        }
    }
    put(out, -1);
}
 
void decode(stream in, stream out)
{
    int c, i, cnt;
    while (1) {
        c = in->get(in);
        if (c == -1) return;
        if (c > 128) {
            cnt = c - 128;
            for (i = 0; i < cnt; i++)
                out->put(out, in->get(in));
        } else {
            cnt = c;
            c = in->get(in);
            for (i = 0; i < cnt; i++)
                out->put(out, c);
        }
    }
}
int Runlength(int flag, char *name_input, char *name_output, int *tam)
{

    FILE *fpin = fopen(name_input,"rb");
    if (!fpin)
        printf("ERROR\n");
    FILE *fpaux = fopen(name_output,"wb+");
    if (!fpaux)
        printf("ERRO 3rd\n");
    int i;
    char c;
    char *str = NULL;
    if (flag)
    {
    
        i=0;
        do{
            c = fgetc(fpin);
            if(c != -1){
                str = (char*)realloc(str,sizeof(char) * (i+1));
                str[i] = c;
                i++;
            }
        }while(!feof(fpin));

        str[i] = '\0';
        *tam = i;
    }
    int n;
    if (flag)
        n=i;
    else
        n=*tam;
    char buf[n];

    string_stream str_in = { sget, 0,str, 0};
    string_stream str_out = { sget, sput, buf, 0 };
 
    if (flag)
    {
        /* encode from str_in to str_out */
        encode((stream)&str_in, (stream)&str_out);
        
        if (!fwrite((stream)&str_out, sizeof(stream),1, fpaux))
        printf("ERRROOO escrita saida rle\n");
    }
    
    string_stream strAux = { sget, sput, buf, 0 };
    file_stream file = { 0, file_put, fpaux};

    if (!flag)
    {
        fseek(fpin, 0, SEEK_SET);
        if(!fread((stream)&strAux, 1, sizeof(stream),fpin))
        printf("ERRO leitura rle dcode\n");
       
    
        decode((stream)&strAux, (stream)&file);
    }
    fclose(fpaux);
    fclose(fpin);
    return 0;
}

int label_compare(char *str1, char *str2)
{
    /*Funcao compara strings */
    int i= 0, check = TRUE;
    while(str1[i]!='\0' && str2[i]!='\0')
    {
        if (str1[i] != str2[i])
        {
            check = FALSE;
            break;
        }
        i++;
    }
    return check;
}
char *copyString(char *buffer, int size)
{
    int i;
    char *source = (char*) malloc(sizeof(char)*size);
    if (buffer[0] == 32)
    {
        for (i = 0; i < size; i++)
        {
            source[i] = buffer[i+1];
        }
    }
    else
    {
        for (i = 0; i < 25; i++)
        {
            source[i] = buffer[i];
        }
    }
    return source;
}

int readLine(int *encode, int *decode, char **name_input, char **name_output, int *btw, int *txt, int *hf, int *rl)
{
    int i, count = 0;
    char character;
    char name[25], *comand = NULL;
    char *buffer = NULL;

    do
    {
        buffer = (char *) realloc(buffer, sizeof(char) * (count+1));
        character = fgetc(stdin);
        if (character == SPACE || character == EQUALS   || character == DOT)
        {
            if (count > 0)
            {
                buffer[count] = '\0';
                comand = copyString(buffer, count);
                if (label_compare(comand, "-i"))
                {
                    i = 0;
                    do
                    {
                        character=fgetc(stdin);
                        name[i] = character;
                        i++;
                    }
                    while(character != SPACE);
                    name[i-1] = '\0';
                    *name_input = copyString (name, i);
                }
                if (label_compare(comand, "-o"))
                {
                    i = 0;
                    do
                    {
                        character=fgetc(stdin);
                        name[i] = character;
                        i++;
                    }
                    while(character != SPACE);
                    name[i-1] = '\0';
                    *name_output = copyString(name, i);
                }
                if (label_compare(comand,"encode"))
                {
                    *encode = TRUE;
                }
                if (label_compare(comand,"decode"))
                {
                    *decode = TRUE;
                }
                if (label_compare(comand,"--bwt"))
                {
                    scanf("%d", btw);
                }
                if (label_compare(comand,"--txtblck"))
                {
                    scanf("%d", txt);
                }
                if (label_compare(comand,"--huffman"))
                {
                    scanf("%d", hf);
                }
                if (label_compare(comand,"--runl"))
                {
                    scanf("%d", rl);
                }
                free(comand);
                count = 0;
            }
        }
        else
        {
            buffer[count] = character;
            ++count;
        }
    }
    while(!feof(stdin));
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
int BWT( int TAM_BLOCO,char *name_input, char *name_output, CABECALHO *label)
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
    fpin = fopen(name_input,"rb+");
    if (!fpin)
    {
        printf("ERRO AO ABRIR O ARQUIVO DE ENTRADA"
               "\nconfira se o mesmo existe no diretorio do codigo\n");
        exit(1);
    }
    fpout = fopen(name_output,"wb+");
    if (!fpout)
    {
        printf("ERRO AO CRIAR O ARQUIVO DE SAIDA "
               " \nconfira se o mesmo existe no diretorio do codigo\n");
    }

    /*Escrevendo o cabeçalho*/
    fwrite(label, sizeof(CABECALHO), 1, fpout);

    while( 42 )
    {
        // do {
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
        for ( i = 0 ; i <= length ; ++i )
        {
            // Guarda o indice da linha original
            if ( indices[ i ] == 0 )
            {
                k = i;
                fputc( ( char )0, fpout );
            }
            else
            {
                fputc( buffer[ indices[ i ] - 1 ], fpout );
            }
        }
        fwrite( ( char * )&k, sizeof( unsigned int ),1, fpout );
        //}while(length == 0);
    }
    fclose(fpin);
    fclose(fpout);
    return 0;
}

int UNBWT(int TAM_BLOCO,char *name_input, char *name_output)
{
    unsigned int i, k, sum, previous;
    buffer = (unsigned char*) malloc(sizeof(unsigned char)*(TAM_BLOCO+1));
    T = (unsigned int*) malloc(sizeof(unsigned int)*(TAM_BLOCO+1));
    count = (unsigned int*) malloc(sizeof(unsigned int) * 256);

    FILE *fpin = NULL;
    FILE *fpout = NULL;

    fpin = fopen(name_input,"rb+");
    fpout = fopen(name_output,"wb");
    if (!fpin || !fpout)
    {
        printf("ERRO\n");
    }

    /*Posicionando o ponteiro no arquivo após o cabeçalho*/
    fseek(fpin, sizeof(CABECALHO), SEEK_SET);

    while ( 42 )
    {
        if( fread( ( char * )&buflen, sizeof( unsigned int ), 1, fpin ) == 0 )
            break;
        
        if ( fread( ( char * )buffer, 1, buflen, fpin ) != buflen );
        
        
        fread( ( char * )&k, sizeof( unsigned int ), 1, fpin );
        
        for ( i = 0; i < 256 ; ++i )
            count[ i ] = 0;

        for ( i = 0 ; i < buflen ; ++i )
            ++count[ buffer[ i ] ];
        --count[ 0 ];

        sum = 1; // Considera o EOF como caracter anterior ao 0
        previous = 0;
        for ( i = 0 ; i < 256 ; ++i )
        {
            previous = count[ i ];
            count[ i ] = sum;
            sum += previous;
        }

        // Agora calcular a funcao de transformacao T
        for ( i = 0 ; i < buflen ; ++i )
        {
            T[ ( i == k ? 0 : count[ buffer[ i ] ]++ ) ] = i;
        }

        // Imprime o conteudo original do vetor A
        k = T[ k ];
        for ( i = 0 ; i < buflen - 1; ++i )
        {
            putc( buffer[ k ], fpout);
            k = T[ k ];
        }
    }

    free(count);
    free(T);
    free(buffer);
    fclose(fpout);
    fclose(fpin);
    return 0;
}

static inline int read_byte(HuffStruct *decoder, FILE* out, unsigned int c)
{
    int i = 0;
    unsigned int shift = 1;
    int val;

    for(; i < 8; i += 1)
    {
        Bit b = (c & shift) && 1;
        val = Huff_Decode_Bit(decoder, b);

        if(val)
        {
            int decode = Huff_Decode_Data(decoder);
            if(decode == 256)
                return 1;
            fputc(decode, out);
        }
        shift <<= 1;
    }
    return 0;
}

static inline void write_byte(HuffStruct *encoder, FILE* out, int c)
{
    int bits, i;
    static unsigned char data = 0, mask = 1;
    bits = Huff_Encode_Data(encoder, c);
    for(i = 0; i < bits; i += 1)
    {
        if(Huff_Get_Encoded_Bit(encoder))
            data |= mask;


        if(mask == 0x80)
        {
            fputc(data, out);
            mask = 1;
            data = 0;
        }
        else
        {
            mask <<= 1;
        }
    }
}

void CallHuffman(char *name_input, char *name_output, CABECALHO *label)
{
    int c;
    FILE *inputFl = NULL, *outputFl = NULL;
    HuffStruct *encoder = Huff_Initialize_Adaptive_Encoder(257);

    if(encoder == NULL)
    {
        abort( );
    }
    if ((inputFl = fopen(name_input,"rb")) == NULL)
    {
        printf("\nErro ao abrir o arquivo entrada\n");
        exit(1);
    }
    if ((outputFl=fopen(name_output, "wb+")) == NULL)
    {
        printf("\nErro ao abrir o arquivo saida\n");
        exit(1);
    }

    fwrite(label, sizeof(CABECALHO), 1, outputFl);

    while((c = fgetc(inputFl)) != EOF)
    {
        write_byte(encoder, outputFl, c);
    }

    write_byte(encoder, outputFl, 256);

    fclose(inputFl);
    fclose(outputFl);
}

void UndoHuffman(char *name_input, char *name_output)
{
    int c;
    FILE *inputFl = NULL, *outputFl = NULL;
    HuffStruct *encoder = Huff_Initialize_Adaptive_Encoder(257);

    if(encoder == NULL)
    {
        abort();
    }

    if ((inputFl = fopen(name_input,"rb")) == NULL)
    {
        printf("\nErro ao abrir o arquivo entrada\n");
        exit(1);
    }
    if ((outputFl=fopen(name_output, "wb")) == NULL)
    {
        printf("\nErro ao abrir o arquivo saida\n");
        exit(1);
    }

    //Posicionando o ponteiro no arquivo após o cabeçalho
    fseek(inputFl, sizeof(CABECALHO), SEEK_SET);

    while((c = fgetc(inputFl)) != EOF && !read_byte(encoder, outputFl, c)) { }

    fclose(inputFl);
    fclose(outputFl);
}

void RunLength(char *name_input, char *name_output, CABECALHO *label)
{
    FILE *fpinput = fopen(name_input,"rb");
    FILE *fpoutput = fopen(name_output,"wb");

    unsigned char anterior, letra;                  //le oprimeiro caracter
    anterior = fgetc(fpinput);                  //le oprimeiro caracter

    unsigned int cont = 1;                                      //inicia o contador pois ja foi lido um caracter
    while(anterior != EOF)                                          //enquanto conseguir ler o arquivo( not eof)
    {
        letra = fgetc(fpinput);                 //a variavel letra recebe o segundo caracter
        if(letra == anterior)                         // compara os caracteres lidos
            cont++;                                   //se forem iguais acresse o contador
        else
        {
            if(cont > 1)                              //se forem diferentes deve-se colocar no arq de saida
            {
                //o marcador
                putc('@',fpoutput);
                fwrite((char *)&count, sizeof(unsigned int),1, fpoutput);
                //zip.write(( char* )&cont, sizeof(int)); // escreve no arquivo o valor contido no contador
            }
            putc(anterior, fpoutput);                                          //que representa o quanto o caracter lido esta repetido
            //zip.put(anterior); //escreve o caracer
            anterior = letra;  // altera a variavel para o proximo caracter lido
            cont = 1; //retorna o contador para 01 pois apenas um caracter foi lido
        }
    }
    fclose(fpoutput);
    fclose(fpinput);
}
void UndoRunlength(char *name_input, char *name_output) /* esta rotina ainda nao foi implementada */
{
    FILE *fpinput = fopen(name_input,"rb");
    FILE *fpoutput = fopen(name_output,"wb");
    int numero, i;
    unsigned char letra = fgetc(fpinput);
    //unsigned int cont = 1;
    while(letra != EOF)
    {
        if(letra == '@')
        {
            //arq.read((char *)&numero, sizeof(int));//(int)arq.get();
            fread((char *)&numero, 1, sizeof(int),fpinput);
            letra = fgetc(fpinput);
            for(i=0; i < numero; i++)
            {
                putc(letra, fpoutput);
            }
        }
        else
        {
            putc(letra, fpoutput);
        }
        letra = fgetc(fpinput);
    }
    fclose(fpoutput);
    fclose(fpinput);
}

char *ConcatenaComandoMove(char *name_output)
{
    char *str=NULL;
    char mv[]= "mv ", auxiliar[]= " arquivoAuxiliar.bin";
    int tamanho;

    tamanho = strlen(name_output);

    str=(char*)malloc((tamanho + 3 + 23)*sizeof(char));

    strcpy(str, mv);
    strcat(str, name_output);
    strcat(str, auxiliar);

    return str;
}

int main(int argc, char const *argv[])
{
    char *name_input, *name_output, *str;
    int encode = FALSE, decode = FALSE;
    int tam, bwt = FALSE, txt_block = FALSE, hf = FALSE, rl = FALSE;
    FILE *AuxiliarArq = NULL;
    CABECALHO *label = (CABECALHO*)malloc(sizeof(CABECALHO));

    readLine(&encode, &decode, &name_input, &name_output, &bwt, &txt_block, &hf, &rl);
    label->bloco_size = txt_block;
    label->bwt = bwt;
    label->huffman = hf;
    label->runlength = rl;

    /*Auxiliar para executar comandos no terminal*/
    str=ConcatenaComandoMove(name_output);

    if (encode)
    {
        //Borruos & Whelles Transformation
        if (bwt)
        {
            if (txt_block > 0)
            {
                BWT(txt_block, name_input, name_output, label);

                printf("ok\n");
            }
            else printf("TAMANHO INVALIDO -> BLOCO DE TEXTO\n");
        }//Huffman
        if (hf)
        {
            if (bwt)
            {
                system(str);
                printf("\nVariavel STR: %s\n", str);
                free(name_input);
                name_input=(char*)malloc(22*sizeof(char));
                strcpy(name_input, "arquivoAuxiliar.bin");
                printf("\nString name input: %s\n", name_input);
            }
            /* Huffman(); */
            CallHuffman(name_input, name_output, label);

        }//Run Length
        if (rl)
        {
            if (bwt || hf)
            {
                system(str);
                free(name_input);
                name_input=(char*)malloc(22*sizeof(char));
                strcpy(name_input, "arquivoAuxiliar.bin");
            }
            Runlength(1,name_input,name_output, &tam);
            
        }

        if (hf || rl)
        {
            system("rm arquivoAuxiliar.bin");
        }

    }
    else if (decode)
    {
        printf("\nEntrou no Decode\n");
        if ((AuxiliarArq = fopen(name_input,"rb")) == NULL)
        {
            printf("\nErro ao abrir o arquivo entrada\n");
            exit(1);
        }
        fread(label, sizeof(CABECALHO), 1, AuxiliarArq);
        fclose(AuxiliarArq);

        //UNDO Run Length
        if (label->runlength)
        {
            /* UNDO Run Length();*/
            Runlength(0,name_input,name_output, &tam);
        }

        //unHuffman
        if (label->huffman)
        {
            if (label->runlength)
            {
                system(str);
                free(name_input);
                name_input=(char*)malloc(22*sizeof(char));
                strcpy(name_input, "arquivoAuxiliar.bin");
                if ((AuxiliarArq = fopen(name_input,"rb")) == NULL)
                {
                    printf("\nErro ao abrir o arquivo entrada\n");
                    exit(1);
                }
                fread(label, sizeof(CABECALHO), 1, AuxiliarArq);
                fclose(AuxiliarArq);
            }
            printf("\nTEste do huffman decode\n");
            /* UnHuffman(); */
            UndoHuffman(name_input, name_output);
        }

        //DECODE Borruos & Whelles Transformation
        if (label->bwt)
        {
            if (label->bloco_size > 0)
            {
                printf("size block text %d\n", label->bloco_size );
                if (label->runlength || label->huffman)
                {
                    system(str);
                    free(name_input);
                    name_input=(char*)malloc(22*sizeof(char));
                    strcpy(name_input, "arquivoAuxiliar.bin");
                    if ((AuxiliarArq = fopen(name_input,"rb")) == NULL)
                    {
                        printf("\nErro ao abrir o arquivo entrada\n");
                        exit(1);
                    }
                    fread(label, sizeof(CABECALHO), 1, AuxiliarArq);
                    
                    fclose(AuxiliarArq);
                }
                
                UNBWT(label->bloco_size, name_input, name_output);
            }
            else printf("TAMANHO INVALIDO -> BLOCO DE TEXTO\n");
        }
        
        if (label->runlength || label->huffman)
        {
            system("rm arquivoAuxiliar.bin");
        }
    }

    free(label);
    free(name_input);
    free(name_output);
    free(str);

    return 0;
}
