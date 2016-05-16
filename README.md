# Multimidia
trabalho compressor texto

O trabalho foi desenvolvido utilizando a linguagem C e compilado utilizando o GNU GCC.

#Instruções de Compilação
Junto com a implementação dos algoritmos encontra-se um arquivo Makefile; para compilar o programa execute o comando "make" no diretório onde encontra-se o projeto.

Após ser compilado o usuário poderá executar o programa da seguinte forma codificar/comprimir um arquivo:

1) $./main < encode -i ArquivodeEntrada.txt -o SaidaComprimida.bin --bwt=X --txtblck=N --huffman=X --runl=X.

Quanto setado o modo "encode" será selecionado o módulo de compressão do programa; a variável "-i" diz que a próxima string será o nosso arquivo de entrada a qual queremos comprimir; a string "-o" indica que a próxima string será o nome do nosso arquivo de saída. O comando "X" é uma variável, podendo ser "0" ou "1" e serve para indicar quais algoritmos serão usados na codificação (ser for "0", o algoritmo correspondente não será utilizado, mas caso seja "1", o algoritmo correspondente será utilizado).

A string "--bwt" faz referência ao algoritmo de compressão Burrows-Wheeler Transformation. A string "--txtblck" está ligada ao algoritmo BWT, e referencia ao tamanho que desejamos utilizar no algoritmo de compressão Burrows-Wheeler Transformation.

A string "--huffman" faz referência ao algoritmo de compressão Huffman.

A string "--runl" faz referência ao algoritmo de compressão Run-Length.

TODA linha de comando deverá ser acompanha de um PONTO FINAL. O ponto final indica fim da entrada de argumentos.

A string "main" faz referência ao nome do arquivo executável após o processo de compilação.

Se o usuário preferir, pode colar os seguintes comandos em um arquivo de e direcionar esse arquivo para entrada padrão do sistema:

$echo "encode -i ArquivodeEntrada.txt -o SaidaComprimida.bin --bwt=X --txtblck=N --huffman=X --runl=X." > ComandosDeEntrada.txt

E depois executar o seguinte comando:

$./main < ComandosDeEntrada.txt