#include <iostream>
#include <chrono>
#include <cstdlib>
#include <unordered_map>
#include <variant>
#include "../MapAbierto.h"
#include "../MapCerrado.h"
#include "../CargarDatos.h"
#include "../CargarDatosSTLMap.h"


int main(int argc, char** argv){
    double running_time_promedio_id_abierto, running_time_promedio_name_abierto;
    double running_time3, running_time4;
    double running_time5, running_time6;
    double running_time7, running_time8;
    double running_time;
    double running_timeqid, running_timeqname;

    int total_busquedas = 5000;
    MapAbierto map_id_abierto(se_usa_user_id);
    CargarDatos datos_id_abierto(&map_id_abierto, "universities_followers.csv");
    

    

    datos_id_abierto.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));

    datos_id_abierto.cargar_map_recordando_keys();

    std::vector<long long> numeros_a_buscar;
    for(int i = 0; i < total_busquedas; i++)
        numeros_a_buscar.push_back(234980298);
    
    //medimos el acceso a keys pseudo randoms

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
{   start = std::chrono::high_resolution_clock::now();
    for (long long numero : numeros_a_buscar){
        map_id_abierto.get(numero);
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time_promedio_id_abierto = running_time / total_busquedas;
    running_time_promedio_id_abierto *= 1e-9;
}

    MapAbierto map_name_abierto(se_usa_user_name);
    CargarDatos datos_name_abierto(&map_name_abierto, "universities_followers.csv");
    

    

    datos_name_abierto.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));

    datos_name_abierto.cargar_map_recordando_keys();

    std::vector<std::string> nombres_a_buscar;
    for(int i = 0; i < total_busquedas; i++)
        nombres_a_buscar.push_back("kjadnajdnsadkjandj");
{    
    
    //medimos el acceso a keys pseudo randoms

    start = std::chrono::high_resolution_clock::now();
    for (std::string palabra : nombres_a_buscar){
        map_name_abierto.get(palabra);
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time_promedio_name_abierto = running_time / total_busquedas;
    running_time_promedio_name_abierto *= 1e-9;
}
    //id lineal

{    MapCerrado map3(se_usa_user_id, use_linear_probing);
    CargarDatos datos3(&map3,"universities_followers.csv");

    datos3.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    datos3.cargar_map();

    start = std::chrono::high_resolution_clock::now();
    for (long long numero : numeros_a_buscar){
        map3.get(numero);
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time3 = running_time / total_busquedas;
    running_time3 *= 1e-9;
}
    //name lineal

{    MapCerrado map4(se_usa_user_name, use_linear_probing);
    CargarDatos datos4(&map4,"universities_followers.csv");

    datos4.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    datos4.cargar_map();


    start = std::chrono::high_resolution_clock::now();
    for (std::string palabra : nombres_a_buscar){
        map4.get(palabra);
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time4 = running_time / total_busquedas;
    running_time4 *= 1e-9;
}

    {MapCerrado mapqid(se_usa_user_id, use_quadratic_probing);
    CargarDatos datosqid(&mapqid,"universities_followers.csv");

    datosqid.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    datosqid.cargar_map();


    start = std::chrono::high_resolution_clock::now();
    for (long long numero : numeros_a_buscar){
        mapqid.get(numero);
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_timeqid = running_time / total_busquedas;
    running_timeqid *= 1e-9;}

    {MapCerrado mapqname(se_usa_user_id, use_quadratic_probing);
    CargarDatos datosqname(&mapqname,"universities_followers.csv");

    datosqname.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    datosqname.cargar_map();


    start = std::chrono::high_resolution_clock::now();
    for (std::string palabra : nombres_a_buscar){
        mapqname.get(palabra);
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_timeqname = running_time / total_busquedas;
    running_timeqname *= 1e-9;}



    //id double
    {MapCerrado map5(se_usa_user_id, use_double_hashing);
    CargarDatos datos5(&map5,"universities_followers.csv");

    datos5.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    datos5.cargar_map();


    start = std::chrono::high_resolution_clock::now();
    for (long long numero : numeros_a_buscar){
        map5.get(numero);
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time5 = running_time / total_busquedas;
    running_time5 *= 1e-9;
    
    }


{    MapCerrado map6(se_usa_user_name, use_double_hashing);
    CargarDatos datos6(&map6,"universities_followers.csv");

    datos6.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    datos6.cargar_map();


    start = std::chrono::high_resolution_clock::now();
    for (std::string palabra : nombres_a_buscar){
        map6.get(palabra);
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time6 = running_time / total_busquedas;
    running_time6 *= 1e-9;
}

{    std::unordered_map<std::variant<long long int, std::string>, SeguidoresUniversidades> map7;
    CargarDatosSTLMap datos7(&map7,"universities_followers.csv", se_usa_user_id);

    datos7.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    datos7.cargar_map();


    start = std::chrono::high_resolution_clock::now();
    for (long long numero : numeros_a_buscar){
        map7[numero];
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time7 = running_time / total_busquedas;
    running_time7 *= 1e-9;
}
    
{    std::unordered_map<std::variant<long long int, std::string>, SeguidoresUniversidades> map8;
    CargarDatosSTLMap datos8(&map8,"universities_followers.csv", se_usa_user_name);

    datos8.cargar_datos(std::stoi(argv[1]), std::stoi(argv[2]));
    datos8.cargar_map();


    start = std::chrono::high_resolution_clock::now();
    for (std::string palabra : nombres_a_buscar){
        map8[palabra];
    }
    end = std::chrono::high_resolution_clock::now();
    running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    
    running_time8 = running_time / total_busquedas;
    running_time8 *= 1e-9;
}

    std::cout << argv[2] << ";" << running_time3 <<
     ";" << running_time4 << ";" << running_timeqname << ";" << 
     running_timeqid << ";" <<running_time5 <<
     ";" << running_time6 << ";" << running_time8 << ";" << running_time7 << ";" <<
     running_time_promedio_name_abierto << ";" << running_time_promedio_id_abierto
     <<std::endl;

    return 0;
}