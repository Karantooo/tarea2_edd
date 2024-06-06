#pragma once
#include <string>
#include "SeguidoresUniversidades.h"

/**
 * @brief Enum para definir la key de nuestro map
 * 
 */
enum opcion_de_clave{
    se_usa_user_id,
    se_usa_user_name
};

/**
 * @brief Clase abstracta que sirve para definir el adt map
 * Esta clase esta pensada para que el resto de implementaciones hereden de esta y
 * poder utilizar indistintamente ambas clases despues de manera polimorfica.
 */
class MapADT{
    protected:
        opcion_de_clave opcion;

    public:
     /**
     * @brief Construye un nuevo mapADT
     * 
     * @param opcion eleccion de key que se utilizara en el map. 
     */
        MapADT(opcion_de_clave opcion) : opcion(opcion){

        }

        /**
         * @brief Metodo para ingresar usuarios al map
         * Con el metodo se agregan usuarios al map.
         * Utilizando la opcion del constructor se realiza el put ya sea con el user_name o user_id
         * @param usuarios 
         */
        virtual void put(SeguidoresUniversidades usuarios) = 0;
        //metodos para user ID

        /**
         * @brief Obtiene metodo a partir de una key long long (para user_id)
         * 
         * @param key el user_id del seguidor a buscar
         * @return SeguidoresUniversidades El seguidor que se esta buscando.
         */
        virtual SeguidoresUniversidades get(long long key) = 0;

        /**
         * @brief Elimina un valor del map a partir de una key long long (para user_id)
         * 
         * @param key el user_id del seguidor a eliminar
         * @return SeguidoresUniversidades El seguidor que se esta buscando.
         */
        virtual SeguidoresUniversidades remove(long long key) = 0;

        //metodos para user name
        /**
         * @brief Obtiene metodo a partir de una key string (para user_name)
         * 
         * @param key el user_name del seguidor a buscar
         * @return SeguidoresUniversidades El seguidor que se esta buscando.
         */

        virtual SeguidoresUniversidades get(std::string key) = 0;
        /**
         * @brief Elimina un valor del map a partir de una key string (para user_name)
         * 
         * @param key el user_name del seguidor a eliminar
         * @return SeguidoresUniversidades El seguidor que se esta buscando.
         */

        virtual SeguidoresUniversidades remove(std::string key) = 0;

        /**
         * @brief retorna la cantidad de elementos en el map
         * 
         * @return int cantidad de elementos
         */
        virtual int size() = 0;

        /**
         * @brief Devuelve si esta vacio o no
         * 
         * @return true si esta vacio
         * @return false si no esta vacio
         */
        virtual bool empty() = 0;

        /**
         * @brief Destruye el mapADT
         * 
         */
        ~MapADT(){

        }
};