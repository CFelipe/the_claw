#ifndef ESTADO_H
#define ESTADO_H

class Estado {
    public:
        virtual ~Estado() {}
        virtual void entrar() = 0;
        virtual void atualizar() = 0;
        virtual void sair() = 0;
};

#endif
