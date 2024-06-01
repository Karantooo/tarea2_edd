#pragma once
#include <vector>
#include <list>
#include <iostream>
#include "MapADT.h"
#include "interesting_prime_numbers.h"


/**
 * @brief Implementacion de MapADT utilizando hashing abierto
 * 
 */
class MapAbierto : public MapADT{
    private:
        int seguidores_totales;
        std::vector<long long>::iterator siguiente_tam_contenedor;
        std::vector<std::list<SeguidoresUniversidades>> contenedor_seguidores;
    public:
        /**
         * @brief Construye un nuevo MapAbierto
         * 
         * @param opcion campo que se utilizara como key
         */
        MapAbierto(opcion_de_clave opcion) : MapADT(opcion){
            siguiente_tam_contenedor = numeros_primos_interesantes.begin();
            contenedor_seguidores.resize(*siguiente_tam_contenedor);
            siguiente_tam_contenedor++;
            seguidores_totales = 0;
        }

        /**
         * @brief implementacion de put de mapADT
         * Dependiendo de cual sea la key se llama a una funcion distinta para añadirla al map
         * Despues se verifica si se nececita aumentar el espacio 
         * 
         * @param usuarios usuario a añadir
         */
        void put(SeguidoresUniversidades usuarios) override {
            if (opcion == se_usa_user_id)
                _put_with_longlong(usuarios);
            else
                _put_with_string(usuarios);
            
            _verificar_cantidad_ocupada();

        }
        
        /**
         * @brief Metodo para obtener un usuario a partir de su user_id
         * En caso de que algo salga mal se va a devolver un usuario con el nombre Invalid user name
         * @param key user_id del usuario a buscar
         * @return SeguidoresUniversidades seguidor buscado
         * @return En caso de que algo salga mal se va a devolver un usuario con el nombre Invalid user name
         */
        SeguidoresUniversidades get(long long key) override {
            SeguidoresUniversidades nullse;
            nullse.user_name = "Invalid user name";
            if (opcion == se_usa_user_name)
                return nullse;
            int index = _hashf1(key);
            std::list<SeguidoresUniversidades> lista = contenedor_seguidores[index];
            for (auto elem : lista){
                if (elem.user_id == key)
                    return elem;
            }

            return nullse;
        }

        /**
         * @brief Implementacion clase para eliminar un elemento del map a partir de user_id
         * En caso de que algo salga mal se va a devolver un usuario con el nombre Invalid user name
         * @param key user_id del usuario a eliminiar
         * @return SeguidoresUniversidades el usuario eliminado.
         * @return En caso de que algo salga mal se va a devolver un usuario con el nombre Invalid user name
         */
        SeguidoresUniversidades remove(long long key) override {
            SeguidoresUniversidades nullse;
            nullse.user_name = "Invalid user name";
            if (opcion == se_usa_user_name)
                return nullse;
            int index = _hashf1(key);
            std::list<SeguidoresUniversidades>::iterator it = (contenedor_seguidores)[index].begin();
            for (auto it = (contenedor_seguidores)[index].begin(); it != (contenedor_seguidores)[index].end(); it++){
                if(it->user_id == key){
                    SeguidoresUniversidades elemento_buscado = *it;
                    (contenedor_seguidores)[index].erase(it);
                    seguidores_totales--;
                    return elemento_buscado;
                }

            }

            return nullse;


        }

        /**
         * @brief Metodo para obtener un usuario a partir de su user_name
         * En caso de que algo salga mal se va a devolver un usuario con el nombre Invalid user name
         * @param key user_name del usuario a buscar
         * @return SeguidoresUniversidades seguidor buscado
         * @return En caso de que algo salga mal se va a devolver un usuario con el nombre Invalid user name
         */
        SeguidoresUniversidades get(std::string key) override {
            SeguidoresUniversidades nullse;
            nullse.user_name = "Invalid user name";
            if (opcion == se_usa_user_id)
                return nullse;
            int index = _hashf1(_acumulacion_polinomial(key, 33));
            std::list<SeguidoresUniversidades> lista = contenedor_seguidores[index];
            for (auto elem : lista){
                if (elem.user_name == key)
                    return elem;
            }

            return nullse;


        }
        
        /**
         * @brief Implementacion clase para eliminar un elemento del map a partir de user_name
         * 
         * @param key user_name del usuario a eliminiar
         * @return SeguidoresUniversidades el usuario eliminado.
         * @return En caso de que algo salga mal se va a devolver un usuario con el nombre Invalid user name
         */
        SeguidoresUniversidades remove(std::string key) override {
            SeguidoresUniversidades nullse;
            nullse.user_name = "Invalid user name";
            if (opcion == se_usa_user_id)
                return nullse;
            int index = _hashf1(_acumulacion_polinomial(key,33));
            std::list<SeguidoresUniversidades>::iterator it = (contenedor_seguidores)[index].begin();
            for (auto it = (contenedor_seguidores)[index].begin(); it != (contenedor_seguidores)[index].end(); it++){
                if(it->user_name == key){
                    SeguidoresUniversidades elemento_buscado = *it;
                    (contenedor_seguidores)[index].erase(it);
                    seguidores_totales--;
                    return elemento_buscado;
                }

            }

            return nullse;

        }

        /**
         * @brief implementacion de size, para obtener la cantidad de elementos del map
         * 
         * @return int cantidad de elementos
         */
        int size() override {
            return seguidores_totales;
        }

        /**
         * @brief se verifica si el map esta vacio o no
         * 
         * @return true esta vacio
         * @return false no esta vacio
         */
        bool empty() override {
            return (size() == 0) ? true :  false;
        };

        ~MapAbierto(){

        }
    private:
        //funciones privadas


        /**
         * @brief funcion para insertar un elemento cuando se esta en modo user_id
         * 
         * @param usuarios usuario a insertar
         */
        void _put_with_longlong(SeguidoresUniversidades usuarios){
            int index = _hashf1(usuarios.user_id);

            (contenedor_seguidores)[index].push_back(usuarios);

            seguidores_totales++;
        }
        
        /**
         * @brief funcion para insertar un elemento cuando se esta en modo user_name
         * 
         * @param usuarios usuario a insertar
         */
        void _put_with_string(SeguidoresUniversidades usuarios){
            int index =  _hashf1(_acumulacion_polinomial(usuarios.user_name, 33));

            (contenedor_seguidores)[index].push_back(usuarios);

            seguidores_totales++;
        }


        /**
         * @brief Devuelve el porcentaje de llenado del map
         * Se define como porcentaje de llenado la division entre los seguidores insertados en el map
         * y el tamanio actual del contenedor
         * @return float porcentaje de llenado
         */
        float _porcentaje_llenado(){
            return float(seguidores_totales) / float(contenedor_seguidores.size());
        }

        /**
         * @brief esta funcion aniade espacios al map en caso de que el porcentaje de llenado sea muy alto (0.9)
         * Si el map esta proximo a llenarse se rellena de nuevo el map.
         * Posterior a esto se procede a hacer un rehash
         */
        void _verificar_cantidad_ocupada(){
            if (_porcentaje_llenado() < 0.9)
                return;
            std::vector<std::list<SeguidoresUniversidades>>  viejo_contenedor_seguidores = this->contenedor_seguidores;
            contenedor_seguidores.clear();
            this->contenedor_seguidores.resize(*siguiente_tam_contenedor);
            siguiente_tam_contenedor++;
            seguidores_totales = 0;
            //hacemos rehashing
            for (auto lista : viejo_contenedor_seguidores){
                while (!lista.empty()){
                    SeguidoresUniversidades elemento = lista.back();
                    lista.pop_back();
                    put(elemento);
                }
            }



        }

        /**
         * @brief funcion para generar el hash correspondiente dependiendo de un valor numerico
         * 
         * @param k valor numerico a hashear
         * @return int valor ya hasheado
         */
        int _hashf1(int k) {
            return k % (contenedor_seguidores).size();
        }

        /**
         * @brief funcion para hacer el hashing inicial de un string
         * Posteriormente al hashing se tiene que pasar el resultado por otra funcion como hashf1.
         * 
         * Utilizamos acumulacion polinomial para hashear el string
         * 
         * Esto es la sumatoria de xn * a^n
         * Con xn el caracter xn de la palabra y a la constante a utilizar
         * 
         * @param word palabra a hashear
         * @param constante la constante que se utilzira para hacer el hashing
         * @return int 
         */
        int _acumulacion_polinomial(std::string word, int constante){
            int resultado = 0;
            for (auto it = word.rbegin(); it != word.rend(); it++){
                resultado*= constante;
                resultado += *it;
            }
            return resultado;
        }

};