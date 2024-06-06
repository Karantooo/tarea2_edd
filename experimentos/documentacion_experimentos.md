# Documentacion general de los experimentos

Si se quiere replicar nuestros experimentos se tiene que hacer un make en la carpeta de experimentos. Hay 4 archivos donde se ejecutan cada uno de los experimentos.

Aqui una descripcion general de cada experimento:

- **busquedas_tiempo.sh:** Testea el tiempo que toma en realizar las busquedas en cada map. Todas las busquedas son de elementos que se encuentran en el map.
- **busquedas_tiempo_map.sh:** Testea el tiempo que toma en realizar las busquedas en cada map. Todas las busquedas son de elementos que no se encuentran en el map.
- **run_experiment_memory.sh:** Aqui se testea la cantidad de memoria utilizada cada implementacion de map.
- **run_experiments_carga_tiempo.sh:** Se testea cuanto tiempo toma cargar los datos en los maps.

## Documentacion archivos
Todos los scripts espacio_* tienen el objetivo medir la memoria. carga_map.cpp es para medir la carga de las implementaciones. numeros_random_map.cpp y numeros_random_no_map.cpp es para medir el timepo de los get.