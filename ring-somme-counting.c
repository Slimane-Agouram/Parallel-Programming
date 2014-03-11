#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  MPI_Request r ;
  int number;
  int sum = 0;
  if (world_rank != 0) {
    MPI_Irecv(&number, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,
             &r);
    MPI_Wait(&r, MPI_STATUS_IGNORE);

    printf("Processus %d reçois %d du processus %d\n", world_rank, number,
           world_rank - 1);
           number = world_rank;
           sum = number + sum;

  } else {
    //printf(" vous avez choisi de transmettre : %d \n",atoi(argv[1]));
  //  int number = atoi(argv[1]);
  }
  MPI_Issend(&number, 1, MPI_INT, (world_rank + 1) % world_size, 0,
           MPI_COMM_WORLD, &r);


  if (world_rank == 0) {
    MPI_Irecv(&number, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD,
              &r);
    MPI_Wait(&r, MPI_STATUS_IGNORE);
    printf("Processus %d reçois %d du processus %d\n", world_rank, number,
           world_size - 1);
           sum = number+sum;
  }
  MPI_Finalize();
  printf("Fin ; la somme est : %d\n", sum);

}
