#include <iostream>
#include "MapAbierto.h"
#include "CargarDatos.h"

int main(){
    MapAbierto map(se_usa_user_id);
    CargarDatos a(&map, "universities_followers.csv");
    a.cargar_datos(0,20);
    a.cargar_map();
    
//pucv_cl,1.09359046472341E+018,dillybooy,324,224,237,Thu Feb 07 19:20:59 +0000 2019

    SeguidoresUniversidades seguidor = map.get(1.09359046472341E+018);
    std::cout << seguidor;

    return 0;
}