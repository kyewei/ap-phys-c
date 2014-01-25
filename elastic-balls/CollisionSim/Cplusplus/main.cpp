#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

struct Vector2D{ // Simple vector struct
       double x;
       double y;       
};

class Ball
{
    public:
           Ball (double xpos, double ypos, double m, double r, double spring)
           {
                //Assign ball positions, velocities, mass, radius, spring
                s.x = xpos;
                s.y = ypos;
                v.x = 0;
                v.y = 0;
                a.x = 0;
                a.y = 0;
                mass = m;
                radius = r;
                kvalue = spring;
                moment = 2*mass*radius*radius/5;
                angle = 0;
                omega = 0;
                alpha = 0;
           }
           Ball() //Default constructor
           {
                s.x = 0;
                s.y = 0;
                v.x = 0;
                v.y = 0;
                a.x = 0;
                a.y = 0;
                mass = 0;
                radius = 0;
                kvalue = 0;
                moment = 0;
                angle = 0;
                omega = 0;
                alpha = 0;
           }
           
           //Kinematic values, and ball properties
           struct Vector2D a;
           struct Vector2D v;
           struct Vector2D s;
           double angle; //angular distance, CCW is positive
           double omega; //angular velocity
           double alpha; //angular acceleration
           double mass;
           double radius;
           double kvalue;
           double moment; //moment of inertia I=(2/5)MR^2
           
           //Applies a force to this ball, taking into account components and mass
           void applyForce (double newtons, double angle){
                a.x = newtons * cos (angle) / mass;
                a.y = newtons * sin (angle) / mass;
           }
           
           //Apply angular acceleration through torque
           void applyTorque (double newtons, double angle){       
                double torque = newtons * radius*cos(angle);
                alpha = torque/moment;
           }
};

//Method to check for collisions by seeing if overlaps exist
//Equivalent to Radiuses - SQRT((deltaX)^2 + (deltaY)^2) 
double ifOverlap (Ball *ball1, Ball *ball2)
{
       return ((ball2->radius + ball1->radius) -(sqrt (pow(ball2->s.x - ball1->s.x, 2) + pow(ball2->s.y - ball1->s.y, 2))));
}

//Finds angle from center of ball 1 to ball 2, to find direction of spring force
double forceDirection (Ball *ball1, Ball *ball2)
{
       //atan2() was used to be able to get values from -Pi to Pi, while atan() 
       //only got values from -Pi/2 to Pi/2, which has ambiguity for 2 quadrants
       return (atan2 (ball1->s.y - ball2->s.y, ball1->s.x - ball2->s.x));
}


int main(int argc, char *argv[])
{
    //Constant variables
    const double pi = 3.1415926535897;
    
    //Ask user for ball values
    printf("How many balls to simulate: ");
    int ballCount;
    scanf("%d", &ballCount);
    
    //Create the ball objects with user details
    Ball *balls[ballCount];
    for (int i = 0; i <ballCount; i++)
    {
        double xpos, ypos, mass, radius, spring, vx, vy;
        
        //Asks for ball information
        printf("\nBall %d\nXposition: ", i+1);
        scanf("%lf", &xpos);
        printf("Yposition: ");
        scanf("%lf", &ypos);
        printf("Mass: ");
        scanf("%lf", &mass);
        printf("Radius: ");
        scanf("%lf", &radius);
        printf("SpringConstant: ");
        scanf("%lf", &spring);
        
        // xpos, ypos, mass, radius, springconstant
        balls[i] = new Ball(xpos, ypos, mass, radius, spring);  
        
        //Asks for initial velocity information
        printf("XVelocity: ");
        scanf("%lf", &vx);
        printf("YVelocity: ");
        scanf("%lf", &vy);
       
        //Sets velocities
        balls[i]->v.x = vx ;
        balls[i]->v.y = vy;
        
        printf("\n");
    }
    
    /*balls[0] = new Ball(100, 100, 1, 2, 1153); 
    balls[1] = new Ball(110, 103.464, 1, 2, 1153);  */

    // The velocities is computed 100 times per second
    double deltaTime = 0.01; 
    double time = 0;
    double overlap;
    double direction; 
   
    /*balls[0]->v.x = 2.2;
    balls[1]->v.x = 0;*/
   
    //The simulation runs for 8 seconds
    while (time<=8) 
    {
              
        //Check for collisions by making a nested for loop that 
        //compares distances from one ball to another
        for (int i = 0 ; i < ballCount ; i++)        
            for (int j = 0 ; j < ballCount ; j++)
            {
                if (i != j) // Makes sure the ball is not comparing with itself
                {
                    //Finds distance balls are from each other to check for collision
                    overlap = ifOverlap (balls [i], balls [j]); 
                    if (overlap > 0) // If there is a collision
                    {
                        //Applies spring force in the direction of incoming ball
                        direction = forceDirection (balls [i], balls[j]);
                        balls[i]->applyForce (balls [i]->kvalue * overlap, direction);
                    }
                }
            }
        
        //Computations for each ball
        for (int i = 0 ; i < ballCount; i++){
            
            //Apply accelerations and velocities to velocity and position respectively
            balls [i]->v.x += balls [i]->a.x * deltaTime;
            balls [i]->v.y += balls [i]->a.y * deltaTime;
            balls [i]->s.x += balls [i]->v.x * deltaTime;
            balls [i]->s.y += balls [i]->v.y * deltaTime;
            //Reset acceleration per deltaT
            balls [i]->a.x = 0;
            balls [i]->a.y = 0;
            
            
            //Unused Rotational Kinematics
            balls [i]->omega += balls [i]->alpha * deltaTime;
            balls [i]->angle += balls [i]->omega * deltaTime;
            //Reset angular acceleration per deltaT
            balls [i]->alpha = 0;
            
            
            //Output of neatly organized kinematic components
            //Pre-specified decimal points to display
            //2 Decimal places for time, 4 spots total
            //4 Decimal places for position, 9 spots total
            //6 Decimal places for velocity, 10 spots total
            printf("Ball %1d %4.2f %9.4f %9.4f %10.6f %10.6f \n", i+1 ,time, balls[i]->s.x, balls[i]->s.y, balls[i]->v.x, balls[i]->v.y);          
        }
        printf("\n");
        time+= deltaTime; // Increment time   
          
    }
       
    //Memory management.  
    for (int i = 0; i < ballCount; i++){
        delete balls[i];
    }
    
        
    system("PAUSE");
    return EXIT_SUCCESS;
};

