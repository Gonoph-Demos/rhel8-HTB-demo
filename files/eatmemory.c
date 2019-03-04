/* eatmemory.c created sometime early 2003 by billy@gonoph.net */
/* Copyright (2010) Added ability to read command line */
/* released under The Unlicense for anyone silly enough to run it */
/* use at your own risk! */
#include <stdio.h>
#include <stdlib.h>
#ifdef POSIX
#include <sys/select.h>
#else
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#endif
#include <string.h>

const int CHUNK=1024*1024;

char **CreateLargeArray(unsigned long megs);
char **CreateLargeChunk(unsigned long chunks,char **largearray);

int main(int argc,char **argv)
{
  
  char **bigarray=NULL;
  unsigned long megabytes;
  unsigned long old_megabytes=0;
  unsigned long looper1;
  unsigned long long realbytes;
  fd_set empty;
  struct timeval waittv;

  if (argc < 2) {
    printf("Enter Megabytes to chew: ");
    fscanf(stdin,"%lu",&megabytes);
    printf("\n");
  } else {
    sscanf(argv[1], "%lu", &megabytes);
  }
  printf("Consuming %ld megabytes\n", megabytes);
  realbytes=megabytes*CHUNK;

  /* the memory eating portion was in a loop.
   * I've since removed the loop, but kept this
   * part in case anyone wants to put it back in */
  if (bigarray) {
    for(looper1=0;looper1<old_megabytes;looper1++) { free(bigarray[looper1]); bigarray[looper1]=0; }
    free(bigarray);
    bigarray=0;
  }
  old_megabytes=megabytes;
  /* end loop handling code */

  bigarray=CreateLargeArray(megabytes);	/* create my array of chunks */
  if (!bigarray) { exit(-1); }

  /* bzero seems faster than memset - I like it more than memset
   * still calloc appears faster on objects larger than 100kb 
   * probably due to mmaping from the OS, so this maybe OS dependant */
  bzero(bigarray,megabytes);

  if (!CreateLargeChunk(megabytes,bigarray)) { exit(-1); }	/* fill in the array with actual chunks */

  /* loop the memory to keep it out of swap
   * wait 100ms per chunk to keep machine from
   * freaking out with max processor usage -
   * especially if it starts to swap */
  for (;;)
  {
    for (looper1=0;looper1<megabytes;looper1++)
    {
      memset(bigarray[looper1],48+(512 % 10),CHUNK);	/* just picked something random to throw in there */
      FD_ZERO(&empty);
      waittv.tv_sec = 0;
      waittv.tv_usec = 100;
      select(0,&empty,&empty,&empty,&waittv);
    }
  }
  
  return(0);
}

char **CreateLargeArray(unsigned long megs)
{
  char **largearray;

  largearray=malloc(megs*sizeof(char*));

  if (!largearray)
  {
    fprintf(stderr,"[warn] Unable to malloc() %lu megabytes.\n",megs);
    perror("[error]");
    return(0);
  }
  return(largearray);
}

char **CreateLargeChunk(unsigned long chunks,char **largearray)
{
  unsigned long looper1;

  /* Loop the largearray and create the CHUNKS
   * I did it this way as in theory, this app
   * should be able to consume >4GB of memory. */
  for(looper1=0;looper1<chunks;looper1++)
  {
    largearray[looper1]=malloc((CHUNK)+1);
    if (!largearray[looper1])
    {
      fprintf(stderr,"[warn] Unable to malloc() %lu chunks.\n",chunks);
      perror("[error]");
      return(0);
    }
    /* set the memory to ascii(48) '0' */
    memset(largearray[looper1],'0',CHUNK);
  }
  return(largearray);
}

// vim: sw=2 cindent :
