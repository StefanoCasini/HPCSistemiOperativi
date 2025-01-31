#!/bin/bash

#SBATCH --account=tra24_IngInfB2
#SBATCH --partition=g100_usr_prod
#SBATCH --nodes=5
#SBATCH --ntasks-per-node=1
#SBATCH -o job.out
#SBATCH -e job.err
module load autoload intelmpi
srun ./MPI 10
