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

/**
 * @brief Esta función calcula el hash primario de una clave larga.
 *
 * @param k La clave a ser hasheada.
 * @param n El tamaño de la tabla de hash.
 * @return El índice de hash calculado.
 */
long long hashf1(unsigned long long k, unsigned long long n) {
    return k % n;
}

/**
 * @brief Esta función calcula el hash secundario usando dos primos.
 *
 * @param k La clave a ser hasheada.
 * @param n El tamaño de la tabla de hash.
 * @return El índice de hash calculado.
 */
long long hashf2(long long k, int n) {
    return 1 + (k % (n - 1));
}

/**
 * @brief Esta función implementa la técnica de lineal probing para manejo de colisiones.
 *
 * @param k La clave a ser hasheada.
 * @param n El tamaño de la tabla de hash.
 * @param i El número de intentos de resolución de colisión.
 * @return El índice de hash calculado.
 */
int linear_probing(long long k, int n, int i) {
    return (hashf1(k, n) + i) % n;
}

/**
 * @brief Esta función implementa la técnica de quadratic probing para manejo de colisiones.
 *
 * @param k La clave a ser hasheada.
 * @param n El tamaño de la tabla de hash.
 * @param i El número de intentos de resolución de colisión.
 * @return El índice de hash calculado.
 */
unsigned long long quadratic_probing(long long k, unsigned long long n, int i) {
    return (hashf1(k, n) + i*i) % n;
}   

/**
 * @brief Esta función implementa la técnica de double hashing para manejo de colisiones.
 *
 * @param k La clave a ser hasheada.
 * @param n El tamaño de la tabla de hash.
 * @param i El número de intentos de resolución de colisión.
 * @return El índice de hash calculado.
 */
int double_hashing(long long k, int n, int i) {
    return (hashf1(k, n) + i * hashf2(k, n)) % n;
}

/**
 * @brief Clase que implementa una tabla hash con manejo de colisiones cerradas.
 */
class MapCerrado : public MapADT {
private:
    int seguidores_totales;
    std::vector<long long>::iterator siguiente_tam_contenedor;
    std::vector<SeguidoresUniversidades> contenedor_seguidores;
    std::vector<bool> ocupado;
    Manejo_de_Colisiones metodo_colisiones;

public:
    /**
     * @brief Constructor de la clase MapCerrado.
     *
     * @param opcion Define si se usa user_id o user_name como clave.
     * @param metodo El método de manejo de colisiones a utilizar.
     */
    MapCerrado(opcion_de_clave opcion, Manejo_de_Colisiones metodo) : MapADT(opcion), metodo_colisiones(metodo) {
        siguiente_tam_contenedor = numeros_primos_interesantes.begin();
        contenedor_seguidores.resize(*siguiente_tam_contenedor);
        ocupado.resize(contenedor_seguidores.size(), false);
        siguiente_tam_contenedor++;
        seguidores_totales = 0;
    }

    /**
     * @brief Inserta un nuevo elemento en la tabla hash.
     *
     * @param usuarios El elemento a ser insertado.
     */
    void put(SeguidoresUniversidades usuarios) override {
        if (opcion == se_usa_user_id) {
            _put_with_longlong(usuarios);
        } 
        else {
            _put_with_string(usuarios);
        }
        _verificar_cantidad_ocupada();
    }

    /**
     * @brief Obtiene un elemento de la tabla hash utilizando una clave larga.
     *
     * @param key La clave del elemento a obtener.
     * @return El elemento obtenido.
     */
    SeguidoresUniversidades get(long long key) override {
        int index = hashf1(key, contenedor_seguidores.size());
        int i = 0;
        while (ocupado[index] && i < contenedor_seguidores.size()) {
            if (contenedor_seguidores[index].user_id == key) {
                return contenedor_seguidores[index];
            }
            i++;
            index = _manejo_colisiones(key, i);
        }
        SeguidoresUniversidades nullse;
        nullse.user_name = "Invalid user ID";
        return nullse;
    }

    /**
     * @brief Elimina un elemento de la tabla hash utilizando una clave larga.
     *
     * @param key La clave del elemento a eliminar.
     * @return El elemento eliminado.
     */
    SeguidoresUniversidades remove(long long key) override {
        int index = hashf1(key, contenedor_seguidores.size());
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
        nullse.user_name = "Invalid user ID";
        return nullse;
    }

    /**
     * @brief Obtiene un elemento de la tabla hash utilizando una clave de texto.
     *
     * @param key La clave del elemento a obtener.
     * @return El elemento obtenido.
     */
    SeguidoresUniversidades get(std::string key) override {
        int index = hashf1(_acumulacion_polinomial(key, 33), contenedor_seguidores.size());
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

    /**
     * @brief Elimina un elemento de la tabla hash utilizando una clave de texto.
     *
     * @param key La clave del elemento a eliminar.
     * @return El elemento eliminado.
     */
    SeguidoresUniversidades remove(std::string key) override {
        int index = hashf1(_acumulacion_polinomial(key, 33), contenedor_seguidores.size());
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

    /**
     * @brief Devuelve el número de elementos en la tabla hash.
     *
     * @return El número de elementos.
     */
    int size() override {
        return seguidores_totales;
    }

    /**
     * @brief Verifica si la tabla hash está vacía.
     *
     * @return Verdadero si está vacía, falso en caso contrario.
     */
    bool empty() override {
        return (size() == 0);
    }

    ~MapCerrado() {}

private:
    /**
     * @brief Inserta un elemento utilizando una clave de texto.
     *
     * @param usuarios El elemento a ser insertado.
     */
    void _put_with_string(SeguidoresUniversidades usuarios) {
        // std::cout << contenedor_seguidores.size() << std::endl;
        unsigned long long index = hashf1(_acumulacion_polinomial(usuarios.user_name, 33), contenedor_seguidores.size());
        int i = 0;
        while (ocupado[index]) {
            i++;
            index = _manejo_colisiones(_acumulacion_polinomial(usuarios.user_name, 33), i);
        }
        contenedor_seguidores[index] = usuarios;
        ocupado[index] = true;
        seguidores_totales++;
    }

    /**
     * @brief Inserta un elemento utilizando una clave larga.
     *
     * @param usuarios El elemento a ser insertado.
     */
    void _put_with_longlong(SeguidoresUniversidades usuarios) {
        int index = hashf1(usuarios.user_id, contenedor_seguidores.size());
        int i = 0;
        while (ocupado[index]) {
            i++;
            index = _manejo_colisiones(usuarios.user_id, i);
        }
        contenedor_seguidores[index] = usuarios;
        ocupado[index] = true;
        seguidores_totales++;
    }

    /**
     * @brief Verifica la cantidad de espacios ocupados en la tabla hash y realiza rehashing si es necesario.
     */
    void _verificar_cantidad_ocupada() {
        if (seguidores_totales < contenedor_seguidores.size() * 0.7) return;
        std::vector<SeguidoresUniversidades> contenedor_viejo = contenedor_seguidores;
        std::vector<bool> ocupado_viejo = ocupado;

        contenedor_seguidores.clear();
        ocupado.clear();

        contenedor_seguidores.resize(*siguiente_tam_contenedor);
        ocupado.resize(contenedor_seguidores.size(), false);
        siguiente_tam_contenedor++;

        seguidores_totales = 0;
        for (int i = 0; i < contenedor_viejo.size(); ++i) {
            if (ocupado_viejo[i]) {
                put(contenedor_viejo[i]);
            }
        }
    }

    /**
     * @brief Calcula la acumulación polinomial de una clave de texto.
     *
     * @param k La clave de texto a ser hasheada.
     * @param x El número base para la acumulación.
     * @return El valor acumulado.
     */
    unsigned long long _acumulacion_polinomial(std::string& word, int constante){
        unsigned long long resultado = 0; 
        for (auto it = word.rbegin(); it != word.rend(); it++){
            resultado*= constante;
            resultado += *it;
           }
        return resultado;
    }

    /**
     * @brief Maneja colisiones utilizando el método de manejo de colisiones especificado.
     *
     * @param k La clave a ser hasheada.
     * @param i El número de intentos de resolución de colisión.
     * @return El índice calculado.
     */
    unsigned long long _manejo_colisiones(long long k, int i) {
        switch (metodo_colisiones) {
            case use_linear_probing:
                return linear_probing(k, contenedor_seguidores.size(), i);
            case use_quadratic_probing:
                return quadratic_probing(k, contenedor_seguidores.size(), i);
            case use_double_hashing:
                return double_hashing(k, contenedor_seguidores.size(), i);
            default:
                return -1;
        }
    }
};