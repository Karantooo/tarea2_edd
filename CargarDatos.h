#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>
#include "MapADT.h"
#include "SeguidoresUniversidades.h"

/**
 * @brief Clase para cargar los datos del csv con los datos a nuestras implementacion de maps
 * 
 */
class CargarDatos{
    private:
        MapADT * map; 
        std::vector<std::string> lineas_datos;
        char delimiter;
        std::string ruta;
        std::ifstream file;
        std::vector<std::string> keys_user_name;
        std::vector<long long> keys_user_id;

    public:

        /**
         * @brief Constructor CargarDatos
         * 
         * @param map puntero al map a insertar
         * @param ruta ruta del archivo a leer
         * @param delimiter el delimitador del arhivo
         */
        CargarDatos(MapADT *map, std::string ruta, char delimiter) : map(map), delimiter(delimiter){
            file.open(this->ruta, std::ios::in); 

        }

        /**
         * @brief Constructor CargarDatos
         * 
         * Se asume que si se ocupa este constructor se ocupa como delimitador ,
         * 
         * @param map puntero al map a insertar
         * @param ruta ruta del archivo a leer
         */
        CargarDatos(MapADT *map, std::string ruta) : map(map), ruta(ruta){
            file.open(this->ruta, std::ios::in); 
            this->delimiter = ',';
        }


        /**
         * @brief Permite cargar internamente en un string los datos que se van a insertar con cargar_map
         * Se separa ambas funciones cargar_datos y cargar_map para no tomar en consideracion el tiempo que toma
         * en leer el archivo y asi reducir el ruido dentro de nuestros datos.
         * @param lim_inferior se va a comenzar a extraer desde el dato lim_inferior
         * @param lim_superior se va a terminar de extraer hasta el dato lim_superior (no incluido)
         */
        void cargar_datos(int lim_inferior, int lim_superior){

            std::string linea_actual;
            //llamamos a la funcion para quitar la primera columna
            std::getline(file, linea_actual);

            for (int i = 0; i < lim_inferior; i++){
                if (!std::getline(file, linea_actual))
                    exit(1);
                
            }

            for (int i = lim_inferior; i < lim_superior; i++){
                if (!std::getline(file, linea_actual))
                    exit(-1);
                
                this->lineas_datos.push_back(linea_actual);
            }

        }

        /**
         * @brief Se cargan los datos cargados desde cargar_datos
         * Se separa ambas funciones cargar_datos y cargar_map para no tomar en consideracion el tiempo que toma
         * en leer el archivo y asi reducir el ruido dentro de nuestros datos.
         */
        void cargar_map(){
            std::vector<std::string> answer; 
            SeguidoresUniversidades seguidor;
            int contador = 0;
            for (std::string linea : lineas_datos){
                answer = this->_strip(linea);
                seguidor.university = answer[0];
                seguidor.user_id = stod(answer[1]);
                seguidor.user_name = answer[2];
                seguidor.number_tweets = stod(answer[3]);
                seguidor.friends_count = stod(answer[4]);
                seguidor.followers_count = stod(answer[5]);
                seguidor.created_at = answer[6]; 
                map->put(seguidor);

            }
        }

         /**
         * @brief Se cargan los datos cargados desde cargar_datos pero recuerda las keys
         * Se separa ambas funciones cargar_datos y cargar_map para no tomar en consideracion el tiempo que toma
         * en leer el archivo y asi reducir el ruido dentro de nuestros datos.
         * Se recuerdan las keys para propositos de medir el tiempo de las operaciones get
         */
        void cargar_map_recordando_keys(){
            std::vector<std::string> answer; 
            SeguidoresUniversidades seguidor;
            int contador = 0;
            for (std::string linea : lineas_datos){
                answer = this->_strip(linea);
                seguidor.university = answer[0];
                seguidor.user_id = stod(answer[1]);
                seguidor.user_name = answer[2];
                seguidor.number_tweets = stod(answer[3]);
                seguidor.friends_count = stod(answer[4]);
                seguidor.followers_count = stod(answer[5]);
                seguidor.created_at = answer[6]; 

                keys_user_name.push_back(seguidor.user_name);
                keys_user_id.push_back(seguidor.user_id);

                map->put(seguidor);

            }
        }

        std::string get_random_user_name(){
            if (keys_user_name.size() == 0)
                return "invalido";
            // Semilla para el generador de números aleatorios
            std::random_device rd;
            std::mt19937 gen(rd());

            // Límites superior e inferior
            int lower_bound = 0;
            int upper_bound = keys_user_name.size() - 1;

            // Distribución uniforme entre los límites
            std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);

            // Generar número aleatorio
            int random_number = distribution(gen);


            return keys_user_name[random_number];
        }

        long long get_random_user_id(){
            if (keys_user_id.size() == 0)
                return -1;
            // Semilla para el generador de números aleatorios
            std::random_device rd;
            std::mt19937 gen(rd());

            // Límites superior e inferior
            int lower_bound = 0;
            int upper_bound = keys_user_id.size() - 1;

            // Distribución uniforme entre los límites
            std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);

            // Generar número aleatorio
            int random_number = distribution(gen);


            return keys_user_id[random_number];
        }


        ~CargarDatos(){
            file.close();
        }

        private:

            /**
             * @brief Funcion que toma las lineas extraidas del csv y las separa en un array a partir del delimeter
             * 
             * @param linea_actual linea que se va a separar
             * @return std::vector<std::string> linea separada por el delimiter
             */
            std::vector<std::string> _strip (std::string linea_actual){
                std::vector<std::string> answer;
                std::string current_info = "";
                for (char character : linea_actual){
                    if (character == delimiter){
                        answer.push_back(current_info);
                        current_info = ""; 
                        continue;
                    }
                    current_info += character;
                }
                answer.push_back(current_info);
                current_info = ""; 

                return answer;
            }       

};