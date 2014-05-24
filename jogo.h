#ifndef JOGO_H
#define JOGO_H

class Jogo {
    public:
        ~Jogo();
        Estado* estadoAtual;
        void inicializar(Estado* estadoInicial);
        void alterarEstado(Estado* estado);
        void atualizar();
};

#endif
