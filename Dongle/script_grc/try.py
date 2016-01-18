import numpy as np
import sys

(scriptName, inFileName, outFileName) = sys.argv;

ubytes = np.fromfile(inFileName, dtype='uint8', count=-1)

# we need an even number of bytes
# discard last byte if the count is odd

if len(ubytes)%2==1:
    ubytes = ubytes[0:-1]

print "read "+str(len(ubytes))+" bytes from "+inFileName

# scale the unsigned byte data to become a float in the interval 0.0 to 1.0

ufloats = 0.008*(ubytes.astype(float)-127.0)

ufloats.shape = (len(ubytes)/2, 2)

# turn the pairs of floats into complex numbers, needed by gqrx and other gnuradio software

IQ_data = (ufloats[:,0]+1j*ufloats[:,1]).astype('complex64')

IQ_data.tofile(outFileName)
