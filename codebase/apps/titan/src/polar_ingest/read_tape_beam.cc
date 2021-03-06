// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
/***************************************************************************
 * read_tape_beam.c
 *
 * reads a logical record from the tape
 *
 * returns the size of the logical record
 *
 * Mike Dixon/Gary Blackburn RAP NCAR September 1990
 *
 **************************************************************************/

#include "polar_ingest.h"
#include <toolsa/sockutil.h>
#include <toolsa/ttape.h>

static si32 read_record(char *buffer);

si32 read_tape_beam (char **beam_buffer)

{

  static char buffer[MAX_TAPE_REC_SIZE];

  static si32 offset = 0;   /* Offset of a logical record */ 
  static si32 left = 0;	    /* Number of logical records left in buffer */
  static si32 nread = 0;
  
  si32 log_rec_size;        /* size of logical record */
  si32 eof_flag = 0;        /* end of tape flag */

  rp7_params_t *rp7hdr;
  
  /*
   * check that the header type is not lincoln
   */

  if (Glob->header_type == LINCOLN_HEADER) {

    fprintf(stderr, "ERROR - %s:read_tape_beam\n",
	    Glob->prog_name);
    fprintf(stderr, "Header type set to 'lincoln'\n");
    fprintf(stderr, "This is not appropriate for tape operations.\n");
    tidy_and_exit(-1);

  }

 read_another:

  if (left == 0) {

    nread = read_record(buffer);
    offset = 0;
    left = nread;

  }

  if (nread <= 0) {

    /*
     * no bytes returned from read
     */

    if (eof_flag >= 2) {

      /*
       * logical end of tape 
       */

      if (Glob->summary_print ||
	  Glob->header_print) {
	printf ("%s: logical end of tape encountered\n",
		Glob->tape_name);
      }
      
      /*
       * set counter to indicate end of tape
       */

      *beam_buffer = (char *) 0;
      log_rec_size = 0;

    } else {

      /*
       * end of file
       */

      left = 0;
      eof_flag++;

      if (Glob->summary_print ||
	  Glob->header_print) {
	printf("%s: end of file\n", Glob->tape_name);
      }
      
      goto read_another;

    }

  } else {

    eof_flag = 0;
    *beam_buffer = buffer + offset;
    rp7hdr = (rp7_params_t *) *beam_buffer;
    BE_to_rp7_params(rp7hdr);
    log_rec_size = rp7hdr->rec_size * 2;
    offset += log_rec_size;
    left -= log_rec_size;
    if (left < log_rec_size) left = 0;

    /*
     * make sure year is in full resolution
     */

    if (rp7hdr->year < 1900) {
      if (rp7hdr->year> 70)
	rp7hdr->year += 1900;
      else
	rp7hdr->year += 2000;
    }

  }

  /*
   * wait a given time
   */

  if (Glob->tape_read_wait > 0)
    uusleep((ui32) Glob->tape_read_wait);

  /*
   * return record size
   */

  return log_rec_size;

}

/***************************************************************************
 * read_record()
 *
 * reads a physical record from the tape
 *
 * Returns the size of the record read, and loads the data into buffer
 *
 * Gary Blackburn / Mike Dixon RAP NCAR September 1990
 *
 **************************************************************************/

static si32 read_record (char *buffer)

{

  static int tape;
  static int first_call = TRUE;
  int nread;

  /*
   * on first call, open tape device
   */

  if (first_call) {

    if((tape = open(Glob->tape_name, O_RDONLY)) < 0) {
      fprintf(stderr, "\nERROR - %s:read_tape_beam.\n",
	      Glob->prog_name);
      fprintf(stderr, "Opening tape unit\n");
      perror(Glob->tape_name);
      tidy_and_exit(-1);
    }

    /*
     * set variable block size
     */
    
    if (TTAPE_set_var(tape)) {
      fprintf(stderr, "ERROR - %s:read_tape_beam - TAPE_set_var\n",
	      Glob->prog_name);
      fprintf(stderr, "Cannot set to variable block size.\n");
      perror(Glob->tape_name);
      tidy_and_exit(-1);
    }
  
    first_call = FALSE;

  }

  /*
   * wait on tape for up to 10 secs at a time
   */
  
  while (SKU_read_select(tape, 10000) < 0) {
    
    /*
     * timeout
     */

    PMU_auto_register("Waiting for tape");

  }

  PMU_auto_register("Reading tape");

  errno = EINTR;
  while (errno == EINTR) {
    errno = 0;
    nread = read (tape, buffer, MAX_TAPE_REC_SIZE);
  }
  
  return (nread);

}
