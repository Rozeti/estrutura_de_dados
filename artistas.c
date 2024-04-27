#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nome[100];
    char genero[100];
    char nacionalidade[100];
    char albuns[1000];
} Artista;

int comparar(const void *a, const void *b) {
    const Artista *artistaA = (const Artista *)a;
    const Artista *artistaB = (const Artista *)b;
    return strcmp(artistaA->nome, artistaB->nome);
}

void converterIniciaisParaMaiusculo(char *string) {
    int tamanho = strlen(string);
    for (int i = 0; i < tamanho; i++) {
        if (i == 0 || string[i - 1] == ' ') {
            string[i] = toupper(string[i]);
        } else {
            string[i] = tolower(string[i]);
        }
    }
}

void editarArtista(Artista artistas[], int contagem_artistas) {
    char buscaNome[100];
    printf("Digite o nome do artista que deseja editar: ");
    fgets(buscaNome, sizeof(buscaNome), stdin);
    buscaNome[strcspn(buscaNome, "\n")] = 0;
    converterIniciaisParaMaiusculo(buscaNome);

    int indiceEncontrado = -1;
    for (int i = 0; i < contagem_artistas; i++) {
        if (strcmp(artistas[i].nome, buscaNome) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("\nArtista nao encontrado.\n");
        return;
    }

    printf("\nArtista encontrado:\n");
    printf("->Nome: %s\n", artistas[indiceEncontrado].nome);
    printf("->Genero: %s\n", artistas[indiceEncontrado].genero);
    printf("->Nacionalidade: %s\n", artistas[indiceEncontrado].nacionalidade);
    printf("->Albuns:\n%s\n", artistas[indiceEncontrado].albuns);

    char escolha;
    printf("\nO que deseja editar?\n");
    printf("1. Nome\n");
    printf("2. Genero\n");
    printf("3. Nacionalidade\n");
    printf("4. Albuns\n");
    printf("Escolha uma opcao: ");
    scanf(" %c", &escolha);

    char novoValor[1000];
    switch (escolha) {
        case '1':
            printf("Digite o novo nome: ");
            getchar();
            fgets(novoValor, sizeof(novoValor), stdin);
            novoValor[strcspn(novoValor, "\n")] = 0;
            for (int i = 0; i < strlen(novoValor); i++) {
                if (i == 0 || novoValor[i - 1] == ' ') {
                    novoValor[i] = toupper(novoValor[i]);
                } else {
                    novoValor[i] = tolower(novoValor[i]);
                }
            }
            strcpy(artistas[indiceEncontrado].nome, novoValor);
            break;
        case '2':
            printf("Digite o novo genero: ");
            getchar();
            fgets(novoValor, sizeof(novoValor), stdin);
            novoValor[strcspn(novoValor, "\n")] = 0;
            strcpy(artistas[indiceEncontrado].genero, novoValor);
            break;
        case '3':
            printf("Digite a nova nacionalidade: ");
            getchar();
            fgets(novoValor, sizeof(novoValor), stdin);
            novoValor[strcspn(novoValor, "\n")] = 0;
            strcpy(artistas[indiceEncontrado].nacionalidade, novoValor);
            break;
        case '4':
            printf("Digite os novos albuns (separe com virgulas): ");
            getchar();
            fgets(novoValor, sizeof(novoValor), stdin);
            novoValor[strcspn(novoValor, "\n")] = 0;
            strcpy(artistas[indiceEncontrado].albuns, "");
            char *token = strtok(novoValor, ",");
            strcpy(artistas[indiceEncontrado].albuns, token);
            while ((token = strtok(NULL, ",")) != NULL) {
                strcat(artistas[indiceEncontrado].albuns, "\n");
                strcat(artistas[indiceEncontrado].albuns, token);
            }
            strcat(artistas[indiceEncontrado].albuns, "\n==========\n");
            break;
        default:
            printf("Opcao invalida.\n");
            return;
    }

    printf("\nAlteracoes aplicadas.\n");
}

void inserirNovoArtista(Artista artistas[], int *contagem_artistas) {
    Artista novoArtista;
    printf("Digite o nome do novo artista: ");
    fgets(novoArtista.nome, sizeof(novoArtista.nome), stdin);
    printf("Digite o genero musical: ");
    fgets(novoArtista.genero, sizeof(novoArtista.genero), stdin);
    printf("Digite a nacionalidade: ");
    fgets(novoArtista.nacionalidade, sizeof(novoArtista.nacionalidade), stdin);

    novoArtista.nome[strcspn(novoArtista.nome, "\n")] = 0;
    novoArtista.genero[strcspn(novoArtista.genero, "\n")] = 0;
    novoArtista.nacionalidade[strcspn(novoArtista.nacionalidade, "\n")] = 0;

    for (int i = 0; i < strlen(novoArtista.nome); i++) {
        if (i == 0 || novoArtista.nome[i - 1] == ' ') {
            novoArtista.nome[i] = toupper(novoArtista.nome[i]);
        } else {
            novoArtista.nome[i] = tolower(novoArtista.nome[i]);
        }
    }

    strcpy(artistas[*contagem_artistas].nome, novoArtista.nome);
    strcpy(artistas[*contagem_artistas].genero, novoArtista.genero);
    strcpy(artistas[*contagem_artistas].nacionalidade, novoArtista.nacionalidade);

    int numAlbuns;
    printf("Quantos albuns deseja inserir para este artista? ");
    scanf("%d", &numAlbuns);
    getchar();

    printf("Digite os albuns do artista (um por linha):\n");
    char album[100];
    strcpy(artistas[*contagem_artistas].albuns, "");
    for (int i = 0; i < numAlbuns; i++) {
        printf("Album %d: ", i + 1);
        fgets(album, sizeof(album), stdin);
        album[strcspn(album, "\n")] = 0;
        strcat(artistas[*contagem_artistas].albuns, album);
        strcat(artistas[*contagem_artistas].albuns, "\n");
    }
    strcat(artistas[*contagem_artistas].albuns, "==========\n");
    (*contagem_artistas)++;
}

void buscarArtistaPorNome(Artista artistas[], int contagem_artistas) {
    char buscaNome[100];
    printf("Digite o nome do artista que deseja buscar: ");
    fgets(buscaNome, sizeof(buscaNome), stdin);
    buscaNome[strcspn(buscaNome, "\n")] = 0;

    char buscaNomeLowerCase[100];
    strcpy(buscaNomeLowerCase, buscaNome);
    for (int i = 0; i < strlen(buscaNomeLowerCase); i++) {
        buscaNomeLowerCase[i] = tolower(buscaNomeLowerCase[i]);
    }

    int encontrado = 0; 

    int baixo = 0, alto = contagem_artistas - 1, meio;
    while (baixo <= alto) {
        meio = (baixo + alto) / 2;
        char nomeArtista[100];

        strcpy(nomeArtista, artistas[meio].nome);
        for (int i = 0; i < strlen(nomeArtista); i++) {
            nomeArtista[i] = tolower(nomeArtista[i]);
        }

        char *tokenBusca = strtok(buscaNomeLowerCase, " ");
        int encontradoPartes = 1;
        while (tokenBusca != NULL) {
            if (strstr(nomeArtista, tokenBusca) == NULL) {
                encontradoPartes = 0;
                break;
            }
            tokenBusca = strtok(NULL, " ");
        }

        if (encontradoPartes) {
            printf("\nArtista encontrado:\n");
            printf("->Nome: %s\n", artistas[meio].nome);
            printf("->Genero: %s\n", artistas[meio].genero);
            printf("->Nacionalidade: %s\n", artistas[meio].nacionalidade);
            printf("->Albuns:\n%s\n", artistas[meio].albuns);
            encontrado = 1; 
            break; 
        } else if (strcmp(nomeArtista, buscaNomeLowerCase) < 0) {
            baixo = meio + 1;
        } else {
            alto = meio - 1;
        }
    }
    if (!encontrado) {
        printf("\nArtista não encontrado.\n");
    }
}

void buscarAlbum(Artista artistas[], int contagem_artistas) {
    char buscaAlbum[100];
    printf("Digite o nome do album que deseja buscar: ");
    fgets(buscaAlbum, sizeof(buscaAlbum), stdin);
    buscaAlbum[strcspn(buscaAlbum, "\n")] = 0;

    for (int i = 0; i < strlen(buscaAlbum); i++) {
        buscaAlbum[i] = tolower(buscaAlbum[i]);
    }

    int encontrado = 0; 
    for (int i = 0; i < contagem_artistas; i++) {
        char albunsLowerCase[1000]; 
        strcpy(albunsLowerCase, artistas[i].albuns);
        
        for (int j = 0; j < strlen(albunsLowerCase); j++) {
            albunsLowerCase[j] = tolower(albunsLowerCase[j]);
        }

        if (strstr(albunsLowerCase, buscaAlbum) != NULL) {
            printf("\nResultado:\n");
            printf("->Nome: %s\n", artistas[i].nome);
            printf("->Genero: %s\n", artistas[i].genero);
            printf("->Nacionalidade: %s\n", artistas[i].nacionalidade);
            printf("->Albuns:\n%s\n", artistas[i].albuns);
            encontrado = 1; 
        }
    }

    if (!encontrado) {
        printf("\nNenhum resultado encontrado para '%s'.\n", buscaAlbum);
    }
}

void removerArtista(Artista artistas[], int *contagem_artistas) {
    char buscaNome[100];
    printf("Digite o nome do artista que deseja remover: ");
    fgets(buscaNome, sizeof(buscaNome), stdin);
    buscaNome[strcspn(buscaNome, "\n")] = 0;

    int indiceEncontrado = -1;
    for (int i = 0; i < *contagem_artistas; i++) {
        if (strcmp(artistas[i].nome, buscaNome) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("Artista nao encontrado.\n");
        return;
    }

    printf("Artista encontrado:\n");
    printf("->Nome: %s\n", artistas[indiceEncontrado].nome);
    printf("->Genero: %s\n", artistas[indiceEncontrado].genero);
    printf("->Nacionalidade: %s\n", artistas[indiceEncontrado].nacionalidade);
    printf("->Albuns:\n%s\n", artistas[indiceEncontrado].albuns);

    char escolha;
    printf("Deseja remover este artista? (s/n): ");
    scanf(" %c", &escolha);

    if (escolha == 's' || escolha == 'S') {
        for (int i = indiceEncontrado; i < *contagem_artistas - 1; i++) {
            strcpy(artistas[i].nome, artistas[i + 1].nome);
            strcpy(artistas[i].genero, artistas[i + 1].genero);
            strcpy(artistas[i].nacionalidade, artistas[i + 1].nacionalidade);
            strcpy(artistas[i].albuns, artistas[i + 1].albuns);
        }
        (*contagem_artistas)--;
        printf("Artista removido com sucesso.\n");
    } else {
        printf("Operacao cancelada.\n");
    }
}

int main() {
    FILE *arquivo = fopen("artistas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char buffer[1000];
    Artista artistas[100];

    int contagem_artistas = 0;
    while (fgets(buffer, sizeof(buffer), arquivo)) {
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) {
            continue;
        }
        if (strcmp(buffer, "==========") == 0) {
            strcat(artistas[contagem_artistas].albuns, "==========\n");
            contagem_artistas++;
        } else if (strlen(artistas[contagem_artistas].nome) == 0) {
            strcpy(artistas[contagem_artistas].nome, buffer);
        } else if (strlen(artistas[contagem_artistas].genero) == 0) {
            strcpy(artistas[contagem_artistas].genero, buffer);
        } else if (strlen(artistas[contagem_artistas].nacionalidade) == 0) {
            strcpy(artistas[contagem_artistas].nacionalidade, buffer);
        } else {
            strcat(artistas[contagem_artistas].albuns, buffer);
            strcat(artistas[contagem_artistas].albuns, "\n");
        }
    }

    fclose(arquivo);
    qsort(artistas, contagem_artistas, sizeof(Artista), comparar);

    int escolha;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir novo artista\n");
        printf("2. Remover artista\n");
        printf("3. Editar artista\n");
        printf("4. Buscar artista pelo nome\n");
        printf("5. Buscar album\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1:
                inserirNovoArtista(artistas, &contagem_artistas);
                qsort(artistas, contagem_artistas, sizeof(Artista), comparar);
                break;
            case 2:
                removerArtista(artistas, &contagem_artistas);
                break;
            case 3:
                editarArtista(artistas, contagem_artistas);
                break;
            case 4:
                buscarArtistaPorNome(artistas, contagem_artistas);
                break;
            case 5:
                buscarAlbum(artistas, contagem_artistas);
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida. Por favor, tente novamente.\n");
        }
    } while (escolha != 0);

    arquivo = fopen("artistas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saida.\n");
        return 1;
    }

    for (int i = 0; i < contagem_artistas; i++) {
        fprintf(arquivo, "%s\n%s\n%s\n%s", artistas[i].nome, artistas[i].genero, artistas[i].nacionalidade, artistas[i].albuns);
    }

    fclose(arquivo);
    printf("\nOrdenacao concluida e salva no arquivo.\n");
    return 0;
}
