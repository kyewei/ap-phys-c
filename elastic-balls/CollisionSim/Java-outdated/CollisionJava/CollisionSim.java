// The "CollisionSim" class.
import java.awt.*;
import hsa.Console;

public class CollisionSim
{
    static Console c;

    public static Ball[] balls;
    public static double deltaTime;

    public static void main (String[] args)
    {
	c = new Console ();

	balls = new Ball [2];
	balls [0] = new Ball (250, 200, 10, 10, 1000);
	balls [1] = new Ball (350, 200, 10, 10, 1000);

	/*for (int i = 2 ; i < 10 ; i++)
	{
	    int xcoord = (int) (Math.random () * (c.getWidth ()) + 1);
	    int ycoord = (int) (Math.random () * (c.getHeight ()) + 1);
	    balls [i] = new Ball (xcoord, ycoord, 10, 10, 200);
	}*/


	deltaTime = 0.05;

	draw ();
	move ();
    }


    public static void draw ()
    {
	c.clear ();

	for (int i = 0 ; i < balls.length ; i++)
	{
	    int aa = (int) Math.round (balls [i].sx - balls [i].radius);
	    int ab = (int) Math.round (balls [i].sy - balls [i].radius);
	    ab = c.getHeight () - ab;  // coordinatewise, +y is down
	    int ac = (int) Math.round (2 * balls [i].radius);
	    int ad = (int) Math.round (2 * balls [i].radius);
	    c.drawOval (aa, ab, ac, ad);
	}
    }


    public static void move ()
    {
	double time = 0;
	double overlap;
	double direction;
	while (true)
	{
	    //forces go here
	    
	    if (time >= 0 && time < 1)
	    {
		applyForce (200, 0, balls [0]);
		applyForce (200, Math.PI, balls [1]);

	    }
	    

	    /*for (int i = 0 ; i < balls.length ; i++)
	    {
		double force = Math.random () * 200 + 1;
		double angle = Math.random () * 2 * Math.PI;
		applyForce (force, angle, balls [i]);

	    }*/

	    for (int i = 0 ; i < balls.length ; i++)
		for (int j = 0 ; j < balls.length ; j++)
		{
		    if (i != j)
		    {
			overlap = overlapper (balls [i], balls [j]);
			if (overlap >= 0)
			{
			    direction = Math.atan ((balls [i].sy - balls [j].sy) / (balls [i].sx - balls [j].sx));
			    if (balls [i].sx >= balls [j].sx)
			    {
			    }
			    else
				direction += Math.PI;
			    applyForce (balls [i].kvalue * overlap, direction, balls [i]);

			}

		    }

		}


	    // Wall bounces
	    for (int i = 0 ; i < balls.length ; i++)
	    {
		if (balls [i].sx < 0)
		    applyForce (balls [i].kvalue * (0 - balls [i].sx), 0, balls [i]);
		if (balls [i].sy < 0)
		    applyForce (balls [i].kvalue * (0 - balls [i].sy), Math.PI / 2, balls [i]);
		if (balls [i].sx > c.getWidth ())
		    applyForce (balls [i].kvalue * (balls [i].sx - c.getWidth ()), -Math.PI, balls [i]);
		if (balls [i].sy > c.getHeight ())
		    applyForce (balls [i].kvalue * (balls [i].sy - c.getHeight ()), -Math.PI / 2, balls [i]);



	    }


	    //final force calculations

	    for (int i = 0 ; i < balls.length ; i++)
	    {
		balls [i].vx += balls [i].ax * deltaTime;
		balls [i].vy += balls [i].ay * deltaTime;
		balls [i].sx += balls [i].vx * deltaTime;
		balls [i].sy += balls [i].vy * deltaTime;

		//System.out.print ("Ball" + i + " Vx, Vy, |V|: ");
		//System.out.print ("" + Math.round (balls [i].vx * 100.0) / 100.0 + " | " + Math.round (balls [i].vy * 100.0) / 100.0 + " | ");
		//System.out.println ("" + Math.round (Math.sqrt (balls [i].vx * balls [i].vx + balls [i].vy * balls [i].vy) * 100.0) / 100.0 + "");

		//Reset acceleration per deltaT
		balls [i].ax = 0;
		balls [i].ay = 0;
	    }


	    //System.out.println ("\n");
	    time = time + deltaTime;
	    draw ();
	    /*
	    try
	    {
		Thread.sleep (10);
	    }
	    catch (InterruptedException ie)
	    {
	    }*/

	}
    }


    public static void applyForce (double newtons, double angle, Ball thisBall)
    {
	thisBall.ax = newtons * Math.cos (angle) / thisBall.mass;
	thisBall.ay = newtons * Math.sin (angle) / thisBall.mass;
    }


    public static double overlapper (Ball ball1, Ball ball2)
    {

	return -(Math.sqrt ((ball1.sx - ball2.sx) * (ball1.sx - ball2.sx) + (ball1.sy - ball2.sy) * (ball1.sy - ball2.sy)) - (ball1.radius + ball2.radius));

    }
}


class Ball
{
    double ax;
    double ay;
    double vx;
    double vy;
    double sx;
    double sy;
    double mass;
    double radius;
    double kvalue;

    public Ball (double xpos, double ypos, double m, double r, double spring)
    {
	sx = xpos;
	sy = ypos;
	mass = m;
	radius = r;
	kvalue = spring;
    }
}


