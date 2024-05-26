#include <string>
#include "SeguidoresUniversidades.h"

enum opcion_de_clave{
    se_usa_user_id,
    se_usa_user_name
};

class MapADT{
    protected:
        opcion_de_clave opcion;

    public:
        MapADT(opcion_de_clave opcion) : opcion(opcion){

        }

        virtual void put(SeguidoresUniversidades usuarios) = 0;
        //metodos para user ID
        virtual SeguidoresUniversidades get(long long key) = 0;
        virtual SeguidoresUniversidades remove(long long key) = 0;

        //metodos para user name
        virtual SeguidoresUniversidades& get(std::string key) = 0;
        virtual SeguidoresUniversidades& remove(std::string key) = 0;

        virtual int size() = 0;
        virtual bool empty() = 0;

        SeguidoresUniversidades operator[](long long key){
            return this->get(key);
        }

        SeguidoresUniversidades operator[](std::string key){
            return get(key);
        }




        ~MapADT(){

        }
};