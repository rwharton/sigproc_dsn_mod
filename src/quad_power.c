/*

  QUAD_POWER - Combine the intensity/power values in two filterbank files
  together in quadrature.
  
  Initial version (April 2017) Aaron B. Pearlman (aaron.b.pearlman@caltech.edu)

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sigproc.h"
#include "header.h"

FILE *output;

main (int argc, char **argv)
{
  int i=1, j, k, nfiles=0, *numbt, schans=0, nbytes, *nchan;
  FILE *input[32];
  double *stamp, *frch1, *froff, *frmhz;
  output=stdout;
  
  if (argc < 3)
  {
    printf("##################################\n");
    printf("Aaron B. Pearlman\n");
    printf("aaron.b.pearlman@caltech.edu\n");
    printf("Division of Physics, Mathematics, and Astronomy\n");
    printf("California Institute of Technology\n");
    printf("Jet Propulsion Laboratory\n");
    printf("##################################\n\n");
    
    printf("quad_power.c - Combines the intensities/powers in two filterbank ");
    printf("files in quadrature. This is designed for combining data from two ");
    printf("filterbank files together, containing data from orthogonal ");
    printf("polarizations.\n\n");
    
    printf("Usage: quad_power [Filterbank filename 1] [Filterbank filename 2] > [Output filterbank filename]\n\n");
    printf("Example: quad_power slcp_15a201_b10.0_rfi1s.corr srcp_15a201_b10.0_rfi1s.corr > squad_15a201_b10.0_rfi1s.corr\n\n");
    
    exit(0);
  }
  
  // Open up files for reading and writing.
  while (i<argc) {
    if (file_exists(argv[i])) {
      input[nfiles]=open_file(argv[i],"rb");
      nfiles++;
    } else if (strings_equal(argv[i],"-o")) {
      output=open_file(argv[++i],"wb");
    }
    i++;
  }

  /* read in headers and check time stamps */
  stamp = (double *) malloc(nfiles*sizeof(double));
  frch1 = (double *) malloc(nfiles*sizeof(double));
  froff = (double *) malloc(nfiles*sizeof(double));
  numbt = (int *) malloc(nfiles*sizeof(int));
  nchan = (int *) malloc(nfiles*sizeof(int));
  for (i=0; i<nfiles; i++) {
    if (read_header(input[i])) {
      stamp[i]=tstart;
      frch1[i]=fch1;
      froff[i]=foff;
      numbt[i]=nbits;
      nchan[i]=nchans;
    } else {
      error_message("Problem reading header parameters");
    }
    if (data_type != 1) 
      error_message("Input data are not in filterbank format!");
    if (stamp[i] != stamp[0]) 
      error_message("Start times in input files are not identical!");
    if (numbt[i] != numbt[0])
      error_message("Number of bits per sample in input files not identical!");
    if (frch1[i] != frch1[0])
      error_message("Frequencies are not identical!");
  }
  
  send_string("HEADER_START");
  send_int("machine_id",machine_id);
  send_int("telescope_id",telescope_id);
  send_int("data_type",1);
   
  send_double("fch1",frch1[0]);
  send_double("foff",froff[0]);
  send_int("nchans",nchans);
  send_int("barycentric", 0);
  
  frmhz = (double *) malloc(sizeof(double)*schans);
  k=0;
  for (i=0; i<nfiles; i++) {
    for (j=0; j<nchans; j++) {
      frmhz[k]=frch1[i]+j*froff[i];
    }
    
    fprintf(stderr, "Reading polarization #%d - Filterbank file: %s...\n", i+1, argv[i+1]);
  }
  

  if (!strings_equal(source_name,"")) {
    send_string("source_name");
    send_string(source_name);
  }
  send_coords(src_raj,src_dej,az_start,za_start);
  send_int("nbits",nbits);
  send_double("tstart",tstart);
  send_double("tsamp",tsamp);
  send_int("nifs",nifs);
  send_string("HEADER_END");
  
  
  // NOTE: Increasing the blocksize > 1 may cause an incorrect number of samples
  // to be written to the output filterbank file. Be careful!
  // Also works for blocksizes = [1, 2, 4, 8, 16, 32].
  // Breaks down at blocksize=64. Larger blocksizes improve the speed of the
  // algorithm.
  int blocksize=32;
  //int blocksize=1;
  int arraySize = blocksize * sizeof(float);
  float* block1 = malloc(arraySize);
  float* block2 = malloc(arraySize);
  
  int arrayLength = blocksize;
  float quadPowerBuffer[arrayLength];
  int blockIndex;
  
  float v1, v2, sum;
  
  // Read in data from the two filterbank files. Loop on the condition of the
  // return value from reading data in the first filterbank file.
  while(fread(block1, sizeof(float), blocksize, input[0]))
  {
    
    fread(block2, sizeof(float), blocksize, input[1]);
    
    // Compute the quadrature sum of the intensities/power.
    for (blockIndex = 0; blockIndex < arrayLength; blockIndex++)
    {
      block1[blockIndex] = block1[blockIndex] + 100;
      block2[blockIndex] = block2[blockIndex] + 100;
      v1 = block1[blockIndex] * block1[blockIndex];
      v2 = block2[blockIndex] * block2[blockIndex];
      sum = v1 + v2;
      
      quadPowerBuffer[blockIndex] = sqrt(sum);
    }
    
    // Write the quadrature values to a new filterbank file.
    fwrite(&quadPowerBuffer, sizeof(float), blocksize, output);
    
  }
}
