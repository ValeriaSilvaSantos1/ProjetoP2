#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOME 30
#define MAX_CODIGO 10
#define MAX_SUPERFICIE 15
#define MAX_AVIOES_ESPERA 10
#define MAX_AVIOES_CADASTRADOS 30
#define MAX_PISTAS 6
#define MAX_TIPO 10
#define MAX_AVIOES_FILA 10 

/* EQUIPE: Elysa Francyne, Laysa Edwyges, Mirelly Fontes, Sophia Sacramento, Valéria Silva. */

// Struct para avião
typedef struct aviao {
    int idAviao;
    char nome[MAX_NOME];
    char modelo[MAX_NOME];
    char fabricante[MAX_NOME];
    char codigoVoo[MAX_CODIGO];
    int maxPassageiros;
    float velocidadeMax;
} Aviao;

// Struct para pista
typedef struct pista {
    int idPista;
    char nome[MAX_NOME];
    float comprimento;
    char superficie[MAX_SUPERFICIE];
    Aviao avioesEspera[MAX_AVIOES_ESPERA];
} Pista;

// Struct para fila de controle aéreo
typedef struct filaControleAereo {
    Aviao fila[MAX_AVIOES_FILA];
    int inicio, fim;
} FilaControleAereo;

// Struct para aeroporto
typedef struct aeroporto {
    int idAeroporto;
    char nome[MAX_NOME];
    char codigoIATA[MAX_CODIGO];
    char tipo[MAX_TIPO];
    int capAnual;
    Aviao avioesCadastrados[MAX_AVIOES_CADASTRADOS];
    int qtdAvioesCadastrados;
    Pista pistasDisponiveis[MAX_PISTAS];
    int qtdPistasDisponiveis;
    FilaControleAereo controleAereo;
} Aeroporto;

// Protótipos das funções
void inicializarFila(FilaControleAereo *f);
int adicionarAviaoFila(FilaControleAereo *f, Aviao a);
int removerAviaoFila(FilaControleAereo *f);
void visualizarFila(FilaControleAereo *f);

void cadastrarAeroporto(Aeroporto *a);
void visualizarAeroporto(Aeroporto *a);
void cadastrarAviao(Aeroporto *a);
void listarAvioes(Aeroporto *a);
void recuperarAviaoPorID(Aeroporto *a);
void atualizarAviao(Aeroporto *a);
void removerAviao(Aeroporto *a);
void menuAvioes(Aeroporto *a);
void cadastrarPista(Aeroporto *aero, Pista novaPista);
void listarPistas(const Aeroporto *aero);
Pista* recuperarPistaPorId(Aeroporto *aero, int id);
void atualizarPista(Aeroporto *aero, int id, const char *novoNome, float novoComprimento);
void removerPista(Aeroporto *aero, int id);
void menuPistas(Aeroporto *a);
void inicializarAeroporto(Aeroporto *a);

// Implementação das funções

void inicializarFila(FilaControleAereo *f) {
    f->inicio = 0;
    f->fim = 0;
}

int adicionarAviaoFila(FilaControleAereo *f, Aviao a) {
    if ((f->fim + 1) % MAX_AVIOES_FILA == f->inicio) {
        printf("Fila de controle aereo cheia.\n");
        return 0; 
    }

    f->fila[f->fim] = a;
    f->fim = (f->fim + 1) % MAX_AVIOES_FILA;
    printf("Aviao %s adicionado à fila.\n", a.nome);
    return 1; 
}

int removerAviaoFila(FilaControleAereo *f) {
    if (f->inicio == f->fim) {
        printf("Fila de controle aereo vazia.\n");
        return 0; 
    }

    Aviao aviaoAutorizado = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_AVIOES_FILA;
    printf("Avião %s autorizado a decolar!\n", aviaoAutorizado.nome);
    return 1; 
}

void visualizarFila(FilaControleAereo *f) {
    if (f->inicio == f->fim) {
        printf("Nenhum aviao na fila de controle aereo.\n");
        return;
    }

    printf("\n=====FILA DE CONTROLE AEREO=====\n");
    int i = f->inicio;
    while (i != f->fim) {
        printf("Aviao: %s\n", f->fila[i].nome);
        i = (i + 1) % MAX_AVIOES_FILA;
    }
    printf("==============================\n");
}

void inicializarAeroporto(Aeroporto *a) {
    a->qtdAvioesCadastrados = 0;
    a->qtdPistasDisponiveis = 0;
    inicializarFila(&a->controleAereo);
}

void cadastrarAeroporto(Aeroporto *a) {
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

void visualizarAeroporto(Aeroporto *a) {
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

void cadastrarAviao(Aeroporto *a) {
    if(a->qtdAvioesCadastrados >= MAX_AVIOES_CADASTRADOS) {
        printf("Limite de avioes cadastrados atingido.\n");
        return;
    }

    Aviao *av = &a->avioesCadastrados[a->qtdAvioesCadastrados];

    printf("Digite o ID do Aviao: ");
    scanf("%d", &av->idAviao);
    getchar();

    printf("Digite o nome do Aviao: ");
    fgets(av->nome, sizeof(av->nome), stdin);
    av->nome[strcspn(av->nome, "\n")] = '\0';

    printf("Digite o modelo do Aviao: ");
    fgets(av->modelo, sizeof(av->modelo), stdin);
    av->modelo[strcspn(av->modelo, "\n")] = '\0';

    printf("Digite o fabricante do Aviao: ");
    fgets(av->fabricante, sizeof(av->fabricante), stdin);
    av->fabricante[strcspn(av->fabricante, "\n")] = '\0';

    printf("Digite o codigo do voo: ");
    fgets(av->codigoVoo, sizeof(av->codigoVoo), stdin);
    av->codigoVoo[strcspn(av->codigoVoo, "\n")] = '\0';

    printf("Digite a quantidade maxima de passageiros: ");
    scanf("%d", &av->maxPassageiros);
    getchar();

    printf("Digite a velocidade maxima (km/h): ");
    scanf("%f", &av->velocidadeMax);
    getchar();

    a->qtdAvioesCadastrados++;
    printf("Aviao cadastrado com sucesso!\n");
}

void listarAvioes(Aeroporto *a) {
    if(a->qtdAvioesCadastrados == 0) {
        printf("Nenhum aviao cadastrado.\n");
        return;
    }

    printf("\n=====LISTA DE AVIOES=====\n");
    for(int i = 0; i < a->qtdAvioesCadastrados; i++) {
        Aviao *av = &a->avioesCadastrados[i];
        printf("ID: %d\n", av->idAviao);
        printf("Nome: %s\n", av->nome);
        printf("Modelo: %s\n", av->modelo);
        printf("Fabricante: %s\n", av->fabricante);
        printf("Codigo do Voo: %s\n", av->codigoVoo);
        printf("Maximo de Passageiros: %d\n", av->maxPassageiros);
        printf("Velocidade Maxima: %.2f km/h\n", av->velocidadeMax);
        printf("------------------------------\n");
    }
}

void recuperarAviaoPorID(Aeroporto *a) {
    if(a->qtdAvioesCadastrados == 0) {
        printf("Nenhum aviao cadastrado.\n");
        return;
    }

    int id;
    printf("Digite o ID do Aviao que deseja buscar: ");
    scanf("%d", &id);
    getchar();

    for(int i = 0; i < a->qtdAvioesCadastrados; i++) {
        if(a->avioesCadastrados[i].idAviao == id) {
            Aviao *av = &a->avioesCadastrados[i];
            printf("\n=====AVIAO ENCONTRADO=====\n");
            printf("ID: %d\n", av->idAviao);
            printf("Nome: %s\n", av->nome);
            printf("Modelo: %s\n", av->modelo);
            printf("Fabricante: %s\n", av->fabricante);
            printf("Codigo do Voo: %s\n", av->codigoVoo);
            printf("Maximo de Passageiros: %d\n", av->maxPassageiros);
            printf("Velocidade Maxima: %.2f km/h\n", av->velocidadeMax);
            printf("===========================\n");
            return;
        }
    }
    printf("Aviao com ID %d nao encontrado.\n", id);
}

void atualizarAviao(Aeroporto *a) {
    if(a->qtdAvioesCadastrados == 0) {
        printf("Nenhum aviao cadastrado.\n");
        return;
    }

    int id;
    printf("Digite o ID do Aviao que deseja atualizar: ");
    scanf("%d", &id);
    getchar();

    for(int i = 0; i < a->qtdAvioesCadastrados; i++) {
        if(a->avioesCadastrados[i].idAviao == id) {
            Aviao *av = &a->avioesCadastrados[i];

            printf("Digite o novo nome do Aviao: ");
            fgets(av->nome, sizeof(av->nome), stdin);
            av->nome[strcspn(av->nome, "\n")] = '\0';

            printf("Digite o novo modelo do Aviao: ");
            fgets(av->modelo, sizeof(av->modelo), stdin);
            av->modelo[strcspn(av->modelo, "\n")] = '\0';

            printf("Digite o novo fabricante do Aviao: ");
            fgets(av->fabricante, sizeof(av->fabricante), stdin);
            av->fabricante[strcspn(av->fabricante, "\n")] = '\0';

            printf("Digite o novo codigo do voo: ");
            fgets(av->codigoVoo, sizeof(av->codigoVoo), stdin);
            av->codigoVoo[strcspn(av->codigoVoo, "\n")] = '\0';

            printf("Digite a nova quantidade maxima de passageiros: ");
            scanf("%d", &av->maxPassageiros);
            getchar();

            printf("Digite a nova velocidade maxima (km/h): ");
            scanf("%f", &av->velocidadeMax);
            getchar();

            printf("Aviao atualizado com sucesso!\n");
            return;
        }
    }
    printf("Aviao com ID %d nao encontrado.\n", id);
}

void removerAviao(Aeroporto *a) {
    if(a->qtdAvioesCadastrados == 0) {
        printf("Nenhum aviao cadastrado.\n");
        return;
    }

    int id;
    printf("Digite o ID do Aviao que deseja remover: ");
    scanf("%d", &id);
    getchar();

    for(int i = 0; i < a->qtdAvioesCadastrados; i++) {
        if(a->avioesCadastrados[i].idAviao == id) {
            for(int j = i; j < a->qtdAvioesCadastrados - 1; j++) {
                a->avioesCadastrados[j] = a->avioesCadastrados[j + 1];
            }
            a->qtdAvioesCadastrados--;
            printf("Aviao removido com sucesso!\n");
            return;
        }
    }
    printf("Aviao com ID %d nao encontrado.\n", id);
}

void menuAvioes(Aeroporto *a) {
    int opcao;
    do {
        printf("\n=====MENU AVIOES=====\n");
        printf("1. Cadastrar Aviao\n");
        printf("2. Listar Todos os Avioes\n");
        printf("3. Recuperar Aviao por ID\n");
        printf("4. Atualizar Aviao\n");
        printf("5. Remover Aviao\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: cadastrarAviao(a); break;
            case 2: listarAvioes(a); break;
            case 3: recuperarAviaoPorID(a); break;
            case 4: atualizarAviao(a); break;
            case 5: removerAviao(a); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
}

void cadastrarPista(Aeroporto *aero, Pista novaPista) { 
    if (aero->qtdPistasDisponiveis < MAX_PISTAS) {
        aero->pistasDisponiveis[aero->qtdPistasDisponiveis] = novaPista;
        aero->qtdPistasDisponiveis++;
        printf("Pista cadastrada com sucesso!\n");
    } else {
        printf("Limite de pistas atingido!\n");
    }
    printf("====================================\n");
}

void listarPistas(const Aeroporto *aero) {
    if (aero->qtdPistasDisponiveis == 0) {
        printf("Nenhuma pista cadastrada.\n");
        return;
    }

    for (int i = 0; i < aero->qtdPistasDisponiveis; i++) {
        printf("ID: %d | Nome: %s | Comprimento: %.2f metros\n",
               aero->pistasDisponiveis[i].idPista,
               aero->pistasDisponiveis[i].nome,
               aero->pistasDisponiveis[i].comprimento);
    }
    printf("====================================\n");
}

Pista* recuperarPistaPorId(Aeroporto *aero, int id) {
    for (int i = 0; i < aero->qtdPistasDisponiveis; i++) {
        if (aero->pistasDisponiveis[i].idPista == id) {
            return &aero->pistasDisponiveis[i];
        }
    }
    return NULL;
}

void atualizarPista(Aeroporto *aero, int id, const char *novoNome, float novoComprimento) {
    Pista *p = recuperarPistaPorId(aero, id);
    if (p != NULL) {
        strcpy(p->nome, novoNome);
        p->comprimento = novoComprimento;
        printf("Pista atualizada com sucesso.\n");
    } else {
        printf("Pista com ID %d não encontrada.\n", id);
    }
    printf("====================================\n");
}

void menuPistas(Aeroporto *a) {
    int opcao;
    do {
        printf("\n===== MENU PISTAS =====\n");
        printf("1. Cadastrar Pista\n");
        printf("2. Listar Todas as Pistas\n");
        printf("3. Recuperar Pista por ID\n");
        printf("4. Atualizar Pista\n");
        printf("5. Remover Pista\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        int id;
        float comprimento;
        char nome[100];

        switch(opcao) {
            case 1: {
                Pista nova;
                printf("Digite o ID da nova pista: ");
                scanf("%d", &nova.idPista);
                getchar();
                printf("Digite o nome da nova pista: ");
                fgets(nova.nome, sizeof(nova.nome), stdin);  
                nova.nome[strcspn(nova.nome, "\n")] = '\0';
                printf("Digite o comprimento da nova pista: ");
                scanf("%f", &nova.comprimento);
                getchar();
                cadastrarPista(a, nova);
                break;
            }
            case 2:
                listarPistas(a);
                break;
            case 3:
                printf("Digite o ID da pista: ");
                scanf("%d", &id);
                getchar();
                Pista *p = recuperarPistaPorId(a, id);
                if (p != NULL) {
                    printf("ID: %d | Nome: %s | Comprimento: %.2f metros\n",
                           p->idPista, p->nome, p->comprimento);
                } else {
                    printf("Pista com ID %d não encontrada.\n", id);
                }
                printf("====================================\n");
                break;
            case 4:
                printf("Digite o ID da pista: ");
                scanf("%d", &id);
                getchar();
                printf("Digite o novo nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Digite o novo comprimento: ");
                scanf("%f", &comprimento);
                getchar();
                atualizarPista(a, id, nome, comprimento);
                break;
            case 5:
                printf("Digite o ID da pista a remover: ");
                scanf("%d", &id);
                getchar();
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
}

int main() {
    Aeroporto aeroporto;
    inicializarAeroporto(&aeroporto);
    int opcao;

    do {
        printf("\n==== MENU PRINCIPAL ====\n");
        printf("1. Aeroporto\n");
        printf("2. Aviões\n");
        printf("3. Pistas\n");
        printf("4. Controle Aéreo\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                int op1;
                printf("\n-- Menu Aeroporto --\n");
                printf("1. Cadastrar dados\n");
                printf("2. Visualizar informações\n");
                printf("Opção: ");
                scanf("%d", &op1);
                getchar();
                if (op1 == 1) cadastrarAeroporto(&aeroporto);
                else if (op1 == 2) visualizarAeroporto(&aeroporto);
                else printf("Opção inválida.\n");
                break;
            }
            case 2: {
                menuAvioes(&aeroporto);
                break;
            }
            case 3: {
                menuPistas(&aeroporto);
                break;
            }
            case 4: {
                int op4;
                printf("\n-- Menu Controle Aéreo --\n");
                printf("1. Adicionar avião à fila\n");
                printf("2. Listar aviões na fila\n");
                printf("3. Autorizar decolagem\n");
                printf("0. Voltar\n");
                printf("Opção: ");
                scanf("%d", &op4);
                getchar();

                switch (op4) {
                    case 1: {
                        int id;
                        printf("ID do avião: ");
                        scanf("%d", &id);
                        getchar();
                        int found = 0;
                        for (int i = 0; i < aeroporto.qtdAvioesCadastrados; i++) {
                            if (aeroporto.avioesCadastrados[i].idAviao == id) {
                                adicionarAviaoFila(&aeroporto.controleAereo, aeroporto.avioesCadastrados[i]);
                                found = 1;
                                break;
                            }
                        }
                        if (!found)
                            printf("Avião com ID %d não encontrado.\n", id);
                        break;
                    }
                    case 2: 
                        visualizarFila(&aeroporto.controleAereo); 
                        break;
                    case 3: 
                        removerAviaoFila(&aeroporto.controleAereo); 
                        break;
                    case 0:
                        printf("Voltando...\n");
                        break;
                    default:
                        printf("Opção inválida.\n");
                }
                break;
            }
            case 5:
                printf("Encerrando o programa. Até a próxima!\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 5);

    return 0;
}