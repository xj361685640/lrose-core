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
/////////////////////////////////////////////////////////////
// DoeNcRadxFile.hh
//
// DoeNcRadxFile object
//
// NetCDF data for radar radial data in early DOE netcdf format
//
// Mike Dixon, RAP, NCAR
// P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// March 2013
//
///////////////////////////////////////////////////////////////

#ifndef DoeNcRadxFile_HH
#define DoeNcRadxFile_HH

#include <string>
#include <vector>

#include <Radx/Radx.hh>
#include <Radx/RadxFile.hh>
#include <Radx/RadxRangeGeom.hh>
#include <Radx/RadxRemap.hh>
#include <Radx/RadxTime.hh>
#include <Radx/RadxRay.hh>
#include <Ncxx/Nc3xFile.hh>
// #include <Radx/Udunits2.hh>

class RadxField;
class RadxVol;
class RadxSweep;
class RadxRcalib;
using namespace std;

///////////////////////////////////////////////////////////////
/// FILE IO CLASS FOR DOE NETCDF RADIAL FILE FORMAT
///
/// This subclass of RadxFile handles I/O for DOE netcdf files.

class DoeNcRadxFile : public RadxFile

{
  
public:

  /// Constructor
  
  DoeNcRadxFile();
  
  /// Destructor
  
  virtual ~DoeNcRadxFile();
  
  /// clear all data
  
  virtual void clear();

  /// Check if specified file is a DOE file
  /// Returns true on success, false on failure
  
  virtual bool isSupported(const string &path);
    
  /// Check if specified file is a DOE file.
  /// Returns true on success, false on failure
  
  bool isDoeNc(const string &path);
    
  //////////////////////////////////////////////////////////////
  /// \name Perform writing:
  //@{

  //////////////////////////////////////////////////////////////
  /// Write data from RadxVol volume to the specified directory.
  ///
  /// This class is for reading only, to the write methods
  /// simply print a warning that they are not implemented.
  ///
  /// Returns 0 on success, -1 on failure

  virtual int writeToDir(const RadxVol &vol,
                         const string &dir,
                         bool addDaySubDir,
                         bool addYearSubDir);

  //////////////////////////////////////////////////////////////
  /// Write data from RadxVol volume to the specified path.
  ///
  /// This class is for reading only, to the write methods
  /// simply print a warning that they are not implemented.
  ///
  /// Returns 0 on success, -1 on failure
  
  virtual int writeToPath(const RadxVol &vol,
                          const string &path);

  //@}

  //////////////////////////////////////////////////////////////
  /// \name Perform the read:
  //@{
  
  /// Read in data file from specified path,
  /// load up volume object.
  /// Returns 0 on success, -1 on failure
  /// Use getErrStr() if error occurs
  
  virtual int readFromPath(const string &path,
                           RadxVol &vol);
  
  //@}

  ////////////////////////
  /// \name Checks
  //@{
  
  /// Check if number of gates vary in volume
  
  // bool getNGatesVary() const { return _nGatesVary; }
    
  //@}

  ////////////////////////
  /// \name Printing:
  //@{
  
  /// Print summary after read.
  
  virtual void print(ostream &out) const;
  
  /// Print data in file, in native format.
  ///
  /// This is not really applicable to netcdf files, and will
  /// return an error.
  ///
  /// For netcdf, use ncdump to inspect file.
  ///
  /// Returns 0 on success, -1 on failure
  /// Use getErrStr() if error occurs
  
  virtual int printNative(const string &path, ostream &out,
                          bool printRays, bool printData);

  /// Get the date and time from a dorade file path.
  /// returns 0 on success, -1 on failure

  int getTimeFromPath(const string &path, RadxTime &rtime);
  
  //@}

protected:
private:

  // netcdf file
  
  Nc3xFile _file;

  // udunits

  // Udunits2 _udunits;
  
  // dimensions

  Nc3Dim *_timeDim;
  Nc3Dim *_rangeDim;
  Nc3Dim *_sweepDim;

  // times
  
  Nc3Var *_timeVar;
  vector<double> _dTimes;
  time_t _refTimeSecsFile;
  bool _rayTimesIncrease;
  size_t _nTimesInFile;
  
  // range

  Nc3Var *_rangeVar;
  vector<double> _rangeKm;
  size_t _nRangeInFile;
  bool _gateSpacingIsConstant;
  RadxRangeGeom _geom;
  RadxRemap _remap;

  // georef variables
  
  Nc3Var *_latitudeVar;
  Nc3Var *_longitudeVar;
  Nc3Var *_altitudeVar;
  
  double _latitudeDeg;
  double _longitudeDeg;
  double _altitudeKm;

  // ray variables

  Nc3Var *_azimuthVar;
  Nc3Var *_azimuthRateVar;
  Nc3Var *_elevationVar;
  Nc3Var *_elevationRateVar;
  Nc3Var *_noiseVar;
  Nc3Var *_pedestalOpModeVar;
  Nc3Var *_polarizationVar;

  vector<double> _azimuths;
  vector<double> _elevations;
  vector<double> _azScanRates;
  vector<double> _elScanRates;
  vector<double> _noiseDbms;
  vector<int> _pedestalOpModes;
  vector<int> _polarizations;
  
  // sweep variables

  Nc3Var *_sweepTypeVar;
  Nc3Var *_sweepStartIndexVar;
  Nc3Var *_sweepLengthVar;
  vector<RadxSweep *> _sweeps;

  // global attributes

  string _command_line_attr;
  string _process_version_attr;
  string _ingest_software_attr;
  string _dod_version_attr;
  string _site_id_attr;
  string _facility_id_attr;
  string _data_level_attr;
  string _input_source_attr;
  string _resolution_description_attr;
  string _sample_int_attr;
  string _serial_number_attr;
  string _calibration_constant_attr;
  string _averaging_int_attr;
  string _pulse_length_attr;
  string _corner_power_attr;
  string _center_freq_attr;
  string _decimation_attr;
  string _drx_gcsync_attr;
  string _drx_ncosync_attr;
  string _drx_zerorx_attr;
  string _external_clock_attr;
  string _integration_attr;
  string _resolution_setpoint_attr;
  string _radar_operating_frequency_attr;
  string _radar_wavelength_attr;
  string _pedestal_true_north_attr;
  string _nyquist_velocity_attr;
  string _nearfield_correction_description_attr;
  string _NumSpectralAverages_attr;
  string _fftlen_attr;
  string _prf_attr;
  string _StartGateDelay_attr;
  string _GateSpacing_attr;
  string _pol_mode_attr;
  string _antenna_altitude_attr;
  string _antenna_diameter_attr;
  string _elevation_correction_attr;
  string _scan_mode_attr;
  string _comment_attr;
  string _polarization_state_attr;
  string _qc_standards_version_attr;
  string _qc_method_attr;
  string _qc_comment_attr;
  string _qc_bit_1_description_attr;
  string _qc_bit_1_assessment_attr;
  string _qc_bit_2_description_attr;
  string _qc_bit_2_assessment_attr;
  string _qc_bit_3_description_attr;
  string _qc_bit_3_assessment_attr;
  string _qc_bit_4_description_attr;
  string _qc_bit_4_assessment_attr;
  string _zeb_platform_attr;
  string _history_attr;

  double _pulseLenNs;
  double _frequencyGhz;
  double _wavelengthM;
  double _nyquistMps;
  double _prfHz;
  double _antennaHtAgl;
  double _antennaDiameterInches;

  string _title;
  string _institution;
  string _references;
  string _source;
  string _history;
  string _comment;
  string _statusXml;
  
  string _siteName;
  string _scanName;
  int _scanId;
  string _instrumentName;

  int _volumeNumber;
  Radx::InstrumentType_t _instrumentType;
  Radx::PlatformType_t _platformType;
  Radx::PrimaryAxis_t _primaryAxis;

  // storing ray information for reading from file
  
  class RayInfo {
  public:
    size_t indexInFile;
    RadxSweep *sweep;
    RadxRay *ray;
  };
  vector<RayInfo> _raysToRead;

  // rays to be added to volume

  vector<RadxRay *> _raysValid;

  int _readDimensions();
  int _readGlobalAttributes();
  int _readTimes();
  int _readRangeVariable();
  int _readPositionVariables();
  int _readSweepVariables();
  void _clearRayVariables();
  int _readRayVariables();
  int _createRays(const string &path);
  int _readFieldVariables(bool metaOnly);

  int _readRayVar(Nc3Var* &var, const string &name, 
                  vector<double> &vals, bool required = true);
  int _readRayVar(Nc3Var* &var, const string &name, 
                  vector<int> &vals, bool required = true);
  
  Nc3Var* _getRayVar(const string &name, bool required);
  int _readSweepVar(Nc3Var* &var, const string &name, 
                    vector<int> &vals, bool required = true);
  Nc3Var* _getSweepVar(const string &name);

  int _addFl64FieldToRays(Nc3Var* var,
                          const string &name, const string &units,
                          const string &standardName, const string &longName,
                          bool isDiscrete, bool fieldFolds,
                          float foldLimitLower, float foldLimitUpper);
  int _addFl32FieldToRays(Nc3Var* var,
                          const string &name, const string &units,
                          const string &standardName, const string &longName,
                          bool isDiscrete, bool fieldFolds,
                          float foldLimitLower, float foldLimitUpper);

  int _loadReadVolume();
  void _computeFixedAngles();

};

#endif
