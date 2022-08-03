# turn_to_target-17-18-2022

I want to make my robot turn to the point on the field by using odometry. This will be use in future as the part for the autoaim or get the robot position.
  For this I need:
  - PID turn or PD turn
  - find the angle, where is target located, through using trigometry(atan2).
  
  
 What I did:
 
 - For the turning, I wanted from my robot to figure out the shorter way (left or right). I made few reserches for that.
 
 
  1st source
  ![image](https://user-images.githubusercontent.com/105900658/182445820-b5db2e11-1dd5-425d-8f11-653b65a7e966.png)
  
  formulas: left   = current angle - desire angle
            right  = desire angle - current angle
           
           
 Only from one of formulas, there come the positive number. The robot will from which the positive number come.
 
 
 problem: It works perfecly to the right; however, to the left it doesnt. The problem is the left formula. Specificaly, if the current angle is smaller than desire angle, the right side will be always positive.
 
  ex. curent angle = 15 , desire angle = 270
      
     left  = 15 - 270 = -255
     right = 270 - 15 = 255     <--- It shows turn to the right side it is shorter way. However, the shorter way is turn to the left.
     
     
     
  2nd sorce
  ![image](https://user-images.githubusercontent.com/105900658/182685630-6d93ab2e-289a-44be-a426-db45ed1e8bc6.png)
  
    formulas: alpha = current angle - desire angle
              gama  = current angle - desire angle - 360
            
 the closest result in absulute value will be the distance of the shortest turn. If the result is negative the shortest way is turning to the left side. And if the result is posite the shortest way is turning right.
     
     
  
   

  
    
