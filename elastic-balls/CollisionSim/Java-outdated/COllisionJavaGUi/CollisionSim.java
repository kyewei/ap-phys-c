// The "CollisionSim" class.
import java.awt.*;
import javax.swing.*;

import hsa.Console;

public class CollisionSim extends JPanel
{
    //static Console c;

    public static Ball[] balls;
    public static double deltaTime;
    public static int WIDTH = 800;
    public static int HEIGHT = 600;
    public static JFrame frame;
    public CollisionSim ()
    {
	super ();

	setLayout (new BorderLayout ());
	add (new JPanel (), BorderLayout.CENTER);
	balls = new Ball [2];
	balls [0] = new Ball (200, 200, 10, 50, 100);
	balls [1] = new Ball (400, 200, 10, 50, 100);

	/*for (int i = 2 ; i < 10 ; i++)
	{
	    int xcoord = (int) (Math.random () * WIDTH + 1);
	    int ycoord = (int) (Math.random () * HEIGHT + 1);
	    balls [i] = new Ball (xcoord, ycoord, 10, 10, 1000);
	}*/

	deltaTime = 0.001;

	draw ();
	move ();
    }


    public static void main (String[] args)
    {
	frame = new JFrame ("CollisionSim"); // starting generation #
	frame.setSize (WIDTH, HEIGHT);
	frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
	frame.setVisible (true);

	CollisionSim panel = new CollisionSim ();

	frame.getContentPane ().add (panel);
	frame.getContentPane ().setSize (WIDTH, HEIGHT);
	frame.setResizable (true);

	frame.show ();
    }


    public void draw ()
    {
	frame.getGraphics ().clearRect (0, 0, 800, 600);
	repaint ();

	for (int i = 0 ; i < balls.length ; i++)
	{
	    int aa = (int) Math.round (balls [i].sx - balls [i].radius);
	    int ab = (int) Math.round (balls [i].sy - balls [i].radius);
	    ab = HEIGHT - ab;  // coordinatewise, +y is down
	    int ac = (int) Math.round (2 * balls [i].radius);
	    int ad = (int) Math.round (2 * balls [i].radius);
	    frame.getGraphics ().fillOval (aa, ab, ac, ad);
	}
    }


    public void move ()
    {
	double time = 0;
	double overlap;
	double direction;
	double totalenergy;
	while (true)
	{
	    //forces go here
	    
	    if (time >= 0 && time < 1)
	    {
		applyForce (800,Math.PI/4, balls [0]);
		applyForce (400, 3*Math.PI/4, balls [1]);

	    }
	    
	    /*if (time == 0)
		for (int i = 0 ; i < balls.length ; i++)
		{
		    double speedx = Math.random () * 20 + 1;
		    double speedy = Math.random () * 20 + 1;
		    balls [i].vx = speedx;
		    balls [i].vy = speedy;

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
		if (balls [i].sx < 0+50)
		    applyForce (balls [i].kvalue * (50 - balls [i].sx), 0, balls [i]);
		if (balls [i].sy < 0+50)
		    applyForce (balls [i].kvalue * (50 - balls [i].sy), Math.PI / 2, balls [i]);
		if (balls [i].sx > WIDTH-50)
		    applyForce (balls [i].kvalue * (balls [i].sx - WIDTH+50), -Math.PI, balls [i]);
		if (balls [i].sy > HEIGHT-50)
		    applyForce (balls [i].kvalue * (balls [i].sy - HEIGHT+50), -Math.PI / 2, balls [i]);
	    }


	    //final force calculations

	    for (int i = 0 ; i < balls.length ; i++)
	    {
		balls [i].vx += balls [i].ax * deltaTime;
		balls [i].vy += balls [i].ay * deltaTime;
		balls [i].sx += balls [i].vx * deltaTime;
		balls [i].sy += balls [i].vy * deltaTime;

		//Reset acceleration per deltaT
		balls [i].ax = 0;
		balls [i].ay = 0;
	    }

	    time = time + deltaTime;
	    draw ();

	    //try
	    {
		//Thread.sleep (1);
	    }
	    //catch (InterruptedException ie)
	    {
	    }


	    totalenergy = 0;
	    for (int i = 0 ; i < balls.length ; i++)
	    {
		totalenergy += balls [i].mass * 0.5 * (balls [i].vx * balls [i].vx + balls [i].vy * balls [i].vy);
	    }
	    frame.setTitle ("" + Math.round(time*100.0)/100.0 + " " + Math.round(totalenergy*100.0)/100.0 + "J");

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
