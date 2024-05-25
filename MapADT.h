#include <string>
#include "SeguidoresUniversidades.h"

class MapADT{
    private:
        opcion_de_clave opcion;

    public:
        MapADT(opcion_de_clave opcion) : opcion(opcion){

        }

        //metodos para user ID
        virtual void put(SeguidoresUniversidades usuarios) = 0;
        virtual SeguidoresUniversidades& get(long long key) = 0;
        virtual SeguidoresUniversidades& remove(long long key) = 0;

        //metodos para user name
        virtual void put(SeguidoresUniversidades usuarios) = 0;
        virtual SeguidoresUniversidades& get(std::string key) = 0;
        virtual SeguidoresUniversidades& remove(std::string key) = 0;

        virtual int size() = 0;
        virtual bool empty() = 0;

        SeguidoresUniversidades& operator[](long long key){
            return this->get(key);
        }

        SeguidoresUniversidades& operator[](std::string key){
            return get(key);
        }




        ~MapADT(){

        }
};