#include "main.h"

using namespace pros;

void PID_get_Angle(int desire_turn_in_deg){
  
  //make loop running
  bool run = true;

  //my PD values 
  float turn_kP = 1.5;
  float turn_kD = 0.012;

  //error(delta in degrees from current and desire heading)
  int alpha_error = 0;
  int gama_error = 0;
  int turn_error = 0;

  //direction - negative to left and positive to right
  int direction = 0;

  //delta between current and previous error
  int turn_derivative = 0;

  //previous error
  int prev_turn_error = 0;

  //power to the motors
  float turn_power = 0;
  
  while (run){

    //potential
    alpha_error  = desire_turn_in_deg - (int)inertial.get_heading();
    gama_error   = desire_turn_in_deg - (int)inertial.get_heading() - 360;

    if(abs(alpha_error) < abs(gama_error)){
      
      turn_error = abs(alpha_error);
      if (alpha_error<0)
      {
        direction= -1;
      }
      else{
        direction = 1;
      }
      
    }

    else{

      turn_error = abs(gama_error);
      if (gama_error<0)
      {
        direction= -1;
      }
      else{
        direction = 1;
      }
    }

    //derivative calculating 
    turn_derivative = turn_error - prev_turn_error;
    prev_turn_error = turn_error;
    

    //calulating the turn power
    turn_power = (turn_error * turn_kP + turn_derivative * turn_kD);

    //set the power
    if(turn_power>100){
      turn_power = 100;
    }

    
    //set the motors to move
    fl.move_velocity(turn_power*direction);
    bl.move_velocity(turn_power*direction);
    fr.move_velocity(-turn_power*direction);
    br.move_velocity(-turn_power*direction); 

    //end the loop when the robot have disired heading 
    if (turn_error <= 0){
      run = false;
    }
    
    //printing values
    //lcd::print(5, "power:%f, error:%d", turn_power, turn_error);
    lcd::print(6, "ang:%d", (int)inertial.get_heading());

    delay(20);
   
    }

  //set brake mode 
  fl.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  bl.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  fr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  br.set_brake_mode(E_MOTOR_BRAKE_HOLD);

  // delay(2000);
  // lcd::print(6, "ang:%d", (int)inertial.get_heading());

}