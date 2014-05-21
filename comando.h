#ifndef COMANDO_H
#define COMANDO_H

class Comando {
    public:
        virtual ~Comando() {}
        virtual void executar() = 0;
};

#endif
