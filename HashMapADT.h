#include <string>
#include "SeguidoresUniversidades.h"

class HashMapADT{
    public:
        HashMapADT(){

        }

        //metodos para user ID
        virtual void insert(long long key, SeguidoresUniversidades usuarios) = 0;
        virtual SeguidoresUniversidades& get(long long key) = 0;
        virtual SeguidoresUniversidades& remove(long long key) = 0;

        //metodos para user name
        virtual void insert(std::string key, SeguidoresUniversidades usuarios) = 0;
        virtual SeguidoresUniversidades& get(std::string key) = 0;
        virtual SeguidoresUniversidades& remove(std::string key) = 0;


        SeguidoresUniversidades& operator[](long long key){
            return this->get(key);
        }

        SeguidoresUniversidades& operator[](std::string key){
            return get(key);
        }

        virtual int size() = 0;
        virtual bool empty() = 0;

        //Falta keys y values


        ~HashMapADT(){

        }
};