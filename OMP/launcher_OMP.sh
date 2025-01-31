#!/bin/bash

#SBATCH --account=tra24_IngInfB2
#SBATCH --partition=g100_usr_prod
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1  # Run a single task per node, more explicit than '-n 1'
#SBATCH -c 7                #  number of CPU cores i.e. OpenMP threads per task
#SBATCH -o job.out
#SBATCH -e job.err

srun ./OMP 12 5