#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// ================================
// Inicializa o tabuleiro com água
// ================================
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// ================================
// Posiciona navio (horizontal, vertical ou diagonal)
// ================================
int posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                    int linha, int coluna,
                    int dirLinha, int dirColuna) {

    for (int i = 0; i < TAM_NAVIO; i++) {
        int novaLinha = linha + i * dirLinha;
        int novaColuna = coluna + i * dirColuna;

        if (novaLinha < 0 || novaLinha >= TAM_TABULEIRO ||
            novaColuna < 0 || novaColuna >= TAM_TABULEIRO ||
            tabuleiro[novaLinha][novaColuna] != AGUA) {
            return 0;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i * dirLinha][coluna + i * dirColuna] = NAVIO;
    }

    return 1;
}

// ================================
// Cria habilidade CONE (apontando para baixo)
// ================================
void criarCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {

            int meio = TAM_HABILIDADE / 2;

            if (j >= meio - i && j <= meio + i)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// ================================
// Cria habilidade CRUZ
// ================================
void criarCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {

    int meio = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {

            if (i == meio || j == meio)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// ================================
// Cria habilidade OCTAEDRO (losango)
// ================================
void criarOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {

    int meio = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {

            if (abs(i - meio) + abs(j - meio) <= meio)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// ================================
// Sobrepõe habilidade no tabuleiro
// ================================
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                       int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemLinha, int origemColuna) {

    int meio = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {

            int linhaTab = origemLinha + (i - meio);
            int colunaTab = origemColuna + (j - meio);

            if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                colunaTab >= 0 && colunaTab < TAM_TABULEIRO) {

                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == AGUA) {
                    tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                }
            }
        }
    }
}

// ================================
// Exibe o tabuleiro
// ================================
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {

    printf("\n=== TABULEIRO FINAL ===\n\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {

            if (tabuleiro[i][j] == AGUA)
                printf("~ ");
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* ");
        }
        printf("\n");
    }
}

// ================================
// MAIN
// ================================
int main() {

    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    // Navios
    posicionarNavio(tabuleiro, 1, 1, 0, 1);  // horizontal
    posicionarNavio(tabuleiro, 4, 4, 1, 0);  // vertical
    posicionarNavio(tabuleiro, 0, 9, 1, -1); // diagonal

    // Criar habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 2, 7);
    aplicarHabilidade(tabuleiro, cruz, 6, 2);
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);

    exibirTabuleiro(tabuleiro);

    return 0;
}