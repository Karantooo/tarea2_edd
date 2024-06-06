#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "limite superior;tiempo clave user_name linear_probing;tiempo clave user_id linear_probing;tiempo clave user_name quadratic;tiempo clave user_id quadratic;tiempo clave user_name double;tiempo clave user_id double;tiempo clave user_name abierto;tiempo clave user_id abierto;tiempo clave user_name stl;tiempo clave user_id stl"

# Repetiremos los experimentos 30 veces
for (( c=1; c<=100; c++ ))
do
    # Ejecutamos la primera versión de heapsort con 5 entradas distintas
    for n in 1000 5000 10000 15000 20000
    do
	    ./carga_map.out  0 $n
    done

done
