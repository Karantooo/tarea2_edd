#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>
#include <unordered_map>
#include <variant>
#include "SeguidoresUniversidades.h"
#include "MapADT.h"

/**
 * @brief Clase para cargar los datos del csv con la clase unordered_map
 * 
 */
class CargarDatosSTLMap{
    private:
        std::unordered_map<std::variant<long long int, std::string>, SeguidoresUniversidades> * map; 
        std::vector<std::string> lineas_datos;
        char delimiter;
        std::string ruta;
        std::ifstream file;
        std::vector<std::string> keys_user_name;
        std::vector<long long> keys_user_id;
        opcion_de_clave opcion;

    public:

        /**
         * @brief Construct a new Cargar Datos S T L Map object
         * 
         * @param map mapa de la stl
         * @param ruta ubicacion del archivo
         * @param delimiter el delimitador que ocupa el csv
         * @param opcion la opcion de clave que se va a ocupar
         */
        CargarDatosSTLMap(std::unordered_map<std::variant<long long int, std::string>, SeguidoresUniversidades> *map, std::string ruta, char delimiter,opcion_de_clave opcion) : map(map), delimiter(delimiter), opcion(opcion){
            file.open(this->ruta, std::ios::in); 

        }


        /**
         * @brief Construct a new Cargar Datos S T L Map object
         * 
         * Se asume que ocupando este constructor el delimitador es ,
         * @param map mapa de la stl a guardar los datos
         * @param ruta ubicacion del csv
         * @param opcion opcion de clave que se va a utilzar
         */
        CargarDatosSTLMap(std::unordered_map<std::variant<long long int, std::string>, SeguidoresUniversidades> *map, std::string ruta, opcion_de_clave opcion) : map(map), ruta(ruta), opcion(opcion){
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
                if (opcion == se_usa_user_id) 
                    (*map)[seguidor.user_id] = seguidor;
                else
                    (*map)[seguidor.user_name] = seguidor;



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
                
                if (opcion == se_usa_user_id) 
                    (*map)[seguidor.user_id] = seguidor;
                else
                    (*map)[seguidor.user_name] = seguidor;
                
                }
            }
        }


        /**
         * @brief Entrega un user:name random
         * esta funcion esta hecha con el objetivo de testear las busquedas
         * 
         * @return std::string user name pseudo random
         */

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


        /**
         * @brief Obtiene un user_id random de los cargados por el usuario
         * 
         * @return long long random user_id
         */

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


        ~CargarDatosSTLMap(){
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