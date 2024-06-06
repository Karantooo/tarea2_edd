#include <string>
#include <iostream>
#pragma once


/**
 * @brief Clase para almacenar los diferentes seguidores de las universidades
 * 
 */
class SeguidoresUniversidades{
    public:
        std::string university;
        long long user_id;
        std::string user_name;
        long long number_tweets;
        long long friends_count;
        long long followers_count;
        std::string created_at;

};

/**
 * @brief Metodo para poder entregar todos los datos de SeguidoresUniversidad en un cout 
 * 
 * @param stream 
 * @param seguidor 
 * @return std::ostream& 
 */
std::ostream& operator<< (std::ostream& stream, SeguidoresUniversidades seguidor){
    stream << seguidor.university << "\n";
    stream << seguidor.user_id << "\n";
    stream << seguidor.user_name << "\n";
    stream << seguidor.number_tweets << "\n";
    stream << seguidor.friends_count << "\n";
    stream << seguidor.followers_count << "\n";
    stream << seguidor.created_at << "\n";
    return stream;
}