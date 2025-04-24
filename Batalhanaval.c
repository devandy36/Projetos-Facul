#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

typedef enum {
    AGUA = 0,
    NAVIO = 3,
    ACERTO = 1,
    ERRO = 2
} EstadoCelula;

typedef struct {
    EstadoCelula celulas[TAM_TABULEIRO][TAM_TABULEIRO];
    int acertos;
    int erros;
} Tabuleiro;

void inicializaTabuleiro(Tabuleiro *t) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            t->celulas[i][j] = AGUA;
        }
    }
    t->acertos = 0;
    t->erros = 0;
}

void exibeTabuleiro(Tabuleiro *t) {
    printf("\n  ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            switch (t->celulas[i][j]) {
                case AGUA: printf("~ "); break;
                case NAVIO: printf("~ "); break; // Oculto
                case ACERTO: printf("X "); break;
                case ERRO: printf("o "); break;
            }
        }
        printf("\n");
    }
}

int posicionaNavioHorizontal(Tabuleiro *t, int linha, int colunaInicial) {
    if (colunaInicial + TAM_NAVIO > TAM_TABULEIRO) return 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (t->celulas[linha][colunaInicial + i] != AGUA) return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        t->celulas[linha][colunaInicial + i] = NAVIO;
    }
    return 1;
}

int posicionaNavioVertical(Tabuleiro *t, int linhaInicial, int coluna) {
    if (linhaInicial + TAM_NAVIO > TAM_TABULEIRO) return 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (t->celulas[linhaInicial + i][coluna] != AGUA) return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        t->celulas[linhaInicial + i][coluna] = NAVIO;
    }
    return 1;
}

void ataque(Tabuleiro *t, int linha, int coluna) {
    if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO) {
        printf("⚠️  Ataque fora do tabuleiro!\n");
        return;
    }

    switch (t->celulas[linha][coluna]) {
        case NAVIO:
            printf("🔥 Acertou um navio!\n");
            t->celulas[linha][coluna] = ACERTO;
            t->acertos++;
            break;
        case AGUA:
            printf("💦 Errou! Água.\n");
            t->celulas[linha][coluna] = ERRO;
            t->erros++;
            break;
        case ACERTO:
        case ERRO:
            printf("⚠️  Posição já atacada!\n");
            break;
    }
}

void jogar(Tabuleiro *t) {
    int linha, coluna;

    while (1) {
        exibeTabuleiro(t);
        printf("\nDigite as coordenadas para atacar (linha coluna) ou -1 para sair: ");
        if (scanf("%d", &linha) != 1 || linha == -1) break;
        if (scanf("%d", &coluna) != 1) break;
        ataque(t, linha, coluna);
        printf("🎯 Acertos: %d | 💦 Erros: %d\n", t->acertos, t->erros);
    }
}

int main() {
    Tabuleiro t;
    inicializaTabuleiro(&t);

    if (!posicionaNavioHorizontal(&t, 2, 4))
        printf("Erro ao posicionar navio horizontal.\n");

    if (!posicionaNavioVertical(&t, 5, 7))
        printf("Erro ao posicionar navio vertical.\n");

    jogar(&t);
    printf("🏁 Fim do jogo. Total de acertos: %d | erros: %d\n", t.acertos, t.erros);

    return 0;
}
