#include <iostream>
#include <cstdlib>
#include "../MapAbierto.h"
#include "../CargarDatos.h"


int main(int argc, char** argv){
    MapAbierto map(se_usa_user_name);
    CargarDatos datos(&map, "universities_followers.csv");

    

    datos.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));

    //medimos la carga de datos
    datos.cargar_map();


    return 0;
}