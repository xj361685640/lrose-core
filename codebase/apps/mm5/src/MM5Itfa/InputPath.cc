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
//////////////////////////////////////////////////////////
// InputPath.cc : Input MM5 file handling
//
// Mike Dixon, RAP, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Sept 1998
//
//////////////////////////////////////////////////////////
//
// See "InputPath.hh" for details.
//
///////////////////////////////////////////////////////////

#include "InputPath.hh"
#include <toolsa/umisc.h>
#include <string>
using namespace std;

/////////////////////////////
// Constructor - Archive mode
//
// Pass in a list of file paths.
//

InputPath::InputPath (const string &prog_name,
		      const Params &params,
		      int n_files,
		      char **file_paths) :
  _progName(prog_name), _params(params)

{

  // initialize

  _archiveMode = true;
  for (int i = 0; i < n_files; i++) {
    _filePaths.insert(file_paths[i]);
  }
  _currentPath = _filePaths.begin();
  _modelTime = -1;
  _forecastLeadTime = -1;
  
}

//////////////////////////////
// Constructor - realtime mode
//
// Pass in (a) the input directory to be watched.
//         (b) the max valid age for a realtime file (secs)
//             the routine will wait for a file with the age
//             less than this.
//         (c) pointer to heartbeat_func. If NULL this is ignored.
//             If non-NULL, this is called once per second while
//             the routine is waiting for new data.

InputPath::InputPath (const string &prog_name,
		      const Params &params,
		      MdvInput_heartbeat_t heartbeat_func) :
  _progName(prog_name), _params(params)

{

  // initialize

  _archiveMode = false;
  _heartbeatFunc = heartbeat_func;
  _ldata.setDir(_params.realtime_input_dir);
  _modelTime = -1;
  _forecastLeadTime = -1;

}

/////////////
// Destructor

InputPath::~InputPath()

{

}

/////////////////////
// get next file path
//
// returns empty string on failure

const string &InputPath::next()

{
  
  if (_archiveMode) {
    
    // in archive mode, go through the file list
    
    if (_currentPath != _filePaths.end()) {
      _inputPath = *_currentPath;
      _currentPath++;
    } else {
      _inputPath = "";
    }

  } else {
    
    // in realtime mode wait for change in latest info
    // sleep 1 second between tries.

    _ldata.readBlocking(_params.max_realtime_valid_age,
			1000, _heartbeatFunc);

    // new data

    _inputPath = _params.realtime_input_dir;
    _inputPath += PATH_DELIM;
    _inputPath += _ldata.getRelDataPath();

    _modelTime = _ldata.getLatestTime();
    int leadTime;
    if (sscanf(_ldata.getUserInfo2().c_str(), "%d", &leadTime) == 1) {
      _forecastLeadTime = leadTime;
    }

  } // if (archiveMode)
  
  return (_inputPath);

}

/////////////////////////
// reset to start of list
// 
// Archive mode only.

void InputPath::reset()

{
  if (_archiveMode) {
    _currentPath = _filePaths.begin();
  }
}



