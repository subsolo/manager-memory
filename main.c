// ---------- ALGORITMO FIFO -------------
// |  SISTEMAS OPERACIONAIS - 5 PERIODO  |
// |   ATIVIDADE 2 PARCIAL - 13/05/18    |
// |       SISTEMAS DE INFORMAÇÃO        |
// | ALUNOS:                             |
// | 1. BRUNO ROBERTO DO ROSARIO.        |
// | 2. PAULO GUSTAVO ZANESE.            |
// ---------------------------------------

// PASSOS PARA RESOLUCAO DA ATIVIDADE:
// 1. CRIAR FUNÇÃO PARA LER ARQUIVO                                     - OK
// 2. CRIAR UMA LISTA ENCADEADA COM TAMANHO VARIAVEL (FRAMES)           - OK
// 3. FAZER COM QUE A LISTA NAO INSIRA ELEMENTO SE CHEGAR NO TAMANHO.   - EM ANDAMENTO
// 4. FUNCAO PARA VERIFICAR SE UMA PAGINA EXISTE NA LISTA.              - OK
// 5. PEGAR UM UNICO ELEMENTO DO ARQUIVO E CONVERTER PARA INT.          - PARA FAZER.

// SEQUENCIA DE EXECUCAO DO PROGRAMA:
// 1. LE O ARQUIVO NA FUNCAO E RETORNA UMA STRING (CHAR *);     - OK
// 2. VERIFICA SE O NUMERO EXISTE NA LISTA.                     - OK
// 3. INSERE NOVO ELEMENTO OU SUBSTITUI ALGUM EXISTENTE.

// ULTIMA ATUALIZAÇÃO: 15/05/2018.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define numPaginas 4;

typedef struct defMemoria
{
    int valor;
    struct defMemoria *prox;
} memoriaFifo;

//----- DEFINIR INICIO DA LISTA -----
memoriaFifo *inicio=NULL;

//----- ASSINATURA DAS FUNÇÕES (INTERFACE) ----------------------
char *lerArquivo(const char *arquivo);
int InserirPagina(int dado);
bool paginaExiste(int dado);
void ImprimirLista(void);


//----- INICIO MAIN ---------------------------------------------
int main(int argc, const char * argv[]) {
    
    char *result = lerArquivo("/Users/paulogusstavo/Desktop/SistemasOperacionais/FIFO/arquivo1.txt");
    
    //----- IMPRESSAO APENAS PARA TESTE DO ARQUIVO -----
    fputs(result, stdout);
    free(result);
    
    
//    if (!paginaExiste(result[1])) {
//        InserirPagina(result[1]);
//    }
//    else {
//
//    }
//    int p = 1;
//    while (result[p] != '\n') {
//        printf("PAULO: %d", p);
//    }
    
        printf("PAULO: %d\n", result[2]);
    
    //CADA VEZ QUE INSER UM ELEMENTO DA LISTA, UMA NOVA LISTA EH CRIADA.
    //EH NECESSARIO FAZER ELA VERIFICAR A CONSTANTE "paginas" E SOBREENCREVER.
    InserirPagina(1);
    InserirPagina(2);
    InserirPagina(3);
    InserirPagina(4);
    
    ImprimirLista();

    return 0;
}


// ----- FUNÇÕES ------------------------------------------------

char *lerArquivo(const char *arquivo)
{
    long int size = 0;
    //----- ABRIR ARQUIVO EM MODO LEITURA -----
    FILE *file = fopen(arquivo, "r");
    
    if(!file) {
        fputs("ERRO AO ABRIR O ARQUIVO.\n", stderr);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    
    //----- ALOCAÇÃO DINÂMICA DO ARQUIVO -----
    char *result = (char *) malloc(size);
    
    if(!result) {
        fputs("ERRO DE MEMÓRIA.\n", stderr);
        return NULL;
    }
    
    if(fread(result, 1, size, file) != size) {
        fputs("ERRO DE LEITURA.\n", stderr);
        return NULL;
    }
    
    fclose(file);
    return result;
}

int InserirPagina(int dado)
{
    memoriaFifo *p;
    p =  (memoriaFifo *) malloc(sizeof(memoriaFifo));
    if (p==NULL)
    {
        printf("ERRO DE ALOCAÇÃO.\n");
        return 0;
    }
    p->valor = dado;
    p->prox = NULL;
    if (inicio==NULL)
        inicio = p;
    else {
        p->prox = inicio;
        inicio  = p;
    }
    return 1;
}

void ImprimirLista()
{
    printf("--- LISTA ENCADEADA ---\n");
    memoriaFifo *ptr;
    
    if (inicio == NULL)
    {
        printf("--- FIM DA LISTA ---\n\n");
        return;
    }
    
    ptr = inicio;
    while (ptr !=NULL) {
        printf("%d\n",ptr->valor);
        ptr = ptr->prox;
    }
    printf("--- FIM DA LISTA ---\n\n");
}

bool paginaExiste(int dado)
{
     memoriaFifo *ptr;
    if (inicio == NULL)
        return false;

    ptr = inicio;
    while (ptr !=NULL)
        if (ptr->valor == dado)
            return true;
        else
            ptr = ptr->prox;
    
    return false;
}



