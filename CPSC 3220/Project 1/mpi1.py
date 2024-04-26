# simple example to show three completely independent
#   processes where each one has its own copies of the
#   variables comm, rank, and x
#
# each process is running the same program and is
#   directed to execute distinct statements by
#   conditioning the statements on the value of the
#   rank variable
#
# command to run is: mpiexec -n 3 python mpi1.py

from mpi4py import MPI
import time

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

x = 0

if rank == 0:
	x += 5
	print( 'for rank ' + str(rank) + ', x = ' + str(x) )

elif rank == 1:
	x += 10
	print( 'for rank ' + str(rank) + ', x = ' + str(x) )

elif rank == 2:
	time.sleep( 1 );
	print( 'for rank ' + str(rank) + ', x = ' + str(x) )
