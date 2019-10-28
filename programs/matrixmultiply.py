"""
/**********************************************************************
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

•   Redistributions of source code must retain this list of conditions and 
    the following disclaimer.
•   Redistributions in binary form must reproduce this list of conditions and
    the following disclaimer in the documentation and/or
    other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
"""
# Matrix multiplication benchmark
# ===============================
# Run by:
#
#    python3 matrixmultiply.py single
#
# or
#
#    python3 matrixmultiply.py double
#
# to measure multiplying two random 2400 x 2400 random matrices
# using single or double precision, respectively.

from numpy.random import seed, uniform
from numpy import float32, float64
from time import process_time, perf_counter
from sys import argv, maxsize
from platform import uname, python_version

def matrixmultiply(typestr = 'double'):
    n = 2400
    iterations = 10
    seed(123)
    if typestr == 'single':
        floattype = float32
    else:
        floattype = float64

    # Initialize
    a = uniform(0, 10, (n, n)).astype(floattype)
    b = uniform(0, 10, (n, n)).astype(floattype)
    
    # Perform measurement
    t0 = 0
    t1 = 0
    for i in range(iterations):
        t0 -= process_time()
        t1 -= perf_counter()
        c = a.dot(b)
        t0 += process_time()
        t1 += perf_counter()
        
    #Print result
    print('{0:.4f}s mean elapsed time,'.format(t1/iterations),
          '{0:.4f}s mean process time (total for all cores)'.format(t0/iterations))
    print('using', floattype)
    # Print general computer info
    u = uname()
    print('Operating system:', u.system, u.release + ',',
          '64-bit,' if (maxsize > 2**31 - 1) else '32-bit;',
          'Python version', python_version(),
          '\nCPU:', u.processor)
    try:
        from psutil import cpu_count, virtual_memory, cpu_freq
        print('Cores:',
              cpu_count(logical=False), 'physical,',
              cpu_count(logical=True), 'logical;',
              'RAM: {0:.3f}GB total'.format(virtual_memory().total/1e9))
        print('Current CPU frequency: {0:.3f}GHz'.format(cpu_freq().current/1e3))
    except:
        print('(Install psutil to find more details!)')

    # System specific information
    if u.system == 'Windows':
        from subprocess import check_output
        info = check_output('wmic cpu get name').decode().split()[1:]
        print(' '.join(info))
    elif u.system == 'Linux':
        from platform import linux_distribution
        print('Distribution: {0} {1}'.format(*linux_distribution()))
        from re import sub
        from subprocess import check_output
        info = check_output('cat /proc/cpuinfo', shell=True).decode().split('\n')
        for line in info:
            if 'model name' in line:
                info = sub( '.*odel name.*:', '', line, 1)
                break
        for line in info:
            if 'ardware' in line:
                info += ', ' + sub( '.*ardware.*:', '', line, 1)
                break
        print(info)
    elif u.system == 'Darwin':
        from platform import mac_ver
        print('Mac OSX release {0},'.format(mac_ver()[0]))

    return c[0, 0]

# For calling from command line
if __name__=='__main__':
    if len(argv) == 2: 
        matrixmultiply(argv[1])
    else:
        matrixmultiply('double')
