#include <iostream>
#include <chrono>
#include <cstdlib>
#include "../MapAbierto.h"
#include "../CargarDatos.h"


int main(int argc, char** argv){
    MapAbierto map(se_usa_user_id);
    CargarDatos datos(&map, "universities_followers.csv");
    

    

    datos.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));

    datos.cargar_map_recordando_keys();
    
    //medimos el acceso a keys pseudo randoms

    auto start = std::chrono::high_resolution_clock::now();
    
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time *= 1e-9;
    std::cout << argv[1] << ";" << argv[2] << ";" << running_time << std::endl;

    return 0;
}