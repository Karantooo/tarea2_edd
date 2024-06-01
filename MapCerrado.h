#include <vector>
#include <iostream>
#include <cmath>
#include "MapADT.h"
#include "interesting_prime_numbers.h"

/// Enum para identificar el tipo de manejo de colisiones
enum Manejo_de_Colisiones {
    use_linear_probing,  
    use_quadratic_probing, 
    use_double_hashing,
};

/// Métodos de hashing auxiliares
/**
 * @brief Funcion hash para calcular la posicion de un dato
 * @param k Clave a hashear
 * @param n Tamaño de la tabla de hash
 * @return Valor hash
 */
long long hashf1(long long k, int n) {
    return k % n;
}

/**
 * @brief Segunda función de hash para el double hashing
 * @param k Clave a hashear
 * @param n Tamaño de la tabla de hash
 * @return Valor hash
 */
long long hashf2(long long k, int n) {
    float A = (std::sqrt(5) - 1) / 2;
    float a = static_cast<float>(k) * A;
    a -= static_cast<int>(a);
    return static_cast<int>(n * a);
}

/// Funciones de manejo de colisiones
/**
 * @brief Función de sondeo lineal
 * @param k Clave a hashear
 * @param n Tamaño de la tabla de hash
 * @param i Número de sondeo
 * @return Posicion después de la colisión
 */
int linear_probing(long long k, int n, int i) {
    return (hashf1(k, n) + i) % n;
}

/**
 * @brief Función de sondeo cuadrático
 * @param k Clave a hashear
 * @param n Tamaño de la tabla de hash
 * @param i Número de sondeo
 * @return Posicion después de la colisión
 */
int quadratic_probing(long long k, int n, int i) {
    return (hashf1(k, n) + i + 2 * i * i) % n;
}

/**
 * @brief Función de doble hash
 * @param k Clave a hashear
 * @param n Tamaño de la tabla de hash
 * @param i Número de sondeo
 * @return Posicion después de la colisión
 */
int double_hashing(long long k, int n, int i) {
    return (hashf1(k, n) + i * (hashf2(k, n) + 1)) % n;
}

/**
 * @brief Implementación de la clase MapCerrado
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
     * @brief Constructor para MapCerrado
     * @param opcion Opción para el tipo de clave
     * @param metodo Método de manejo de colisiones
     */
    MapCerrado(opcion_de_clave opcion, Manejo_de_Colisiones metodo) : MapADT(opcion), metodo_colisiones(metodo) {
        siguiente_tam_contenedor = numeros_primos_interesantes.begin();
        contenedor_seguidores.resize(*siguiente_tam_contenedor);
        ocupado.resize(contenedor_seguidores.size(), false);
        siguiente_tam_contenedor++;
        seguidores_totales = 0;
    }

    /**
     * @brief Inserta un usuario en el mapa
     * @param usuarios Usuario a insertar
     */
    void put(SeguidoresUniversidades usuarios) override {
        if (opcion == se_usa_user_id)
            _put_with_longlong(usuarios);
        else
            _put_with_string(usuarios);

        _verificar_cantidad_ocupada();
    }

    /**
     * @brief Obtiene un usuario segun su user id
     * @param key user id a buscar
     * @return Usuario asociado con la clave
     */
    SeguidoresUniversidades get(long long key) override {
        int index = hashf1(key,size());
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
     * @brief Elimina uun usuario segun su user id
     * @param key Clave a buscar
     * @return Usuario asociado con la clave
     */
    SeguidoresUniversidades remove(long long key) override {
        int index = hashf1(key,size());
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
     * @brief Recupera un usuario del mapa segun su user name
     * @param key Clave a buscar
     * @return Usuario asociado con la clave
     */
    SeguidoresUniversidades get(std::string key) override {
        int index = hashf1(_acumulacion_polinomial(key, 33),size());
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
     * @brief Elimina un usuario del mapa segun su user name
     * @param key user name a buscar
     * @return SeguidoresUniversidades asociado
     */
    SeguidoresUniversidades remove(std::string key) override {
        int index = hashf1(_acumulacion_polinomial(key, 33),size());
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
     * @brief Obtiene el número de elementos en el mapa
     * @return Número de elementos
     */
    int size() override {
        return seguidores_totales;
    }

    /**
     * @brief Verifica si el mapa está vacío
     * @return True si está vacío, false en caso contrario
     */
    bool empty() override {
        return (size() == 0);
    }

    /**
     * @brief Destructor para MapCerrado
     */
    ~MapCerrado() {
    }

private:
    /**
     * @brief Inserta un usuario en el mapa segun su user name
     * @param usuarios Usuario a insertar
     */
    void _put_with_string(SeguidoresUniversidades usuarios) {
        int index = hashf1(_acumulacion_polinomial(usuarios.user_name, 33),size());
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
     * @brief Maneja la insercion de un usuario segun su user id
     * @param usuarios Usuario a insertar
     */
    void _put_with_longlong(SeguidoresUniversidades usuarios) {
        int index = hashf1(usuarios.user_id,size());
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
     * @brief Calcula el porcentaje de llenado del mapa
     * @return Porcentaje de llenado
     */
    float _porcentaje_llenado() {
        return float(seguidores_totales) / float(contenedor_seguidores.size());
    }

    /**
     * @brief Verifica la cantidad de espacio ocupado y hace Rehashing si es necesario
     */
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

    /**
     * @brief Maneja colisiones usando el método seleccionado
     * @param k Clave a hashear
     * @param i Número de sondeo
     * @return Nuevo valor hash después de la colisión
     */
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

    /**
     * @brief Función de acumulación polinomial para los user name
     * @param word String a hashear
     * @param constante Constante para la acumulación polinomial
     * @return Valor acumulado
     */
    int _acumulacion_polinomial(std::string word, int constante) {
        int resultado = 0;
        for (auto it = word.rbegin(); it != word.rend(); ++it) {
            resultado *= constante;
            resultado += *it;
        }
        return resultado;
    }
};
