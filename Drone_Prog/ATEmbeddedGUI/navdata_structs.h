/************************************************************************************
 * This file is the product of the work of ailab, and was taken from the webpage :  *
 * http://ardrone-ailab-u-tokyo.blogspot.fr/2012/06/12-receive-navigation-data.html *
 * Also, most of our work concerning navdata has been directly inspired by his work *
 ***********************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NAVDATA_STRUCTS_H
#define NAVDATA_STRUCTS_H

#include <netdb.h>

typedef float   float32_t;

// navdata header
typedef struct _navdata_header_t {
  uint32_t    header;                   // header:55667788 
  uint32_t    state;                    // the state of the drone 
  uint32_t    seq;                      // sequence number 
  uint32_t    vision;                   // vision flag 
} navdata_header_t;

// navdata option, demo mode
typedef struct _navdata_demo_t {
  uint16_t    id;                        // Navdata block ('option') identifier 
  uint16_t    size;                      // set this to the size of this structure 
  
  uint32_t    ctrl_state;               // Flying state (landed, flying, hovering, etc.) defined in CTRL_STATES enum. 
  uint32_t    vbat_flying_percentage;   // battery voltage filtered (mV) 
  
  float32_t   theta;                    // pitch angle in milli-degrees 
  float32_t   phi;                      // roll  angle
  float32_t   psi;                      // yaw   angle
  
  int32_t     altitude;                 // altitude in centimeters[??] 
  
  float32_t   vx;                       // estimated linear velocity
  float32_t   vy;                       // estimated linear velocity
  float32_t   vz;                       // estimated linear velocity

  uint32_t    num_frames;               //!< streamed frame index  // Not used -> To integrate in video stage.
} navdata_demo_t;

// navdata structure
typedef struct _navdata_t {
  navdata_header_t     navdata_header;  // navdata header 
  navdata_demo_t       navdata_option;  // navdata option 
} navdata_t;

// Structure containing navdata and a flag indicating if it is ready to be copied
typedef struct nav_data_type{
    navdata_demo_t nav_data;
    int is_ready ;
}nav_data_type;
#endif // NAVDATA_STRUCTS_H

#ifdef __cplusplus
}
#endif
