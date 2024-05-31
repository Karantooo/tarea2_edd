#include <vector>
#include <iostream>
#include "MapADT.h"
#include "HashingMethod.h"
#include "interesting_prime_numbers.h"

class MapCerrado : public MapADT {
private:
    int seguidores_totales;
    std::vector<long long>::iterator siguiente_tam_contenedor;
    std::vector<SeguidoresUniversidades> *contenedor_seguidores;
    std::vector<bool> *ocupado; // Vector para marcar si la posición está ocupada
    HashingMethod hashingMethod;

public:
    MapCerrado(opcion_de_clave opcion) : MapADT(opcion) {
        siguiente_tam_contenedor = numeros_primos_interesantes.begin();
        contenedor_seguidores = new std::vector<SeguidoresUniversidades>(*siguiente_tam_contenedor);
        ocupado = new std::vector<bool>(contenedor_seguidores->size(), false);
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
        while ((*ocupado)[index] && i < contenedor_seguidores->size()) {
            if ((*contenedor_seguidores)[index].user_id == key) {
                return (*contenedor_seguidores)[index];
            }
            i++;
            index = _linear_probing(key, i);
        }
        SeguidoresUniversidades nullse;
        nullse.user_name = "Invalid user name";
        return nullse;
    }

    SeguidoresUniversidades remove(long long key) override {
        int index = _hashf1(key);
        int i = 0;
        while ((*ocupado)[index] && i < contenedor_seguidores->size()) {
            if ((*contenedor_seguidores)[index].user_id == key) {
                SeguidoresUniversidades elemento_buscado = (*contenedor_seguidores)[index];
                (*ocupado)[index] = false;
                seguidores_totales--;
                return elemento_buscado;
            }
            i++;
            index = _linear_probing(key, i);
        }
        SeguidoresUniversidades nullse;
        nullse.user_name = "Invalid user name";
        return nullse;
    }

    SeguidoresUniversidades& get(std::string key) override {
        // Implementación para obtener por nombre de usuario
    }

    SeguidoresUniversidades& remove(std::string key) override {
        // Implementación para eliminar por nombre de usuario
    }

    int size() override {
        return seguidores_totales;
    }

    bool empty() override {
        return (size() == 0);
    }

    ~MapCerrado() {
        delete contenedor_seguidores;
        delete ocupado;
    }

private:
    void _put_with_string(SeguidoresUniversidades usuarios) {
        // Falta implementar
    }

    void _put_with_longlong(SeguidoresUniversidades usuarios) {
        int index = _hashf1(usuarios.user_id);
        int i = 0;
        while ((*ocupado)[index]) {
            i++;
            index = _linear_probing(usuarios.user_id, i);
        }
        (*contenedor_seguidores)[index] = usuarios;
        (*ocupado)[index] = true;
        seguidores_totales++;
    }

    float _porcentaje_llenado() {
        return float(seguidores_totales) / float(contenedor_seguidores->size());
    }

    void _verificar_cantidad_ocupada() {
        if (_porcentaje_llenado() < 0.9)
            return;

        std::vector<SeguidoresUniversidades> *viejo_contenedor_seguidores = this->contenedor_seguidores;
        std::vector<bool> *viejo_ocupado = this->ocupado;
        this->contenedor_seguidores = new std::vector<SeguidoresUniversidades>(*siguiente_tam_contenedor);
        this->ocupado = new std::vector<bool>(contenedor_seguidores->size(), false);
        siguiente_tam_contenedor++;
        seguidores_totales = 0;

        for (size_t i = 0; i < viejo_contenedor_seguidores->size(); i++) {
            if ((*viejo_ocupado)[i]) {
                put((*viejo_contenedor_seguidores)[i]);
            }
        }

        delete viejo_contenedor_seguidores;
        delete viejo_ocupado;
    }

    int _hashf1(long long k) {
        return hashingMethod.hashf1(k, contenedor_seguidores->size());
    }

    int _linear_probing(long long k, int i) {
        return hashingMethod.linearProbing(k, contenedor_seguidores->size(), i);
    }
};
