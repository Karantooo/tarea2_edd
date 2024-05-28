#include <iostream>
#include <math.h>

class HashingMethod {
    private:

    float A = (sqrt(5) - 1) / 2;

    public:
    // Funciones Hash para determinar a que bucket va el dato
    int hashf1(int k, int n) {
        return k % n;
    }
    int hashf2(int k, int n) {
        float a = (float)k*A;
        a -= (int)a;
        return n*a;
    }

    int acumulacion_polinomial(std::string word, int constante){
        int resultado = 0;
        for (auto it = word.rbegin(); it != word.rend(); it++){
            resultado*= constante;
            resultado += *it;
        }
        return resultado;
    }
    // Funciones de los distintos metodos de Hashing

    int linearProbing(int k, int n, int i) {
        return (hashf1(k, n) + i) % n;
    }

    int quadraticProbing(int k, int n, int i) {
        return (hashf1(k, n) + i + 2 * i * i) % n;
    }

    int doubleHashing(int k, int n, int i) {
        return (hashf1(k, n) + i * (hashf2(k, n) + 1)) % n;
    }
};