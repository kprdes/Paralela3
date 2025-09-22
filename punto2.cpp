#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[]) {
    int rank, size;
    int num;

    MPI_Init(&argc, &argv);             
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        num = 49;      
        num = num * num;   
        cout << "Process 0 computed num = " << num << endl;
    }

    MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

    cout << "Process " << rank << " has num = " << num << endl;

    MPI_Finalize(); 
    return 0;
}
