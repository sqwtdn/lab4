#ifndef GEOMETRYSIZE_HH
#define GEOMETRYSIZE_HH

#include "G4SystemOfUnits.hh"

const double detector_side_size = 0.5*m;
const double detector_length = 2*m;

const double calorimeter_lead_thickness = 1*cm;
const double calorimeter_plastic_thickness = 5*cm;

const int calorimeter_number_of_segment = 8;
const int number_of_tracking_cell = 10;
const int full_number_of_tracking_cell = number_of_tracking_cell*number_of_tracking_cell;

const double tracking_cell_size = 0.05*m;
const double tracking_thickness = 0.5*mm;

const double distance_tracking_layer = 0.1*m;
const double distance_tracking_area = 0.2*m;
const double distance_tracking_center = 0.2*m;
const double distance_tracking_calorimeter = 0.1*m;

#endif