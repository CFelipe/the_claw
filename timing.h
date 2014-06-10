#ifndef TIMING_H
#define TIMING_H

class LoopTimer {
    public:
        LoopTimer(float min, float max, float dur);
        void atualizar(float dt);
        float valor;
    private:
        float min, max, dur, elapsed;
};

#endif
