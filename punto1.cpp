#include <mpi.h>        
#include <iostream>     
#include <vector>       
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if (size != 2) {
        if (rank == 0) {
            cerr << "Este programa debe ejecutarse con exactamente 2 procesos.\n";
            cerr << "Ejemplo: mpirun -np 2 ./mpi_pp_point2point\n";
        }
        MPI_Finalize();  
        return 1;        
    }

    const int N = 10000;
    vector<float> A(N), B(N);

    for (int i = 0; i < N; i++) {
        A[i] = float(rank);
    }

    int other;
    if (rank == 0) {
        other = 1;
    } else {
        other = 0;
    }

    MPI_Status status;

    // Proceso 0: primero ENVÍA, luego RECIBE
    // Proceso 1: primero RECIBE, luego ENVÍA

    if (rank == 0) {
        MPI_Send(A.data(), N, MPI_FLOAT, other, 0, MPI_COMM_WORLD);
        
        MPI_Recv(B.data(), N, MPI_FLOAT, other, 0, MPI_COMM_WORLD, &status);
    } else {
        MPI_Recv(B.data(), N, MPI_FLOAT, other, 0, MPI_COMM_WORLD, &status);
    
        MPI_Send(A.data(), N, MPI_FLOAT, other, 0, MPI_COMM_WORLD);
    }

    int idx = 500;
    for (int i = 0; i < 5; i++) {
        cout << "Proceso " << rank << " B[" << i << "] = " << B[i] << " "<<endl;
    }
    cout << endl;
    
    MPI_Finalize();
    return 0;
}
