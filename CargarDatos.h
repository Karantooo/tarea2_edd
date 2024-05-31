#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "MapADT.h"
#include "SeguidoresUniversidades.h"
#include <iostream>


class CargarDatos{
    private:
        MapADT * map; 
        std::vector<std::string> lineas_datos;
        char delimiter;
        std::string ruta;
        std::ifstream file;
    public:

        CargarDatos(MapADT *map, std::string ruta, char delimiter) : map(map), delimiter(delimiter){
            file.open(this->ruta, std::ios::in); 

        }

        CargarDatos(MapADT *map, std::string ruta) : map(map), ruta(ruta){
            file.open(this->ruta, std::ios::in); 
            this->delimiter = ',';
        }

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