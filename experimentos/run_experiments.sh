#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "limite superior;tiempo clave user_name;tiempo clave user_id"

# Repetiremos los experimentos 30 veces
for (( c=1; c<=3000; c++ ))
do
    # Ejecutamos la primera versión de heapsort con 5 entradas distintas
    for n in 1000 5000 10000 15000 20000
    do
	./a.out 0 $n
    done

done
