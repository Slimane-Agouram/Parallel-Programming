
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  const int PING_PONG_LIMIT = 8000;
	double start=0;
	double end=0;
  // Initialisation
  MPI_Init(NULL, NULL);
  // rang et taille
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  //on verifie qu'on a deux processus pour l'echange
  if (world_size != 2) {
    fprintf(stderr, "World size doit étre 2 %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1); 
  }

  int ping_pong_count = 0;
	
  int partner_rank = (world_rank + 1) % 2;
 start = MPI_Wtime();
	    printf("temps de depart  n. %d %f\n",ping_pong_count, start);
  while (ping_pong_count < PING_PONG_LIMIT) {
    if (world_rank == ping_pong_count % 2) {
      // on incremente le comptuer du nombre de messages envoyés
      ping_pong_count++;
	 

      MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
      printf("%d envoie et incremente du message ping-pong %d à %d\n",
             world_rank, ping_pong_count, partner_rank);
		end= MPI_Wtime();
		printf("temps de fin n. %d %f \n\n",ping_pong_count,end);
    } else{ 
	  
      MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      printf("%d recois le message ping-pong numero %d de %d\n",
             world_rank, ping_pong_count, partner_rank);
	 
   
 }

  }
 end= MPI_Wtime();
	
  MPI_Finalize();
  printf("temps de fin n. %d %f \n\n",ping_pong_count,end);
	printf("Nous avons envoyé en total : %d messages \n", ping_pong_count);
	printf("temps total : %f  secondes \n", end-start );
	printf("temps moyen pour l'envoi d'un msg : %f secondes \n", (end-start)/(double)ping_pong_count);
	printf("le debit est de : %f  octets/secondes \n", 8000.0/((end-start)));
}
