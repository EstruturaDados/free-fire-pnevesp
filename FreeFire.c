#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 10

typedef struct {
    char nome[20];
    char tipo[20];
    int quantidade;
} Item;

typedef struct {
    Item dados[TAM_MAX];
    int quantidade;
} ListaInventario;


void IniciarListaInventario(ListaInventario *lista) {
    lista->quantidade = 0;
}

void InserirListaInventario(ListaInventario *lista, Item novo) {
    if (lista->quantidade == TAM_MAX) {
        printf("Inventário cheio!\n");
        return;
    }

    lista->dados[lista->quantidade] = novo;
    lista->quantidade++;

    printf("Item '%s' inserido com sucesso!\n", novo.nome);
}

void RemoverListaInventario(ListaInventario *lista, const char* nome) {
    int pos = -1;
    for (int i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    for (int i = pos; i < lista->quantidade - 1; i++) {
        lista->dados[i] = lista->dados[i + 1];
    }

    lista->quantidade--;
    printf("Item '%s' removido com sucesso!\n", nome);
}

void ordenarVetor(ListaInventario *lista) {
    for (int i = 0; i < lista->quantidade - 1; i++) {
        for (int j = i + 1; j < lista->quantidade; j++) {
            if (strcmp(lista->dados[i].nome, lista->dados[j].nome) > 0) {
                Item temp = lista->dados[i];
                lista->dados[i] = lista->dados[j];
                lista->dados[j] = temp;
            }
        }
    }
}

int buscarBinariaVetor(ListaInventario *lista, const char *nome) {
    int inicio = 0, fim = lista->quantidade - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, lista->dados[meio].nome);

        if (cmp == 0)
            return meio;

        else if (cmp > 0)
            inicio = meio + 1;

        else
            fim = meio - 1;
    }

    return -1;
}

void ListarInventario(const ListaInventario *lista) {
    if (lista->quantidade == 0) {
        printf("Inventário vazio.\n");
        return;
    }

    printf("\n- Inventário -\n");
    for (int i = 0; i < lista->quantidade; i++) {
        printf("- %s (Tipo: %s, Qtd: %d)\n",
               lista->dados[i].nome,
               lista->dados[i].tipo,
               lista->dados[i].quantidade);
    }
    printf("====================\n");
}


int main() {
    ListaInventario inventario;
    IniciarListaInventario(&inventario);

    int opcao;
    char nome[20];

    do {
        printf("\nMOCHILA DE SOBREVIVÊNCIA\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (binária)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            Item novo;
            printf("Nome do item: ");
            fgets(novo.nome, 20, stdin);
            novo.nome[strcspn(novo.nome, "\n")] = '\0';

            printf("Tipo do item: ");
            fgets(novo.tipo, 20, stdin);
            novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

            printf("Quantidade: ");
            scanf("%d", &novo.quantidade);
            getchar();

            InserirListaInventario(&inventario, novo);
        }

        else if (opcao == 2) {
            printf("Nome do item para remover: ");
            fgets(nome, 20, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            RemoverListaInventario(&inventario, nome);
        }

        else if (opcao == 3) {
            ListarInventario(&inventario);
        }

        else if (opcao == 4) {
            printf("Nome do item para buscar: ");
            fgets(nome, 20, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            ordenarVetor(&inventario);  // obrigatório antes da binária

            int pos = buscarBinariaVetor(&inventario, nome);

            if (pos == -1)
                printf("Item não encontrado.\n");
            else
                printf("Item encontrado na posição %d.\n", pos);
        }

    } while (opcao != 0);

    return 0;
}
