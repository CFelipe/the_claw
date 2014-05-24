#ifndef ESTADOJOGO_H
#define ESTADOJOGO_H

class EstadoJogo {
    public:
        ~EstadoJogo();
        void entrar();
        void atualizar();
        void sair();

    private:
        bool pausado;
};

#endif
