/*
Andressa Oliveira Bernardes 12121BSI201
Álvaro Ala Moraes Borges 12121BSI269
Giovanna Sara Lemos Guzzardi 12121BSI261
*/
#include <stdlib.h>	                                //malloc, free, exit
#include <stdio.h>	                                //scanf, printf
#include <stdbool.h>	                            //true, false
#include <string.h>	                                //funções de string

#define MAX_FILA 3	                                //máximo de elementos permitidos na fila
#define MAX_ELEMENTOS_FILA 15                       //número de elementos do arquivo cardapio.txt
#define MAX_ELEMENTOS_PILHA 40                      //máximo de elementos do arquivo chocolate.txt

struct Item{                                        //declarando a struct item
	int codigo;                                     //codigo do item/refeição
	char refeicao[100];                             //nome da refeição
	float preco;                                    //preço em R$ da refeição
};
typedef struct Item item;                           //redefinindo o nome struct Item para item

void cardapio(item *menu, int X)                    //função *auxiliar* cardápio
//int X é o número de elementos do arquivo
{

	FILE *file;                                     //ponteiro para o arquivo que contém os itens

	file = fopen("cardapio.txt", "r");                    
	//abertura do arquivo que contém os itens para leitura
	if(file == NULL) {                                    
		//testando se o arquivo foi aberto corretamente
		printf("Erro ao abrir arquivo!\n");         //mensagem de erro
	}

	for(int i=0; i<X; i++) {                    //for para percorrer o menu
		fscanf(file, "%d %s %f", &(menu[i].codigo), menu[i].refeicao, &(menu[i].preco));
		//lendo do arquivo cada refeição: código, nome e preco
	}

	fclose(file);                                   //fechando o arquivo que contém os itens
}

void apresentaMenu(item *menu, int X)               //função *auxiliar* apresentaMenu
//X é o máximo de elementos do arquivo cardapio.txt
{
	printf("-----------------------------------------------------------------------------------\n");
	printf("CARDÁPIO RESTAURANTE ROSSAGI\n");       //RO de alvaRO, SSA de andresSA e de GIovanna
	for(int i=0; i<X; i++){                        //for para impressão do menu na tela
		printf("[%d]%s", menu[i].codigo, menu[i].refeicao);
		//imprimindo o código e o nome de cada refeição
		for(int j=0; j<(73 - strlen(menu[i].refeicao)); j++){
		//for para formatação do menu
			printf(".");
		}
		printf("%.2f\n", menu[i].preco);
		//imprimindo o preço de cada refeição
	}
	printf("-----------------------------------------------------------------------------------\n");
} 

//PARTE DA FILA DE CLIENTES (alocada dinâmicamente)
struct cliente{                                     //definindo e declarando a struct cliente
	char cliente[100];                              //nome do cliente
	item comanda[20];	                            //vetor de itens chamado comanda
	float totalConsumido;                           //total consumido em R$ por cada cliente
	int nItensEscolhidos;                            //quantidade de itens escolhidos pelo cliente
	//também necessário para fazer as comparações nos laços de repetições
};
typedef struct cliente cliente;                     //redefinindo o nome struct cliente para cliente

struct filaClientes{                                //definindo e declarando a struct cliente
	cliente elementos[MAX_FILA];                    //conjunto de elementos do tipo cliente
	int n_elem;		                                //número de elementos
	int primeiro;	                                //posição do primeiro elemento
	int ultimo;		                                //primeira posicao livre
};
typedef struct filaClientes filaClientes;
//redefinindo o nome struct filaClientes para filaClientes

filaClientes *criarFilaClientes()                   //função *criar* do tad filaClientes
{	
	filaClientes *FC;                               //declaração da filaClientes FC por referência
		
	FC = (filaClientes*) malloc(sizeof(filaClientes));
	//alocando memória para a filaClientes FC
	if (FC != NULL) {                               //alocou corretamente
		FC->n_elem = 0;
		//número de elementos da filaClientes FC recebe 0
		FC->primeiro = 0;
		//posição do primeiro elemento recebe 0 (vazia)
		FC->ultimo = 0;
		//posição do último elemento recebe 0 (vazia)
	}
	
	return FC;                                      //retorna a filaClientes FC
}

void destruirFilaClientes(filaClientes *FC)         //função  *destruir* do tad filaClientes
{ 
	if(FC != NULL) free(FC);
	//caso a alocação da fila tenha dado certo (!= NULL), libera a memória da filaClientes
}

bool vazia(filaClientes *FC)                        //função *vazia* do tad filaClientes 
{    
	if(FC->n_elem == 0) return true;                //se o número de elementos for = 0, retorna true
	else return false;                              //senão, retorna false
}

bool cheia(filaClientes *FC)                        //função *cheia* do tad filaClientes
{
	if(FC->n_elem == MAX_FILA) return true;
	//se o número de elementos da filaClientes for = ao máximo permitido, retorna true (está cheia)
	else return false;                              //senão, retorna false
}

cliente leItensCliente(item *menu, cliente X)       //função *auxiliar* do TAD filaClientes
//função *auxiliar* leItensCliente que lê os itens escolhidos por cada cliente
{

	int nItens, i, codigo;
	//nItens = quantidade de itens escolhidos pelo cliente, codigo = codigo do item

	printf("\nNome do(a) cliente: "); scanf("%s", &X.cliente);
	//lendo o campo cliente do elemento
	printf("Quantidade de itens a serem consumidos: "); scanf("%d", &nItens);
	//lendo a quantidade de itens que o cliente escolheu
	for(int i=0; i<nItens; i++){
		//for para ler o código de cada item escolhido do cliente
		printf("%dº item: ", i+1); scanf("%d", &codigo);
		X.nItensEscolhidos = nItens;
		/* atribuindo a quantidade de itens escolhidos pelo cliente ao campo de mesma serventia 
		"nItensEscolhidos" de cada elemento */
		X.comanda[i].codigo = menu[codigo-1].codigo;
		/* atribuindo o código de cada item escolhido pelo cliente a partir do menu (cardapio.txt) ao 
		campo de mesma função "codigo" da comanda de itens de cada elemento da filaClientes */
		strcpy(X.comanda[i].refeicao, menu[codigo-1].refeicao);
		/* copiando o nome da refeição (string) de cada item escolhido pelo cliente a partir do menu 
		(cardapio.txt) ao campo de mesma função "refeicao" da comanda de itens de cada elemento da 
		filaClientes */
		X.comanda[i].preco = menu[codigo-1].preco;
		/* atribuindo o preço de cada item escolhido pelo cliente a partir do menu (cardapio.txt) ao 
		campo de mesma função "preco" da comanda de itens de cada cliente da filaClientes */
	}

	return X;
}

bool insere(filaClientes *FC, cliente X)            //função *insere* do tad filaClientes
{
		
	if(cheia(FC) == true) {                         //se a filaClientes estiver cheia
		return false;                               //retorna false, não tem como inserir
	}
	//senão:
	FC->elementos[FC->ultimo] = X;                  //recebe X na posição do último elemento
	FC->n_elem = FC->n_elem + 1;                    //adiciona 1 no número de elementos
	
	if(FC->ultimo == (MAX_FILA-1)) FC->ultimo = 0;
	//se a posição (número) do último elemento for igual ao máximo permitido - 1, então a posição
	//do último elemento recebe 0 (a posição disponível é a posição 0)
	else FC->ultimo = FC->ultimo + 1;
	/* senão a posição do último elemento recebe a própria posição + 1; a posição disponível recebe
	a próxima posição */
	
	return true;                                    //retorna true
}

void imprimeElemento(cliente *X)                    //função *auxiliar* imprimeElemento
{

	printf("\n\nCliente: %s\n", X->cliente);        //imprime o campo cliente de cada elemento
	for(int i=0; i<(X->nItensEscolhidos); i++){
	//for para percorrer o vetor do campo "comanda" de cada cliente
		printf("\tCódigo da refeição: %d\n", X->comanda[i].codigo);    
		//imprime o campo "codigo" da comanda de itens de cada cliente
		printf("\tRefeição: %s\n", X->comanda[i].refeicao); 
		//imprime o campo "refeição" da comanda de itens de cada cliente
		printf("\tPreço refeição: %.2f\n", X->comanda[i].preco);
		//imprime o campo "preço" da comanda de itens de cada cliente
	}
	printf("  Preço total: R$%.2f\n", X->totalConsumido);
	//imprime o campo "totalConsumido" de cada elemento
}

bool retira(filaClientes *FC, cliente *X)           //função *retira* do tad filaClientes
{

	if(vazia(FC) == true) {                         //se a filaClientes estiver vazia
		return false;                               //retorna false, não tem como retirar
	}
	// senão:
	*X = FC->elementos[FC->primeiro];               //o elemento X recebe a posição do primeiro elemento
	FC->n_elem = FC->n_elem - 1;                    //subtrai 1 do número de elementos

	if(FC->primeiro == (MAX_FILA-1)) FC->primeiro = 0;
	//se a posição do primeiro elemento é igual ao máximo permitido - 1, então a posição do primeiro
	//elemento recebe 0
	else FC->primeiro = FC->primeiro + 1;
	//senão a posição do primeiro elemento recebe a própria posição + 1

	return true;                                    //retorna true
}

filaClientes *total(filaClientes *FC, cliente X)
//função *auxiliar* para mostrar o total consumido por cada cliente
{

	int i;
	filaClientes *auxiliar;                         //definindo uma filaClietes auxiliar
	auxiliar = criarFilaClientes();

	while(vazia(FC) == false){                      //enquanto a filaClientes FC não for vazia
		float soma=0;                               //definindo a variável soma com um número pequeno
		retira(FC, &X);                             //retira os elemento
		for(i=0; i<(X.nItensEscolhidos); i++){
			soma = soma + X.comanda[i].preco;       //soma os elementos
		}
		X.totalConsumido = soma;
		//o campo "totalConsumido" recebe o valor da soma dos itens
		insere(auxiliar, X);                        //insere os elemento na filaClientes auxiliar
	}
	while(vazia(auxiliar) == false){                //voltando os elementos para a filaClientes FC
		retira(auxiliar, &X);                       //retira os elementos da filaClientes auxiliar
		insere(FC, X); 	                            //insere os elementos na filaClientes FC
	}
	return FC;                                      //retorna a filaClientes com a soma total de cada cliente
}

void imprimeFilaClientes(filaClientes *FC, cliente X)
//função *auxiliar* para imprimir a filaClientes
{

	filaClientes *auxiliar;                         //declarando uma filaClientes auxiliar
	auxiliar = criarFilaClientes();
	int i;

	if(vazia(FC) == true){                         //se a filaClientes FC estiver vazia
		printf("A filaClientes está vazia!\n");
	}

	while(vazia(FC) == false){                      //while para percorrer a lista FC
		retira(FC, &X);                             //retira os elementos da filaClientes FC
		printf("Cliente: %s\n", X.cliente);         //imprime o campo cliente de cada elemento
		for(i=0; i<(X.nItensEscolhidos); i++){
		//for para percorrer o vetor do campo "comanda" de cada elemento
			printf("\tCódigo: %d\n", X.comanda[i].codigo);    
			//imprime o campo "codigo" da comanda de itens de cada elemento
			printf("\tRefeição: %s\n", X.comanda[i].refeicao); 
			//imprime o campo "refeição" da comanda de itens de cada elemento
			printf("\tPreço da refeição: R$%.2f\n", X.comanda[i].preco);
			//imprime o campo "preco" da comanda de itens de cada elemento
		}
		printf("  Preço total: R$%.2f\n\n", X.totalConsumido);
		//imprime o campo "totalConsumido" de cada elemento
		insere(auxiliar, X);                        //insere o elemento na filaClientes auxiliar
	}

	while(vazia(auxiliar) == false){                //while para percorrer a lista auxiliar
		retira(auxiliar, &X);                       //retira os elementos da filaClientes auxiliar
		insere(FC, X);                              //insere os elementos na filaClientes FC
	}
}

//PARTE DA PILHA DE CHOCOLATES (estática)
struct chocolate{                                   //definindo e declarando a struct cholocate
    char nome[100];                                 //nome do chocolate
};
typedef struct chocolate Chocolate;

struct pilha{                                       //declarando a struct pilha
    Chocolate chocolates[MAX_ELEMENTOS_PILHA];
	//declarando o vetor do tipo chocolates (aka matriz de char ou vetor de string)
    int topo;                                       //declarando o topo da pilha
};
typedef struct pilha Pilha;

void criarPilha(Pilha* p)                           //função *criar* do tad pilha
{
	p->topo = -1;                                   //topo da pilha recebe -1, está vazia
}

void destruirPilha(Pilha *p)                        //função *destruir* do tad pilha
{
	p->topo = -1;                                   //topo da pilha recebe -1, está vazia
}

void empilha(Pilha* p, Chocolate c)
//função *empilha* do tad pilha, onde os chocolates serão empilhados
{    
	if((p->topo) < (MAX_ELEMENTOS_PILHA-1)){        //se o topo da pilha for menor que o máximo permitido   
		p->topo = p->topo + 1;                      //o topo da pilha recebe a própria posição + 1
		p->chocolates[p->topo] = c;                 //a posição do topo recebe "c"
    }else{
        printf("A pilha está cheia!\n");            //senão imprime na tela que a pilha está cheia
    }
}

void desempilha(Pilha *p, Chocolate *c)             //função *desempilhar* do tad pilha
{
	if((p->topo) == -1) {                           //se o topo da pilha for igual -1
        printf("A pilha está vazia!\n");            //então imprime na tela que a pilha está vazia
    }else{                                          //senão...
        *c = p->chocolates[p->topo];                //o elemento "c" recebe a posição do topo
		p->topo = p->topo - 1;                      //o topo da pilha recebe a própria posição - 1
	}
}

void brinde(Pilha *p, char *nome_arquivo)           //função *auxiliar* brinde
{ 
	FILE* arquivo = fopen("chocolate.txt", "r");    //abre o arquivo chocolate.txt
    if (arquivo == NULL) {                          //verifica se o arquivo esta vazio
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    Chocolate c;                                    //cria a variável "c" do tipo Chocolate
    while (fscanf(arquivo, "%s", c.nome) != EOF) {  //while que lê o arquivo chocolate.txt
        empilha(p, c);
		//empilha cada elemento lido do arquivo chocolate.txt
    }

    fclose(arquivo);                                //fecha o arquivo
}

void entregaChocolates(Pilha *p, Chocolate *c, filaClientes *FC, cliente *X)
//função *auxiliar* que entrega os chocolates para os clientes que vão embora
{
	while(vazia(FC) == false){                      //enquanto a filaClientes não for vazia...
		retira(FC, X);                              //retira cada elemento da filaClientes FC
		desempilha(p, c);                           //desempilha elemento da pilha p
		printf("Cliente que foi embora: %s, chocolate que ele recebeu: %s\n", X->cliente, c->nome);
		//imprime o cliente que saiu e o chocolate que ele recebeu
	}
}

void imprimePilhaChocolates(Pilha *p, Chocolate choc)
//função *auxiliar* do tad pilha
{
    Pilha auxiliar;                                 //declarando uma pilha de cholocates auxiliar
	criarPilha(&auxiliar);                          //criando a pilha de chocolates auxiliar

	if(p->topo == -1){                              //se o topo da pilha é igual a -1
		printf("A pilha está vazia!\n");            //então imprime na tela que a pilha está vazia
	}

	printf("\nChocolates na pilha:\n");
	while((p->topo == -1) == false){                //enquanto a pilha não estiver vazia
		desempilha(p, &choc);                       //desempilha cada chocolate pilha p
		empilha(&auxiliar, choc);                   //empilha o mesmo chocolate na pilha auxiliar
	}

	while((auxiliar.topo == -1) == false) {         //enquanto a pilha auxiliar não estiver vazia
		desempilha(&auxiliar, &choc);               //desempilha da pilha auxiliar
		printf(" %s\n", choc.nome);                 //imprime na tela o nome do chocolate desempilhado
		empilha(p, choc);                           //empilha o mesmo chocolate na pilha p
	}
	printf("\n\n");

}

int main(){
	
	filaClientes *FC;                               //declarando a filaClientes FC
	cliente fregues;                                //declarando a variável fregues do tipo cliente

	FC = criarFilaClientes();
	if(FC == NULL){                                 //tratamento de erro
		printf("ERRO na alocação da filaClientes\n");
	}

	item menu[MAX_ELEMENTOS_FILA];                  //declarando vetor de itens chamado menu
	cardapio(menu, MAX_ELEMENTOS_FILA);             //abrindo e lendo o cardápio

	apresentaMenu(menu, MAX_ELEMENTOS_FILA);
	//função apresentaMenu faz a apresentação do menu para o cliente

	while(cheia(FC) == false){                      //enquanto a filaClientes não estiver vazia...
		fregues = leItensCliente(menu, fregues);
		insere(FC, fregues);	                    //...insere elementos
	}

	printf("\n\nLista dos clientes com o total consumido por cada um: \n");
	total(FC, fregues);
	//função total calcula o total consumido por cada cliente
	imprimeFilaClientes(FC, fregues);
	//função imprimeClientes imprime toda a filaClientes

	Pilha pilhaChocolates;                          //declara a variável pilhaChocolates
	Chocolate choc;                                 //declara a variável do tipo Chocolate

    criarPilha(&pilhaChocolates);

	brinde(&pilhaChocolates, "chocolate.txt");
	//abre e lê o arquivo chocolate.txt, empilha os elementos do arquivo na pilhaCholates, e fecha o arquivo

	imprimePilhaChocolates(&pilhaChocolates, choc);
	//função imprimePilhaClientes imprime toda a pilha de chocolates
	entregaChocolates(&pilhaChocolates, &choc, FC, &fregues);
	//a cada cliente que vai embora, é entregue um chocolate
	//a filaClientes é desenfileirada (os elementos são retirados)

	desempilha(&pilhaChocolates, &fregues);         //desempilha os chocolates que ficaram na pilha de chocolates
		
	destruirFilaClientes(FC);                       //desaloca a memória da filClientes
	destruirPilha(&pilhaChocolates);                //destrói a pilha de chocolates

	return 0;
}