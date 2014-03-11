#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);


  int number=0;
  if (world_rank != 0) {
    MPI_Recv(&number, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Processus %d reçois %d du processus %d\n", world_rank, number,
           world_rank - 1);
           printf("la somme a ce stage est : %d\n", number);
           number += world_rank;


  } else {
    //printf(" vous avez choisi de transmettre : %d \n",atoi(argv[1]));
  //  int number = atoi(argv[1]);
  }
  MPI_Send(&number, 1, MPI_INT, (world_rank + 1) % world_size, 0,
           MPI_COMM_WORLD);

  if (world_rank == 0) {
    MPI_Recv(&number, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Processus %d reçois %d du processus %d\n", world_rank, number,
           world_size - 1);
  }
  MPI_Finalize();
}
