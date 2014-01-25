/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package solenoidsim;

/**
 *
 * @author Kye
 */
public class SolenoidSim {

    static double R = 0.07; //y coefficient
    static double f = 320 / 0.022; //frequency
    static double w = 2 * 3.141592 * f; //angular frequency

    public static double x(double t) {
        return R * Math.cos(w * t) + 0.10;
    }

    public static double y(double t) {
        return R * Math.sin(w * t) + 0.10;
    }

    public static double z(double t) {
        return t + 0.03;

    }

    public static double xp(double t) {
        return -w * R * Math.sin(w * t);
    }

    public static double yp(double t) {
        return w * R * Math.cos(w * t);
    }

    public static double zp(double t) {
        return 1;

    }

    public static double x2(double t) {
        return -t + 0.192;
    }

    public static double y2(double t) {
        return R * Math.sin(w * t) + 0.10;
    }

    public static double z2(double t) {
        return R * Math.cos(w * t) + 0.10;
    }

    public static double x2p(double t) {
        return -1;
    }

    public static double y2p(double t) {
        return w * R * Math.cos(w * t);
    }

    public static double z2p(double t) {
        return -w * R * Math.sin(w * t);

    }

    public static void main(String[] args) {

        //x=at, y=bcos(wt), z=csin(wt)
        //db = mu/(4 pi) * i/ r^3 * ds\vec CROSS  r\vec 
        double i = 1.5; // current
        double dt = 0.000002; //reference dt for discrete integration

        double Tstart = 0;
        double Tend = 0.022;
        double t = Tstart;
        int sizex = 24;// in cm
        int sizey = 24;// in cm
        int sizez = 24;// in cm

        int oneunit = 1;
        int twounit = 1;

        Vector3D Bvec[][][];
        Bvec = new Vector3D[sizex / oneunit * twounit + 1][sizey / oneunit * twounit + 1][sizez / oneunit * twounit + 1];

        //initialize Bvecs to zero.
        for (int arrx = 0; arrx < Bvec.length; arrx++) {
            for (int arry = 0; arry < Bvec[0].length; arry++) {
                for (int arrz = 0; arrz < Bvec[0][0].length; arrz++) {
                    Bvec[arrx][arry][arrz] = new Vector3D(0, 0, 0);
                }
            }
        }

        //double error = detaildiv / 100 * 0.99;
        while (Tstart <= t && t <= Tend) {
            for (int arrx = 0; arrx < Bvec.length; arrx++) {
                for (int arry = 0; arry < Bvec[0].length; arry++) {
                    for (int arrz = 0; arrz < Bvec[0][0].length; arrz++) {
                        //position to take field-position of ds                        
                        Vector3D Rvec;
                        Vector3D ds;
                        Vector3D dsCrossRvec;
                        Vector3D newBvec;

                        Rvec = Vector3D.Sub(new Vector3D(arrx * oneunit / twounit * 1.0 / 100, arry * oneunit / twounit * 1.0 / 100, arrz * oneunit / twounit * 1.0 / 100), new Vector3D(x(t), y(t), z(t)));
                        //ds = Vector3D.Sub(new Vector3D(x(t + dt), y(t + dt), z(t + dt)), new Vector3D(x(t), y(t), z(t)));
                        ds = Vector3D.SMultiply(dt, new Vector3D(xp(t), yp(t), zp(t)));

                        dsCrossRvec = Vector3D.Cross(ds, Rvec);
                        newBvec = Vector3D.SMultiply(0.00000125663 / 4 / 3.141592 * i / Math.pow(Vector3D.Magnitude(Rvec), 3), dsCrossRvec);

                        Bvec[arrx][arry][arrz] = Vector3D.Add(Bvec[arrx][arry][arrz], newBvec);

                        Rvec = Vector3D.Sub(new Vector3D(arrx * oneunit / twounit * 1.0 / 100, arry * oneunit / twounit * 1.0 / 100, arrz * oneunit / twounit * 1.0 / 100), new Vector3D(x2(t), y2(t), z2(t)));
                        //ds = Vector3D.Sub(new Vector3D(x2(t + dt), y2(t + dt), z2(t + dt)), new Vector3D(x2(t), y2(t), z2(t)));
                        ds = Vector3D.SMultiply(dt, new Vector3D(x2p(t), y2p(t), z2p(t)));

                        dsCrossRvec = Vector3D.Cross(ds, Rvec);
                        newBvec = Vector3D.SMultiply(0.00000125663 / 4 / 3.141592 * i / Math.pow(Vector3D.Magnitude(Rvec), 3), dsCrossRvec);

                        Bvec[arrx][arry][arrz] = Vector3D.Add(Bvec[arrx][arry][arrz], newBvec);
                    }
                }
            }
            System.out.println(t);
            t += dt;
        }

        for (int arrx = 0; arrx < Bvec.length; arrx++) {
            for (int arry = 0; arry < Bvec[0].length; arry++) {
                for (int arrz = 0; arrz < Bvec[0][0].length; arrz++) {
                    System.out.println(0.01 * arrx * oneunit / twounit + "," + 0.01 * arry * oneunit / twounit + "," + 0.01 * arrz * oneunit / twounit + "," + Bvec[arrx][arry][arrz].x + "," + Bvec[arrx][arry][arrz].y + "," + Bvec[arrx][arry][arrz].z);
                }
            }
        }
    }
}

class Vector3D {

    double x, y, z;

    Vector3D(double xpos, double ypos, double zpos) {
        x = xpos;
        y = ypos;
        z = zpos;
    }

    public static Vector3D Cross(Vector3D one, Vector3D two) {
        return new Vector3D(one.y * two.z - one.z * two.y, one.z * two.x - one.x * two.z, one.x * two.y - one.y * two.x);
    }

    public static Vector3D Add(Vector3D one, Vector3D two) {
        return new Vector3D(one.x + two.x, one.y + two.y, one.z + two.z);
    }

    public static Vector3D Sub(Vector3D one, Vector3D two) {
        return new Vector3D(one.x - two.x, one.y - two.y, one.z - two.z);
    }

    public static Vector3D SMultiply(double one, Vector3D two) {
        return new Vector3D(one * two.x, one * two.y, one * two.z);
    }

    public static double Magnitude(Vector3D one) {
        return Math.sqrt(Math.pow(one.x, 2) + Math.pow(one.y, 2) + Math.pow(one.z, 2));
    }
}
