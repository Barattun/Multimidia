# Multimidia
Trabalho - compressor de texto

Nome dos alunos:
	Bruno Molina Rosaboni n° 7656533
	Werik Amaral Fachim n° 7656512

O trabalho foi desenvolvido utilizando a linguagem C e compilado utilizando o GNU GCC. Todo o processo foi realizado em ambiente Linux.

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

2) $./main decode -i SaidaComprimida.bin -o SaidaVoltaOriginal.txt --bwt=X --txtblck=N --huffman=X --runl=X.

Quando utilizamos o modo "decode", o programa irá executar a sequência de descompressão, o elemento "-i" indica que a próxima string corresponde a um arquivo comprimido utilizando o método BWT e/ou Huffman e/ou Run-Length. O elemento "-o" indica que a próxima string será o nome do nosso arquivo de saída (arquivo descomprimido). Apesar de não ser necessário nessa operação, é importante manter as flags "--bwt=X --txtblck=N --huffman=X --runl=X." para critérios de execução de entrada; nesse caso não importa qual o valor de "X". Lembrando sempre ao final(ao setar as flags) deve-se adicionar um PONTO FINAL.

Para facilitar, pode-se fazer da mesma forma utilizada no passo 1
	|
	|-->> $echo "decode -i SaidaComprimida.bin -o SaidaVoltaOriginal --bwt=X --txtblck=N --huffman=X --runl=X." > ComandosDeEntrada.txt
		  $./main < ComandosDeEntrada.txt

Ao final da execução do "decode", teremos uma cópia do arquivo original comprimido.
Como foi exigido para o trabalho o uso de 3 algoritmos de compressão, foi necessário o uso de um cabeçalho, que é escrito em forma de "struct" no início do arquivo que está sendo comprimido.
Caso o usuário utilize essa implementação para comprimir e uma outra para descomprimir, ou outra implementação para comprimir e esta para descomprimir, terá problemas devido ao uso do nosso cabeçalho.

--> O comando "make clean" remove os arquivos "*.o" e o executável.
