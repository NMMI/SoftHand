// ----------------------------------------------------------------------------
// BSD 3-Clause License

// Copyright (c) 2016, qbrobotics
// Copyright (c) 2017, Centro "E.Piaggio"
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------

/**
* \file         globals.h
*
* \brief        Global definitions and macros are set in this file.
* \date         October 01, 2017
* \author       _Centro "E.Piaggio"_
* \copyright    (C) 2012-2016 qbrobotics. All rights reserved.
* \copyright    (C) 2017 Centro "E.Piaggio". All rights reserved.
*
*/

#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
// -----------------------------------------------------------------------------

//=================================================================     includes
#include <device.h>
#include "stdlib.h"
#include "math.h"
#include "commands.h"

//==============================================================================
//                                                                        DEVICE
//==============================================================================

#define VERSION                 "SH-PRO v6.1.8 Centro Piaggio R2023"

#define NUM_OF_MOTORS           2       /*!< Number of motors.*/
#define NUM_OF_SENSORS          3       /*!< Number of encoders.*/
#define NUM_OF_EMGS             2       /*!< Number of emg channels.*/
#define NUM_OF_ANALOG_INPUTS    4       /*!< Total number of analogic inputs.*/
#define NUM_OF_PARAMS           28      /*!< Number of parameters saved in the EEPROM.*/

//==============================================================================
//                                                               SYNCHRONIZATION
//==============================================================================

//Main frequency 1000 Hz
#define CALIBRATION_DIV         10      /*!< Frequency divisor for hand calibration (100Hz).*/
#define DIV_INIT_VALUE          1       /*!< Initial value for hand counter calibration.*/

//==============================================================================
//                                                                           DMA
//==============================================================================
    
#define DMA_BYTES_PER_BURST 2
#define DMA_REQUEST_PER_BURST 1
#define DMA_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_DST_BASE (CYDEV_SRAM_BASE)
    
//==============================================================================
//                                                                     INTERRUPT
//==============================================================================

#define    WAIT_START   0               /*!< Package start waiting status.*/
#define    WAIT_ID      1               /*!< Package ID waiting status.*/
#define    WAIT_LENGTH  2               /*!< Package lenght waiting status.*/
#define    RECEIVE      3               /*!< Package data receiving status.*/
#define    UNLOAD       4               /*!< Package data flush status.*/

//==============================================================================
//                                                                 CYCLE COUNTER
//==============================================================================
        
#define STATE_INACTIVE  0               /*!< Open SoftHand position / EMG Inactive.*/
#define STATE_ACTIVE    1               /*!< Closed SoftHand position / EMG Active.*/
#define COUNTER_INC     2               /*!< Counter cycle increment.*/
    
//==============================================================================
//                                                                         OTHER
//==============================================================================

#define FALSE                   0
#define TRUE                    1

#define DEFAULT_EEPROM_DISPLACEMENT 50   /*!< Number of pages occupied by the EEPROM.*/
#define EEPROM_BYTES_ROW        16      /*!< EEPROM number of bytes per row.*/
#define EEPROM_COUNTERS_ROWS    5       /*!< EEPROM number of rows dedicated to store counters.*/
    
#define MAX_WATCHDOG_TIMER      250     /*!< num * 2 [cs].*/

#define PWM_MAX_VALUE           100     /*!< Maximum value of the PWM signal.*/

#define ANTI_WINDUP             1000    /*!< Anti windup saturation.*/ 
#define DEFAULT_CURRENT_LIMIT   1500    /*!< Default Current limit, 0 stands for unlimited.*/

#define CURRENT_HYSTERESIS      10      /*!< milliAmperes of hysteresis for current control.*/

#define EMG_SAMPLE_TO_DISCARD   500     /*!< Number of sample to discard before calibration.*/
#define SAMPLES_FOR_MEAN        100     /*!< Number of samples used to mean current values.*/
#define SAMPLES_FOR_EMG_MEAN    1000    /*!< Number of samples used to mean emg values.*/
#define REST_POS_ERR_THR_GAIN   10      /*!< Gain related to stop condition threshold in rest position routine.*/
#define CALIB_DECIMATION        1
#define NUM_OF_CLOSURES         5

#define POS_INTEGRAL_SAT_LIMIT  50000000    /*!< Anti windup on position control.*/
#define CURR_INTEGRAL_SAT_LIMIT 100000      /*!< Anti windup on current control.*/

#define MIN_CURR_SAT_LIMIT      30

#define LOOKUP_DIM              6           /*!< Dimension of the current lookup table.*/

//==============================================================================
//                                                        structures definitions
//==============================================================================

//=========================================================     motor references
/** \brief Motor Reference structure
 * 
**/
struct st_ref {
    int32 pos[NUM_OF_MOTORS];       /*!< Motor position reference.*/
    int32 curr[NUM_OF_MOTORS];      /*!< Motor current reference.*/
    int32 pwm[NUM_OF_MOTORS];       /*!< Motor direct pwm control.*/
    uint8 onoff;                    /*!< Motor drivers enable.*/
    int32 curr_offset;              /*!< Current offset used in CURR_AND_POS_CONTROL.*/
};

//=============================================================     measurements
/** \brief Measurements structure
 * 
**/
struct st_meas {
    int32 pos[NUM_OF_SENSORS];      /*!< Encoder sensor position.*/
    int32 curr[NUM_OF_MOTORS];      /*!< Motor current and current estimation.*/
    int8 rot[NUM_OF_SENSORS];       /*!< Encoder sensor rotations.*/

    int32 emg[NUM_OF_EMGS];         /*!< EMG sensors values.*/
    int32 vel[NUM_OF_SENSORS];      /*!< Encoder rotational velocity.*/
    int32 acc[NUM_OF_SENSORS];      /*!< Encoder rotational acceleration.*/
};

//==============================================================     data packet
/** \brief Data sent/received structure
 *
**/
struct st_data {
    uint8   buffer[128];            /*!< Data buffer [CMD | DATA | CHECKSUM].*/
    int16   length;                 /*!< Data buffer length.*/
    int16   ind;                    /*!< Data buffer index.*/
    uint8   ready;                  /*!< Data buffer flag to see if the data is ready.*/
};

//============================================     settings stored on the memory
/** \brief EEPROM stored structure
 * 
**/
struct st_mem {
    uint8   flag;                       /*!< If checked the device has been configured.*/                   //1
    uint8   id;                         /*!< Device id.*/                                                   //1

    int32   k_p;                        /*!< Position controller proportional constant.*/                   //4
    int32   k_i;                        /*!< Position controller integrative constant.*/                    //4
    int32   k_d;                        /*!< Position controller derivative constant.*/                     //4

    int32   k_p_c;                      /*!< Current controller proportional constant.*/                    //4
    int32   k_i_c;                      /*!< Current controller integrative constant.*/                     //4
    int32   k_d_c;                      /*!< Current controller derivative constant.*/                      //4 26

    int32   k_p_dl;                     /*!< Double loop position controller prop. constant.*/              //4
    int32   k_i_dl;                     /*!< Double loop position controller integr. constant.*/            //4
    int32   k_d_dl;                     /*!< Double loop position controller deriv. constant.*/             //4
    int32   k_p_c_dl;                   /*!< Double loop current controller prop. constant.*/               //4
    int32   k_i_c_dl;                   /*!< Double loop current controller integr. constant.*/             //4
    int32   k_d_c_dl;                   /*!< Double loop current controller deriv. constant.*/              //4 24
    
    uint8   activ;                      /*!< Startup activation.*/                                          //1
    uint8   input_mode;                 /*!< Motor Input mode.*/                                            //1
    uint8   control_mode;               /*!< Motor Control mode.*/                                          //1

    uint8   res[NUM_OF_SENSORS];        /*!< Angle resolution.*/                                            //3
    int32   m_off[NUM_OF_SENSORS];      /*!< Measurement offset.*/                                          //12
    float   m_mult[NUM_OF_SENSORS];     /*!< Measurement multiplier.*/                                      //12 30

    uint8   pos_lim_flag;               /*!< Position limit active/inactive.*/                              //1
    int32   pos_lim_inf[NUM_OF_MOTORS]; /*!< Inferior position limit for motors.*/                          //8
    int32   pos_lim_sup[NUM_OF_MOTORS]; /*!< Superior position limit for motors.*/                          //8

    int32   max_step_pos;               /*!< Maximum number of steps per cycle for positive positions.*/    //4
    int32   max_step_neg;               /*!< Maximum number of steps per cycle for negative positions.*/    //4 25

    int16   current_limit;              /*!< Limit for absorbed current.*/                                  //2

    uint16  emg_threshold[NUM_OF_EMGS]; /*!< Minimum value for activation of EMG control.*/                 //4

    uint8   emg_calibration_flag;       /*!< Enable emg calibration on startup.*/                           //1
    // End of row seven.
    uint32  emg_max_value[NUM_OF_EMGS]; /*!< Maximum value for EMG.*/                                       //8

    uint8   emg_speed;                  /*!< Maximum closure speed when using EMG.*/                        //1

    uint8   double_encoder_on_off;      /*!< Double encoder ON/OFF.*/                                       //1

    int8    motor_handle_ratio;         /*!< Discrete multiplier for handle device.*/                       //1 

    uint8   activate_pwm_rescaling;     /*!< Activation of PWM rescaling for 12V motors.*/                  //1 19

    float   curr_lookup[LOOKUP_DIM];    /*!< Table of values to get estimated curr.*/                       //24
    // End of row eight. curr_lookup[0] is on row eight, while others are on row nine and curr_lookup[5] is on row ten.
    uint8   baud_rate;                  /*!< Baud Rate setted.*/                                            //1
    uint8   watchdog_period;            /*!< Watchdog period setted, 255 = disable.*/                       //1

    int32   rest_pos;                   /*!< Hand rest position while in EMG mode.*/                        //4
    int32   rest_delay;                 /*!< Hand rest position delay while in EMG mode.*/                  //4
    int32   rest_vel;                   /*!< Hand velocity closure for rest position reaching.*/            //4
    // End of row ten. rest_vel is half on row ten and half on row eleven.
    uint8   maint_day;                  /*!< Day of maintenance.*/                                          //1
    uint8   maint_month;                /*!< Month of maintenance.*/                                        //1
    uint8   maint_year;                 /*!< Year of maintenance.*/                                         //1
    uint8   switch_emg;                 /*!< EMG opening/closure switch.*/                                  //1
    uint8   rest_position_flag;         /*!< Enable rest position feature.*/                                        //1    
    uint8   unused_bytes[9];
    // End of row eleven.
    
    uint32  emg_counter[2];             /*!< Counter for EMG activation - both channels.*/                  //8
    uint32  position_hist[10];          /*!< Positions histogram - 10 zones.*/                              //40
    uint32  current_hist[4];            /*!< Current histogram - 4 zones.*/                                 //16
    uint32  rest_counter;               /*!< Counter for rest position occurrences.*/                       //4
    uint32  wire_disp;                  /*!< Counter for total wire displacement measurement.*/             //4
    uint32  total_time_on;              /*!< Total time of system power (in seconds).*/                     //4
    uint32  total_time_rest;            /*!< Total time of system while rest position is maintained.*/      //4
                                                                                         //TOT           150 bytes
};

//=================================================     device related variables
/** \brief Device related structure
 *
**/ 
struct st_dev{
    int32   tension;                /*!< Power supply tension.*/
    float   tension_conv_factor;    /*!< Used to calculate input tension.*/
    int8    pwm_limit;              /*!< Limit on pwm value driven to the motor.*/
    uint8   tension_valid;          /*!< Flag checked if the power supply has a valid value.*/
};


//==============================================     hand calibration parameters
/** \brief Hand calibration structure
 *
**/ 
struct st_calib {
    uint8   enabled;                /*!< Calibration enabling flag.*/
    uint8   direction;              /*!< Direction of motor winding.*/
    int16   speed;                  /*!< Speed of hand opening/closing.*/
    int16   repetitions;            /*!< Number of cycles of hand closing/opening.*/
};

//=================================================     emg status
typedef enum {

    NORMAL        = 0,              /*!< Normal execution */
    RESET         = 1,              /*!< Reset analog measurements */
    DISCARD       = 2,              /*!< Discard first samples to obtain a correct value */
    SUM_AND_MEAN  = 3,              /*!< Sum and mean a definite value of samples*/
    WAIT          = 4,              /*!< The second emg waits until the first emg has a valid value */
    WAIT_EoC      = 5               /*!< The second emg waits for end of calibration */

} emg_status;                       /*!< EMG status enumeration */

typedef enum {
    
    PREPARE_DATA    = 0,            /*!< Prepare data to be written on EEPROM.*/
    WRITE_CYCLES    = 1,            /*!< Cycles writing on EEPROM is enabled and control is passed to query.*/
    WAIT_QUERY      = 2,            /*!< Wait until EEPROM_Query() has finished writing on EEPROM and then disable cycles writing.*/
    WRITE_END       = 3,            /*!< End of EEPROM writing.*/
    NONE            = 4             /*!< Cycles writing on EEPROM is disabled.*/
} counter_status;                   /*!< Cycles counter state machine status.*/ 

//====================================      external global variables definition

extern struct st_ref    g_ref, g_refNew, g_refOld;  /*!< Reference variables.*/
extern struct st_meas   g_meas, g_measOld;          /*!< Measurements.*/
extern struct st_data   g_rx;                       /*!< Incoming/Outcoming data.*/
extern struct st_mem    g_mem, c_mem;               /*!< Memory parameters.*/
extern struct st_calib  calib;						/*!< Calibration variables.*/

extern uint32 timer_value;                          /*!< End time of the firmware main loop.*/
extern uint32 timer_value0;                         /*!< Start time of the firmware main loop.*/
extern float cycle_time;							/*!< Variable used to calculate how much time a cycle takes.*/

// Device Data

extern int32    dev_tension;                        /*!< Power supply tension */
extern uint8    dev_pwm_sat;                        /*!< Device pwm limit saturation */
extern uint8    dev_pwm_limit;                      /*!< Device pwm limit */
extern int32    dev_tension_f;                      /*!< Filtered power supply tension */
extern int32    pow_tension;						/*!< Computed power supply tension.*/

// Bit Flag

extern CYBIT reset_last_value_flag;                 /*!< This flag is set when the encoders last values must be resetted.*/
extern CYBIT tension_valid;                         /*!< Tension validation bit.*/
extern CYBIT interrupt_flag;                        /*!< Interrupt flag enabler.*/
extern CYBIT watchdog_flag;                         /*!< Watchdog flag enabler.*/
extern float tau_feedback;                          /*!< Torque feedback.*/
extern CYBIT cycles_interrupt_flag;                 /*!< Cycles timer interrupt flag enabler.*/
extern CYBIT can_write;                             /*!< Write to EEPROM flag.*/
extern uint8 rest_enabled;                          /*!< Rest position flag.*/
extern uint8 forced_open;                           /*!< Forced open flag (used in position with rest position control).*/
extern counter_status CYDATA cycles_status;         /*!< Cycles counter state machine status.*/
extern emg_status CYDATA emg_1_status;              /*!< First EMG sensor status.*/
extern emg_status CYDATA emg_2_status;              /*!< Second EMG sensor status.*/ 

// DMA Buffer

extern int16 ADC_buf[4];                            /*! ADC measurements buffer.*/

// PWM value

extern int8 pwm_sign;                               /*!< Sign of pwm driven. Used to obtain current sign.*/

extern int32 rest_pos_curr_ref;						/*!< Rest position current reference.*/


// -----------------------------------------------------------------------------


#endif

//[] END OF FILE