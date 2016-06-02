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
#include "funcao.h"

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
            }
            else printf("TAMANHO INVALIDO -> BLOCO DE TEXTO\n");
        }//Huffman
        if (hf)
        {
            if (bwt)
            {
                system(str);
                free(name_input);
                name_input=(char*)malloc(22*sizeof(char));
                strcpy(name_input, "arquivoAuxiliar.bin");
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
