#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX_NOME 30
#define MAX_CODIGO 10
#define MAX_SUPERFICIE 15
#define MAX_AVIOES_ESPERA 10
#define MAX_AVIOES_CADASTRADOS 30
#define MAX_PISTAS 6
#define MAX_TIPO 10

/*EQUIPE: Elysa Francyne, Laysa Edwyges, Mirelly Fontes, Sophia Sacramento, Valéria Silva.*/

//struct para avião
typedef struct aviao{
    int idAviao;
    char nome[MAX_NOME];
    char modelo[MAX_NOME];
    char fabricante[MAX_NOME];
    char codigoVoo[MAX_CODIGO];
    int maxPassageiros;
    float velocidadeMax;
}Aviao;

//struct para pista
typedef struct pista{
    int idPista;
    char nome[MAX_NOME];
    float comprimento;
    char superficie[MAX_SUPERFICIE];
    Aviao avioesEspera[MAX_AVIOES_ESPERA];
}Pista;

//struct para aeroporto
typedef struct aeroporto{
    int idAeroporto;
    char nome[MAX_NOME];
    char codigoIATA[MAX_CODIGO];
    char tipo[MAX_TIPO];
    int capAnual;
    Aviao avioesCadastrados[MAX_AVIOES_CADASTRADOS];
    int qtdAvioesCadastrados;
    Pista pistasDisponiveis[MAX_PISTAS];
    int qtdPistasDisponiveis;
}Aeroporto;

void cadastrarAeroporto(Aeroporto *a){
    printf("Digite o ID do Aeroporto: ");
    scanf("%d", &a->idAeroporto);
    getchar();

    printf("Digite o nome do Aeroporto: ");
    fgets(a->nome, sizeof(a->nome), stdin);
    a->nome[strcspn(a->nome, "\n")] = '\0';

    printf("Digite o codigo IATA: ");
    fgets(a->codigoIATA, sizeof(a->codigoIATA), stdin);
    a->codigoIATA[strcspn(a->codigoIATA, "\n")] = '\0';

    printf("Digite o tipo (publico ou privado): ");
    fgets(a->tipo, sizeof(a->tipo), stdin);
    a->tipo[strcspn(a->tipo, "\n")] = '\0';

    printf("Digite a capacidade de passageiros anual: ");
    scanf("%d", &a->capAnual);
    getchar();

}

void visualizarAeroporto(Aeroporto *a){
    printf("\n=====INFORMACOES DO AEROPORTO=====\n");
    printf("ID: %d\n", a->idAeroporto);
    printf("Nome: %s\n", a->nome);
    printf("Codigo IATA: %s\n", a->codigoIATA);
    printf("Tipo: %s\n", a->tipo);
    printf("Capacidade de passageiros anual: %d\n", a->capAnual);

    if (a->qtdAvioesCadastrados == 0) {
        printf("Nenhum aviao cadastrado.\n");
    } else {
        printf("Avioes cadastrados:\n");
        for (int i = 0; i < a->qtdAvioesCadastrados; i++) {
            printf("%d - %s\n", i + 1, a->avioesCadastrados[i].nome);
        }
    }
    if (a->qtdPistasDisponiveis == 0) {
        printf("Nenhuma pista disponivel.\n");
    } else {
        printf("Pistas disponiveis:\n");
        for (int i = 0; i < a->qtdPistasDisponiveis; i++) {
            printf("  %d - %s\n", i + 1, a->pistasDisponiveis[i].nome);
        }
    }
    printf("====================================\n");
}

