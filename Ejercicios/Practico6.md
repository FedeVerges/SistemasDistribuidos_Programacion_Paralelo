# Practico 6 MPI

## Cambios en el ejercicio 1.

Principalmente lo que se puede modificar es "mover" el codigo del proceso 0 a otro, simplemente cambiando la condicion del if(world_rank == <Numero del proceso que desee.>).



## Ejercicio 4 Generacion Dinamica de procesos.

* En este caso tenemos un proceso padre llamado Manager que es el encargado de crear otros procesos a traves del metodo MPI_Comm_spawn esto le permite, pasando como parametro el programa que ejecutara el proceso hijo (worker), la cantidad de procesos que creará, el numero del proceso raiz, el comunicador del proceso maestro (MPI_Comm_Self) y el intercomunicador (se encarga de comunicar al padre con su hijo), y otros parametros mas.

* Cada proceso maestro (padre) tiene su propio comunicador, cada proceso hijo que es generado por su proceso maestro tiene su propio comunicador (es decir, su MPI_Comm_World) y tambien estos tienen su intercomunicador que es pasado en el metodo de Spawn.
  
* El proceso hijo se obtiene su comunicador a traves del metodo MPI_Comm_get_parent. Cada proceso hijo es un proceso remoto.


