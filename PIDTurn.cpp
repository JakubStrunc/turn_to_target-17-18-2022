#include "main.h"

using namespace pros;

void PID_get_Angle(int desire_turn_in_deg){
  
  bool run = true;

  float turn_kP = 1.5;
  float turn_kD = 0.012;

  int alpha_error = 0;
  int gama_error = 0;
  int turn_error = 0;
  int direction = 0;

  int turn_derivative = 0;
  int prev_turn_error = 0;

  int total_turn_error = 0;

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

    //derivative
    turn_derivative = turn_error - prev_turn_error;
    prev_turn_error = turn_error;
    //integral 
    total_turn_error += turn_error;

    turn_power = (turn_error * turn_kP + turn_derivative * turn_kD);
    if(turn_power>100){
      turn_power = 100;
    }

    

    fl.move_velocity(turn_power*direction);
    bl.move_velocity(turn_power*direction);
    fr.move_velocity(-turn_power*direction);
    br.move_velocity(-turn_power*direction); 


    if (turn_error <= 0){
      run = false;
    }
    
    //lcd::print(5, "power:%f, error:%d", turn_power, turn_error);
    lcd::print(6, "ang:%d", (int)inertial.get_heading());

    delay(20);
   
    }


  fl.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  bl.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  fr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  br.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  delay(2000);
  lcd::print(6, "ang:%d", (int)inertial.get_heading());

}