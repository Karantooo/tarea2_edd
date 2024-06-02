#include <iostream>
#include <chrono>
#include <cstdlib>
#include "../MapAbierto.h"
#include "../CargarDatos.h"


int main(int argc, char** argv){
    MapAbierto map(se_usa_user_name);
    CargarDatos datos(&map, "universities_followers.csv");

    

    datos.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));

    //medimos la carga de datos

    auto start = std::chrono::high_resolution_clock::now();
    datos.cargar_map();
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time *= 1e-9;


    MapAbierto map2(se_usa_user_id);
    CargarDatos datos2(&map2, "universities_followers.csv");
    
    datos2.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));

    //medimos la carga de datos

    start = std::chrono::high_resolution_clock::now();
    datos2.cargar_map();
    end = std::chrono::high_resolution_clock::now();
    double running_time_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time_2 *= 1e-9;
    std::cout << argv[2] << ";" << running_time << ";" << running_time_2 << std::endl;


    return 0;
}