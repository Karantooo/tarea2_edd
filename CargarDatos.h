#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
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

        ~CargarDatos(){
            file.close();
        }

        private:

            /**
             * @brief Funcion que toma las lineas esctraidas del csv y las separa en un array a partir del delimeter
             * 
             * @param linea_actual linea qye se va a separar
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