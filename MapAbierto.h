#pragma once
#include <vector>
#include <list>
#include <iostream>
#include "MapADT.h"
#include "interesting_prime_numbers.h"

class MapAbierto : public MapADT{
    private:
        int seguidores_totales;
        std::vector<long long>::iterator siguiente_tam_contenedor;
        std::vector<std::list<SeguidoresUniversidades>> contenedor_seguidores;
    public:

        MapAbierto(opcion_de_clave opcion) : MapADT(opcion){
            siguiente_tam_contenedor = numeros_primos_interesantes.begin();
            contenedor_seguidores.resize(*siguiente_tam_contenedor);
            siguiente_tam_contenedor++;
            seguidores_totales = 0;
        }

        void put(SeguidoresUniversidades usuarios){
            if (opcion == se_usa_user_id)
                _put_with_longlong(usuarios);
            else
                _put_with_string(usuarios);
            
            _verificar_cantidad_ocupada();

        }
        
        SeguidoresUniversidades get(long long key){
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

        SeguidoresUniversidades remove(long long key){
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

        SeguidoresUniversidades get(std::string key){
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
        SeguidoresUniversidades remove(std::string key){
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


        int size(){
            return seguidores_totales;
        }


        bool empty(){
            return (size() == 0) ? true :  false;
        };

        ~MapAbierto(){

        }
    private:

        void _put_with_longlong(SeguidoresUniversidades usuarios){
            int index = _hashf1(usuarios.user_id);

            (contenedor_seguidores)[index].push_back(usuarios);

            seguidores_totales++;
        }
        
        void _put_with_string(SeguidoresUniversidades usuarios){
            int index =  _hashf1(_acumulacion_polinomial(usuarios.user_name, 33));

            (contenedor_seguidores)[index].push_back(usuarios);

            seguidores_totales++;
        }

        float _porcentaje_llenado(){
            return float(seguidores_totales) / float(contenedor_seguidores.size());
        }

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
            std::cout << "se llamo\n";

        }

        int _hashf1(int k) {
            return k % (contenedor_seguidores).size();
        }

        int _acumulacion_polinomial(std::string word, int constante){
            int resultado = 0;
            for (auto it = word.rbegin(); it != word.rend(); it++){
                resultado*= constante;
                resultado += *it;
            }
            return resultado;
        }

};