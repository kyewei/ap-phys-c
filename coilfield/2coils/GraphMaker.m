clc
set(0, 'DefaultFigureRenderer', 'OpenGL');
interval = 0.01;
interval2 = 25;
[X Y Z] = meshgrid(0:interval:0.24,0:interval:0.24,0:interval:0.24);
[U V W] = meshgrid(0:interval:0.24,0:interval:0.24,0:interval:0.24);
count = 1;
for a=1:1:interval2;
for b=1:1:interval2;
for c=1:1:interval2;
U(b,a,c)=VarName4(count);
V(b,a,c)=VarName5(count);
W(b,a,c)=VarName6(count);
count = count+1;
end
end
end

w=2*pi*10/0.022; %actual f=320 %
t=0:0.000001:0.022;
x1=R*cos(w*t)+0.1;
y1=R*sin(w*t)+0.1;
z1=t+0.03;
x2=-t+0.192;
y2=R*sin(w*t)+0.1;
z2=R*cos(w*t)+0.1;

plot3(x1,y1,z1);
hold on;
plot3(x2,y2,z2);

quiver3(X,Y,Z,U,V,W,4);
%quiver3(VarName1,VarName2,VarName3,VarName4,VarName5,VarName6,6);
hold off;
axis ([0 0.24 0 0.24 0 0.24]);
pbaspect ([1 1 1]);
daspect ([1 1 1]);
set(gcf,'color','w');

hold on
wa=2*pi*1;
t=0.125:0.125:1;
x3=0.08*cos(wa*t)+0.10;
y3=0.08*sin(wa*t)+0.10;
z3=-0.00*ones(size(x3));

t=0:0.25:0.75;
x4=0.01*cos(wa*t)+0.10;
y4=0.01*sin(wa*t)+0.10;
z4=-0.00*ones(size(x4));

t=0.125:0.125:1;
y5=0.05*sin(w*t)+0.1;
z5=0.05*cos(w*t)+0.1;
x5=0.232*ones(size(y5));

t=0:0.25:0.75;
y6=0.01*sin(w*t)+0.1;
z6=0.01*cos(w*t)+0.1;
x6=0.212*ones(size(y6));

streamline(X,Y,Z,U,V,W,x3,y3,z3)
streamline(X,Y,Z,U,V,W,x4,y4,z4)
streamline(X,Y,Z,U,V,W,x5,y5,z5)
streamline(X,Y,Z,U,V,W,x6,y6,z6)
hold off
