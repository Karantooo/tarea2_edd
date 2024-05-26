#include <vector>
#include <list>
#include <iostream>
#include "MapADT.h"

class MapAbierto : public MapADT{
    private:
        int seguidores_totales;
    public:
        std::vector<std::list<SeguidoresUniversidades>> * contenedor_seguidores;

        MapAbierto(opcion_de_clave opcion) : MapADT(opcion){
            contenedor_seguidores = new std::vector<std::list<SeguidoresUniversidades>>(3);
            seguidores_totales = 0;
        }

        void put(SeguidoresUniversidades usuarios){
            if (opcion == se_usa_user_id)
                _put_with_longlong(usuarios);
            else
                _put_with_longlong(usuarios);
            
            _verificar_cantidad_ocupada();

        }
        
        SeguidoresUniversidades get(long long key){
            int index = _hashf1(key);
            SeguidoresUniversidades nullse;
            nullse.user_name = "Invalid user name";
            std::list<SeguidoresUniversidades> lista = (*contenedor_seguidores)[index];
            for (auto elem : lista){
                if (elem.user_id == key)
                    return elem;
            }

            return nullse;
        }


        int size(){
            return seguidores_totales;
        }


        bool empty(){
            return (size() == 0) ? true :  false;
        };
    private:
        void _put_with_string(SeguidoresUniversidades usuarios){
        }

        void _put_with_longlong(SeguidoresUniversidades usuarios){
            int index = _hashf1(usuarios.user_id);

            (*contenedor_seguidores)[index].push_back(usuarios);

            seguidores_totales++;
        }
        
        float _porcentaje_llenado(){
            return float(seguidores_totales) / float(contenedor_seguidores->size());
        }

        void _verificar_cantidad_ocupada(){
            if (_porcentaje_llenado() < 0.9)
                return;
            
            std::vector<std::list<SeguidoresUniversidades>> * viejo_contenedor_seguidores = this->contenedor_seguidores;
            this->contenedor_seguidores = new std::vector<std::list<SeguidoresUniversidades>>(contenedor_seguidores->size() * 2);
            seguidores_totales = 0;
            //hacemos rehashing
            for (auto lista : *viejo_contenedor_seguidores){
                while (!lista.empty()){
                    SeguidoresUniversidades elemento = lista.back();
                    lista.pop_back();
                    put(elemento);
                }
            }
            delete viejo_contenedor_seguidores;
            std::cout << "se llamo\n";

        }

        int _hashf1(int k) {
            return k % (*contenedor_seguidores).size();
        }

};