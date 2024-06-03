#include <iostream>
#include <chrono>
#include <cstdlib>
#include "../MapAbierto.h"
#include "../CargarDatos.h"
#include "../MapCerrado.h"

int main(int argc, char** argv){
    
    MapCerrado map1(se_usa_user_name, use_linear_probing);
    CargarDatos datos1(&map1, "universities_followers.csv");

    datos1.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    auto start = std::chrono::high_resolution_clock::now();
    datos1.cargar_map();
    auto end = std::chrono::high_resolution_clock::now();
    double running_time1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    running_time1 *= 1e-9;
    
    MapCerrado map2(se_usa_user_id, use_linear_probing);
    CargarDatos datos2(&map2, "universities_followers.csv");

    datos2.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    start = std::chrono::high_resolution_clock::now();
    datos2.cargar_map();
    end = std::chrono::high_resolution_clock::now();
    double running_time2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    running_time2 *= 1e-9;

    // TO FIX:
    /*
    MapCerrado map3(se_usa_user_name, use_quadratic_probing);
    CargarDatos datos3(&map3, "universities_followers.csv");

    datos3.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    start = std::chrono::high_resolution_clock::now();
    datos3.cargar_map();
    end = std::chrono::high_resolution_clock::now();
    double running_time3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    running_time3 *= 1e-9;
    */
   
    MapCerrado map4(se_usa_user_id, use_quadratic_probing);
    CargarDatos datos4(&map4, "universities_followers.csv");

    datos4.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    start = std::chrono::high_resolution_clock::now();
    datos4.cargar_map();
    end = std::chrono::high_resolution_clock::now();
    double running_time4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    running_time4 *= 1e-9;

    MapCerrado map5(se_usa_user_name, use_double_hashing);
    CargarDatos datos5(&map5, "universities_followers.csv");

    datos5.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    start = std::chrono::high_resolution_clock::now();
    datos5.cargar_map();    
    end = std::chrono::high_resolution_clock::now();
    double running_time5 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    running_time5 *= 1e-9;

    MapCerrado map6(se_usa_user_id, use_double_hashing);
    CargarDatos datos6(&map6, "universities_followers.csv");

    datos6.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    start = std::chrono::high_resolution_clock::now();
    datos6.cargar_map();
    end = std::chrono::high_resolution_clock::now();
    double running_time6 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    running_time6 *= 1e-9;

    std::cout << argv[1] << ";" << argv[2] << "/" << running_time1 << ";" << running_time2 << ";" << running_time4 << ";" << running_time5 << ";" <<running_time6 << std::endl;
//std::cout << argv[1] << ";" << argv[2] << "/" << running_time1 << ";" << running_time2 << ";" << running_time3 << ";" << running_time4 << ";" << running_time5 <<  ";" << running_time6 << std::endl;

    return 0;
}
