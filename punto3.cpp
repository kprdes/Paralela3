#include <mpi.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    const int N = 10000;
    vector<float> A(N), B(N);

    for (int i = 0; i < N; i++) {
        A[i] = float(rank);
    }

    int destination = (rank + 1) % size;
    int source = (rank - 1 + size) % size;

    MPI_Status status;

    if (rank == 0) {
        MPI_Send(A.data(), N, MPI_FLOAT, destination, 0, MPI_COMM_WORLD);
        MPI_Recv(B.data(), N, MPI_FLOAT, source, 0, MPI_COMM_WORLD, &status);
    } else if (rank == size - 1) {
        MPI_Recv(B.data(), N, MPI_FLOAT, source, 0, MPI_COMM_WORLD, &status);
        MPI_Send(A.data(), N, MPI_FLOAT, destination, 0, MPI_COMM_WORLD);
    } else {
        MPI_Send(A.data(), N, MPI_FLOAT, destination, 0, MPI_COMM_WORLD);
        MPI_Recv(B.data(), N, MPI_FLOAT, source, 0, MPI_COMM_WORLD, &status);
    }

    cout << "I am process ranked " << rank << " and I have received b[0] = ";
    cout << fixed;
    cout.precision(2);
    cout << B[0] << endl;

    MPI_Finalize();
    return 0;
}