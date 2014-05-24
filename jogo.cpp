#include "jogo.h"

Jogo::~Jogo() {
    estadoAtual->sair();
}

void Jogo::inicializar(Estado* estadoInicial) {
    //
}

void Jogo::alterarEstado(Estado* estado) {
    estadoAtual->sair();
    estadoAtual = estado;
    estado->entrar();
}

void Jogo::atualizar() {
    estadoAtual->atualizar();
}
