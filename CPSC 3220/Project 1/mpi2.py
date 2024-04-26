# Python script for a simple send and receive
#
# messages are one-element lists created by numpy
#
# command line to run is: mpiexec -n 2 python mpi2.py

import numpy
import time

from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

a = numpy.empty(1, dtype='i')
b = numpy.empty(1, dtype='i')
b[0] = 0
c = 0

if rank == 0:
	time.sleep( 1 );

	a[0] = 1

	print( 'process ' + str(rank) + ' sends message ' + str(a) + \
	 ' to process 1' )
	comm.Send( a, dest=1 )

if rank == 1:
	print( 'process ' + str(rank) + ' starts with empty message ' + \
	 str(b) )

	comm.Recv( b, source=0 )
	print( 'process ' + str(rank) + ' receives message ' + str(b) + \
	 ' from process 0' )

	c = b[0]
	print( 'process ' + str(rank) + ' can now use value ' + str(c) )
