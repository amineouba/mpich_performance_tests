To compare the old MPICH and the MPCIH with optimized collectives. You need to download the two versions.

* The old version (MPCIH-1.2.0) : https://archive.org/download/tucows_8930_MPICH

* The newer (MPCIH2-1.0) : https://www.mpich.org/static/downloads/1.0/

* In the two versions, there is a folder "doc/" with a document (install.pdf,  install.ps.gz) containing an installation guide.

As I wasn't able to install these versions on Grid'5000 (no guide for MPICH), I ran the tests on my machine with 4 processes.

There is a file for each collective operation in which :
for different message sizes, I run 10 tests and calculate the average time.

Instead of using the MPI_Wtime() function to measure the execution time, I used clock() because it has a higher-resolution timer.
