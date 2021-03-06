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

/* RCS info
 *   $Author: dixon $
 *   $Locker:  $
 *   $Date: 2016/03/03 19:24:05 $
 *   $Id: PtFuzzyFunc.hh,v 1.4 2016/03/03 19:24:05 dixon Exp $
 *   $Revision: 1.4 $
 *   $State: Exp $
 */
 
/**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**/

/************************************************************************
 * PtFuzzyFunc.hh: class implementing a fuzzy function defined by a
 *                 point function.  The point function can be interpolated
 *                 in several ways (see the classes derived from
 *                 PtFunction).
 *
 * RAP, NCAR, Boulder CO
 *
 * August 1999
 *
 * Nancy Rehak
 *
 ************************************************************************/

#ifndef PtFuzzyFunc_HH
#define PtFuzzyFunc_HH

/*
 **************************** includes **********************************
 */


#include <iostream>

#include <rapmath/FuzzyFunction.hh>
#include <rapmath/PtFunction.hh>
using namespace std;


/*
 ******************************* defines ********************************
 */

/*
 ******************************* structures *****************************
 */

/*
 ************************* global variables *****************************
 */

/*
 ***************************** function prototypes **********************
 */

/*
 ************************* class definitions ****************************
 */

class PtFuzzyFunc : public FuzzyFunction
{
public:

  ////////////////////////////////
  // Constructors & destructors //
  ////////////////////////////////

  // Constructors

  PtFuzzyFunc(PtFunction *function);
  
  // Destructor

  virtual ~PtFuzzyFunc(void);
  

  /////////////////////////
  // Computation methods //
  /////////////////////////

  // Apply the fuzzy function to the given data value.

  double apply(const double x) const;
  

  //////////////////////////
  // Input/output methods //
  //////////////////////////

  // Print the function information to the given stream.

  void print(ostream &out) const;
  

protected:

  ///////////////////////
  // Protected members //
  ///////////////////////

  PtFunction *_function;
  

private:

  /////////////////////
  // Private methods //
  /////////////////////

  // Don't let people use the copy constructor.  We do this because the
  // object contains a PtFunction pointer, but this pointer most likely
  // points to an object derived from the PtFunction object.

  PtFuzzyFunc(const PtFuzzyFunc& rhs);
  
  // Return the class name for error messages.

  static const char *_className(void)
  {
    return("PtFuzzyFunc");
  }
  
};


#endif
