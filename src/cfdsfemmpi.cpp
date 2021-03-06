/*
! Program for incompressible Navier-Stokes using Stabilised Finite Element Method
!
!
! Author: Dr. Chennakesava Kadapa
! Date  : 06-May-2020
! Place : Swansea, UK
!
!
*/


#include "headersVTK.h"
#include "headersBasic.h"
#include "headersEigen.h"
#include "StabFEM.h"

using namespace std;



int main(int argc, char* argv[])
{
    //Set the input file name
    //The file name is specified from the command line
    if(argc == 0)
    {
        cerr << " Error in input data " << endl;
        cerr << " You must enter name of input file" << endl;
        cerr << " Aborting..." << endl;
    }

    PetscInitialize(NULL, NULL, "../input/petsc_options.dat", NULL);

    string  meshfile = argv[1];
    string  controlfile = argv[2];


    StabFEM  stabfem;

    stabfem.readInputData(meshfile);

    stabfem.readControlParameters(controlfile);

    stabfem.prepareInputData();

    //stabfem.partitionMesh();

    double t1, t2; 
    int parm[3];

    t1 = MPI_Wtime(); 
    stabfem.setSolver(1, parm, false);
    t2 = MPI_Wtime(); 
    PetscPrintf(MPI_COMM_WORLD, "\n\n Elapsed time = %f seconds \n\n", t2 - t1 );

    t1 = MPI_Wtime(); 
    stabfem.solveFullyImplicit();
    t2 = MPI_Wtime(); 
    PetscPrintf(MPI_COMM_WORLD, "\n\n Elapsed time = %f seconds \n\n", t2 - t1 );

    //string  outputfile = "solution.dat";
    //stabfem.writeResult(outputfile);
    //stabfem.postProcess();

    PetscPrintf(MPI_COMM_WORLD, " Program is successful \n ");

    PetscFinalize(); //CHKERRQ(ierr);

    return 0;
}

