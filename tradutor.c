#include "Bibliotecas/bib.h"					/*Defini��o das fun��es*/
#include "Bibliotecas/misc.h"					/*Fun��es de arquivos e hex -> decimal*/
#include "Bibliotecas/preproc.h"
#include "Bibliotecas/parser.h"
#include "Bibliotecas/scanner.h"
#include "Bibliotecas/analise.h"
#include "Bibliotecas/traducaoIA32.h"

bool debug1 = true;

int main (int argc,char *argv[]) {

	SYMBOL_TABLE *comeco_tabela=NULL, *aux;

	if (!valida_linhacomando(argc, argv))
		return 0;

	/*Pr�-processa e salva o arquivo com o nome PREPROCESSED_FILE*/
	pre_processamento(argv[1], PREPROCESSED_FILE);

	/*Faz a an�lise do c�digo j� pr�-processado*/
	comeco_tabela = analise(PREPROCESSED_FILE);

	/*Mudando a flag de debug, observe os r�tulos*/
	if (debug1){
		printf ("\n\nRotulo\t\t\tEndereco\n");
		for (aux=comeco_tabela; aux != NULL; aux = aux->prox)
			printf ("%s\t\t\t\t%d\n", aux->rotulo, aux->endereco);
	}

	/*Se encontrar erros nem passa para a pr�xima fase*/
	if (error_count > 0){
		remove(PREPROCESSED_FILE);
		return 0;
	}

	/*TRADUZ PARA ASSEMBLY DE VERDADE*/
	sintese_linguagem(PREPROCESSED_FILE, DEFAULT_OUTPUT_NAME);

	/*FAZENDO O C�DIGO COM OS OPCODES*/
	sintese_codigo (PREPROCESSED_FILE, DEFAULT_OUTPUT_CODE, comeco_tabela);

	/*DEPOIS QUE J� FEZ O QUE TINHA QUE FAZER*/
	remove(PREPROCESSED_FILE);
	return 0;
}
