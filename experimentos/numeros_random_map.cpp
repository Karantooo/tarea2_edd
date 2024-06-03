#include <iostream>
#include <chrono>
#include <cstdlib>
#include "../MapAbierto.h"
#include "../CargarDatos.h"


int main(int argc, char** argv){
    int total_busquedas = 5000;
    MapAbierto map_id_abierto(se_usa_user_id);
    CargarDatos datos_id_abierto(&map_id_abierto, "universities_followers.csv");
    

    

    datos_id_abierto.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));

    datos_id_abierto.cargar_map_recordando_keys();

    std::vector<long long> numeros_a_buscar;
    for(int i = 0; i < total_busquedas; i++)
        numeros_a_buscar.push_back(datos_id_abierto.get_random_user_id());
    
    //medimos el acceso a keys pseudo randoms

    auto start = std::chrono::high_resolution_clock::now();
    for (long long numero : numeros_a_buscar){
        map_id_abierto.get(numero);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    double running_time_promedio_id_abierto = running_time / total_busquedas;
    running_time_promedio_id_abierto *= 1e-9;


    MapAbierto map_name_abierto(se_usa_user_name);
    CargarDatos datos_name_abierto(&map_name_abierto, "universities_followers.csv");
    

    

    datos_name_abierto.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));

    datos_name_abierto.cargar_map_recordando_keys();

    std::vector<std::string> nombres_a_buscar;
    for(int i = 0; i < total_busquedas; i++)
        nombres_a_buscar.push_back(datos_name_abierto.get_random_user_name());
    
    //medimos el acceso a keys pseudo randoms

    start = std::chrono::high_resolution_clock::now();
    for (std::string palabra : nombres_a_buscar){
        map_name_abierto.get(palabra);
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    double running_time_promedio_name_abierto = running_time / total_busquedas;
    running_time_promedio_name_abierto *= 1e-9;




    std::cout << argv[1] << ";" << argv[2] << ";" << running_time_promedio_id_abierto << ";" << running_time_promedio_name_abierto <<std::endl;

    return 0;
}