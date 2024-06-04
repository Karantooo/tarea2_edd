#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include "../MapAbierto.h"
#include "../CargarDatosSTLMap.h"


int main(int argc, char** argv){
    std::unordered_map<std::variant<long long int, std::string>, SeguidoresUniversidades> map;
    CargarDatosSTLMap datos(&map, "universities_followers.csv", se_usa_user_name);

    

    datos.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));

    //medimos la carga de datos
    datos.cargar_map();


    return 0;
}