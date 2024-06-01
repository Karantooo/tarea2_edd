#include <vector>
#include <iostream>
#include <cmath>
#include "MapADT.h"
#include "interesting_prime_numbers.h"

enum Manejo_de_Colisiones {
    use_linear_probing,
    use_quadratic_probing,
    use_double_hashing,
};

// Métodos de hashing auxiliares
int h1(long long k, int n) {
    return k % n;
}

int h2(long long k, int n) {
    float A = (std::sqrt(5) - 1) / 2;
    float a = static_cast<float>(k) * A;
    a -= static_cast<int>(a);
    return static_cast<int>(n * a);
}

// Funciones de manejo de colisiones
int linear_probing(long long k, int n, int i) {
    return (h1(k, n) + i) % n;
}

int quadratic_probing(long long k, int n, int i) {
    return (h1(k, n) + i + 2 * i * i) % n;
}

int double_hashing(long long k, int n, int i) {
    return (h1(k, n) + i * (h2(k, n) + 1)) % n;
}

class MapCerrado : public MapADT {
private:
    int seguidores_totales;
    std::vector<long long>::iterator siguiente_tam_contenedor;
    std::vector<SeguidoresUniversidades> contenedor_seguidores;
    std::vector<bool> ocupado;
    Manejo_de_Colisiones metodo_colisiones;

public:
    MapCerrado(opcion_de_clave opcion, Manejo_de_Colisiones metodo) : MapADT(opcion), metodo_colisiones(metodo) {
        siguiente_tam_contenedor = numeros_primos_interesantes.begin();
        contenedor_seguidores.resize(*siguiente_tam_contenedor);
        ocupado.resize(contenedor_seguidores.size(), false);
        siguiente_tam_contenedor++;
        seguidores_totales = 0;
    }

    void put(SeguidoresUniversidades usuarios) override {
        if (opcion == se_usa_user_id)
            _put_with_longlong(usuarios);
        else
            _put_with_string(usuarios);

        _verificar_cantidad_ocupada();
    }

    SeguidoresUniversidades get(long long key) override {
        int index = _hashf1(key);
        int i = 0;
        while (ocupado[index] && i < contenedor_seguidores.size()) {
            if (contenedor_seguidores[index].user_id == key) {
                return contenedor_seguidores[index];
            }
            i++;
            index = _manejo_colisiones(key, i);
        }
        SeguidoresUniversidades nullse;
        nullse.user_name = "Invalid user name";
        return nullse;
    }

    SeguidoresUniversidades remove(long long key) override {
        int index = _hashf1(key);
        int i = 0;
        while (ocupado[index] && i < contenedor_seguidores.size()) {
            if (contenedor_seguidores[index].user_id == key) {
                SeguidoresUniversidades elemento_buscado = contenedor_seguidores[index];
                ocupado[index] = false;
                seguidores_totales--;
                return elemento_buscado;
            }
            i++;
            index = _manejo_colisiones(key, i);
        }
        SeguidoresUniversidades nullse;
        nullse.user_name = "Invalid user name";
        return nullse;
    }

    SeguidoresUniversidades get(std::string key) override {
        int index = _hashf1(_acumulacion_polinomial(key, 33));
        int i = 0;
        while (ocupado[index] && i < contenedor_seguidores.size()) {
            if (contenedor_seguidores[index].user_name == key) {
                return contenedor_seguidores[index];
            }
            i++;
            index = _manejo_colisiones(_acumulacion_polinomial(key, 33), i);
        }
        SeguidoresUniversidades nullse;
        nullse.user_name = "Invalid user name";
        return nullse;
    }

    SeguidoresUniversidades remove(std::string key) override {
        int index = _hashf1(_acumulacion_polinomial(key, 33));
        int i = 0;
        while (ocupado[index] && i < contenedor_seguidores.size()) {
            if (contenedor_seguidores[index].user_name == key) {
                SeguidoresUniversidades elemento_buscado = contenedor_seguidores[index];
                ocupado[index] = false;
                seguidores_totales--;
                return elemento_buscado;
            }
            i++;
            index = _manejo_colisiones(_acumulacion_polinomial(key, 33), i);
        }
        SeguidoresUniversidades nullse;
        nullse.user_name = "Invalid user name";
        return nullse;
    }

    int size() override {
        return seguidores_totales;
    }

    bool empty() override {
        return (size() == 0);
    }

    ~MapCerrado() {
        // No es necesario eliminar explícitamente los vectores porque no son punteros
    }

private:
    void _put_with_string(SeguidoresUniversidades usuarios) {
        int index = _hashf1(_acumulacion_polinomial(usuarios.user_name, 33));
        int i = 0;
        while (ocupado[index]) {
            i++;
            index = _manejo_colisiones(_acumulacion_polinomial(usuarios.user_name, 33), i);
        }
        contenedor_seguidores[index] = usuarios;
        ocupado[index] = true;
        seguidores_totales++;
    }

    void _put_with_longlong(SeguidoresUniversidades usuarios) {
        int index = _hashf1(usuarios.user_id);
        int i = 0;
        while (ocupado[index]) {
            i++;
            index = _manejo_colisiones(usuarios.user_id, i);
        }
        contenedor_seguidores[index] = usuarios;
        ocupado[index] = true;
        seguidores_totales++;
    }

    float _porcentaje_llenado() {
        return float(seguidores_totales) / float(contenedor_seguidores.size());
    }

    void _verificar_cantidad_ocupada() {
        if (_porcentaje_llenado() < 0.9)
            return;

        std::vector<SeguidoresUniversidades> viejo_contenedor_seguidores = contenedor_seguidores;
        std::vector<bool> viejo_ocupado = ocupado;
        contenedor_seguidores.resize(*siguiente_tam_contenedor);
        ocupado.resize(contenedor_seguidores.size(), false);
        siguiente_tam_contenedor++;
        seguidores_totales = 0;

        for (size_t i = 0; i < viejo_contenedor_seguidores.size(); i++) {
            if (viejo_ocupado[i]) {
                put(viejo_contenedor_seguidores[i]);
            }
        }
    }

    int _hashf1(long long k) {
        return h1(k, contenedor_seguidores.size());
    }

    int _hashf1(int k) {
        return k % contenedor_seguidores.size();
    }

    int _manejo_colisiones(long long k, int i) {
        switch (metodo_colisiones) {
            case use_linear_probing:
                return linear_probing(k, contenedor_seguidores.size(), i);
            case use_quadratic_probing:
                return quadratic_probing(k, contenedor_seguidores.size(), i);
            case use_double_hashing:
                return double_hashing(k, contenedor_seguidores.size(), i);
            default:
                return linear_probing(k, contenedor_seguidores.size(), i);
        }
    };

    int _acumulacion_polinomial(std::string word, int constante) {
        int resultado = 0;
        for (auto it = word.rbegin(); it != word.rend(); ++it) {
            resultado *= constante;
            resultado += *it;
        }
        return resultado;
    }
};
