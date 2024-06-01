#include <vector>
#pragma once


/**
 * @brief Esta constante contienen los numeros primos interesantes.
 * Para efectos de esta tarea se define como un numero primo interesante
 * aquel que es primo y ademas es el primero despues de una potencia de 2.
 * Estos serviran para el tamaño de los contenedores
 * Los numeros fueron buscados ocupando https://t5k.org/lists/small/millions/
 * y un script en python
 * 
 */
std::vector<long long> numeros_primos_interesantes{
    2, 3, 5, 11, 17, 37, 67, 131, 257, 521, 1031, 2053, 4099, 8209, 16411, 32771, 65537, 131101, 262147, 524309, 1048583, 2097169, 4194319, 8388617, 16777259, 33554467, 67108879, 134217757, 268435459, 536870923
};