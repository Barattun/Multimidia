/*Funções do trabalho*/
#ifndef _FUNCAO_H_
#define _FUNCAO_H_

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

int sget(stream);
int sput(stream, int);
int file_put(stream, int);
void output(stream, unsigned char*, int);
void encode(stream, stream);
void decode(stream, stream);
int Runlength(int, char*, char*, int*);
int label_compare(char*, char*);
char *copyString(char*, int);
int readLine(int*, int*, char**, char**, int*, int*, int*, int*);
int compare(const unsigned int*, const unsigned int*);
int BWT(int, char*, char*, CABECALHO*);
int UNBWT(int,char*, char*);
static inline int read_byte(HuffStruct*, FILE*, unsigned int);
static inline void write_byte(HuffStruct*, FILE*, int);
void CallHuffman(char*, char*, CABECALHO*);
void UndoHuffman(char*, char*);
void RunLength(char*, char*, CABECALHO*);
void UndoRunlength(char*, char*); /* esta rotina ainda nao foi implementada */
char *ConcatenaComandoMove(char*);



#endif