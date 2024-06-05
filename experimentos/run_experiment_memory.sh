#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "experimento;limite superior;memoria ocupada en bytes"

# Repetiremos los experimentos 30 veces
for (( c=1; c<=30; c++ ))
do
    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./name_cerrado_quadratic.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "cerrado quadratic name;$n;$palabra"

    done
    # Ejecutamos la primera versión de heapsort con 5 entradas distintas
    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./name_abierto.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "name abierto;$n;$palabra"
    done

    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./id_abierto.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "id abierto;$n;$palabra"

    done

    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./map_stl_id.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "map stl id;$n;$palabra"

    done

    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./map_stl_name.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "map stl name;$n;$palabra"

    done

    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./id_cerrado_linear.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "cerrado lineal id;$n;$palabra"

    done

    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./name_cerrado_linear.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "cerrado lineal name;$n;$palabra"

    done

    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./name_cerrado_double.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "cerrado double name;$n;$palabra"

    done

    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./id_cerrado_double.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "cerrado double id;$n;$palabra"

    done

    for n in 1000 5000 10000 15000 20000
    do
        palabra=$(valgrind ./id_cerrado_quadratic.out 0 "$n" 2>&1 | grep "total heap usage")

        # Imprimir el contenido de 'palabra'
        echo "cerrado quadratic id;$n;$palabra"

    done




done
