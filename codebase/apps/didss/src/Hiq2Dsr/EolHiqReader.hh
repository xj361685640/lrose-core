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
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

// RCS info
//   $Author: dixon $
//   $Locker:  $
//   $Date: 2016/03/06 23:53:40 $
//   $Id: EolHiqReader.hh,v 1.2 2016/03/06 23:53:40 dixon Exp $
//   $Revision: 1.2 $
//   $State: Exp $
//
 
/**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**/
/*********************************************************************
 * EolHiqReader: Class for objects used to read HiQ beam data from an
 *               EOL processor.
 *
 * RAP, NCAR, Boulder CO
 *
 * October 2008
 *
 * Nancy Rehak
 *
 *********************************************************************/

#ifndef EolHiqReader_hh
#define EolHiqReader_hh

#include "HiqReader.hh"

using namespace std;


class EolHiqReader : public HiqReader
{

public:

  ////////////////////////////////
  // Constructors & Destructors //
  ////////////////////////////////

  /*********************************************************************
   * Constructor
   */

  EolHiqReader(MsgFactory *msg_factory, const bool debug = false);


  /*********************************************************************
   * Destructor
   */

  virtual ~EolHiqReader();


protected:

  ///////////////////////
  // Protected methods //
  ///////////////////////

  /*********************************************************************
   * _getMessageLen() - Get the message length from this message pointer.
   */

  virtual int _getMessageLen(char *msg_ptr) const;
  

  /*********************************************************************
   * _isHeader() - Returns true if this message starts with a header,
   *               false otherwise.
   */

  virtual bool _isHeader(char *msg_ptr) const;
  

};

#endif
