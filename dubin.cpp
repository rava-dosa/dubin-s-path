#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <limits>
#include <vector>
#define PI 3.141
using namespace std ;
//using namespace cv ;

struct pt{
	float x;
	float y;
};
struct pt1{
	float x;
	float y;
	float m;
};

typedef struct pt pt;

struct Stheta{
	float start;
	float end;
};
typedef struct Stheta Stheta;

float length( float a,float b,float c,float d)
{
	float l1=sqrt(((float)a-c)*((float)a-c) + ((float)b-d)*((float)b-d)); 
	return l1;
}

float qcheck(pt a,pt b)
{
	float c,d;
	c=b.x-a.x;
	d=b.y-a.y;
	if(c>0&&d>0)
	{
//   printf("CHU\n");
		
		return 1;
	}
	if(c<0&&d>0)
	{
		return 2;
	}
    if(c<0&&d<0)
	{
		return 3;
	}
    if(c>0&&d<0)
	{
		return 4;
	}

}
float thetacalc(float theta1,float theta2,float quad)
{
    float theta3;
    if(theta1>0)
    {
    	theta3=90-theta1 + theta2 ;
    	//printf("%f\n",theta3 );
    	return theta3;
    }
    if(theta1<0)
    {
       theta3=90+theta1-theta2 ;
       return theta3;
    }
    
}
pt findpointS(pt centreS,float theta,float rad,float quad)
{
	int e,f;
	pt S;
	if(quad==1)
	{   
		float l=rad;
		e=1;
		f=1;
		S.x=centreS.x+e*l*cos(theta);
		S.y=centreS.y+f*l*sin(theta);
		//printf("%f\n",S.x );
		return S;

	}
}


pt findpointE(pt a,float theta,float rad,float quad)
{
	int e,f;
	pt S;
	if(quad==1)
	{   float l=rad;
		e=1;
		f=1;
		S.x=a.x+e*l*cos(theta);
		S.y=a.y-f*l*sin(theta);
		//printf("%f\n",S.x );
		return S;

	}
}

float theta(float a,float b)
{
	
  float result,param;
  param =(float)a/b;
  result = atan (param) * 180 / PI;
		//printf("%f\n",result);

  return result;
}

pt1 markerupdate(pt a,pt c)
{   pt1 d;
    printf("mu%f\n",a.x );
    printf("mu%f\n",c.x );

	if(a.x>c.x)
	{
       d.x=a.x;
       d.y=a.y;
       d.m=1;
	}
	else{
       d.x=a.x;
       d.y=a.y;
       d.m=0;
	}
	
	return d;
}

float pathtype(pt1 a,float quad)
{   //printf("CHU\n");
    if (quad==1&&a.m==0)
    {
    	float b=213;
    	//printf("VGF%f\n",b );
    	return b;
    }
}
int cw( pt p0, pt p1, pt p2 )
{
	int dx1, dx2, dy1, dy2;
	
	dx1 = p1.x - p0.x; dy1 = p1.y - p0.y;
	dx2 = p2.x - p0.x; dy2 = p2.y - p0.y;
	
	if (dx1*dy2 > dy1*dx2)
		return -1;
	if (dx1*dy2 < dy1*dx2)
		return +1;
	if ((dx1*dx2 < 0) || (dy1*dy2 < 0))
		return +1;
	if ((dx1*dx1 + dy1*dy1) < (dx2*dx2 + dy2*dy2))
		return -1;
	return 0;
}


float pathlength(pt a,pt b,pt start,pt end,pt centreS,pt centreE,float l,float rad,float param)
{
    printf("%f\n",a.x );
    printf("%f\n",a.y );
    printf("%f\n",b.x );
    printf("%f\n",b.y );
    printf("%f\n",centreS.x );
    printf("%f\n",centreS.y );
    printf("%f\n",centreE.x);
    printf("%f\n",centreE.y);
    printf("%f\n",start.x );
    printf("%f\n",start.y );
    float l1=(float)(length(a.x,a.y,start.x,start.y)/2);
    printf("%f\n",l1 );
    float l2=(float)(sqrt(rad*rad-l1*l1));
    printf("%f\n",l2 );
    float fi=2*theta(l1,l2);
    printf("hiiiii%f\n",fi );
    int n[3];
    n[2]=(int)param%10;
    param=param/10;
    n[1]=(int)param%10;
    param/10;
    n[0]=(int)param;
    int param1=cw( a,start, centreS);
    int param2=cw( b, end, centreE);
    if(n[0]==2&&param1==1)
    {
    	fi=(360-fi)/180*PI;
    	fi=fi*rad;

    }
    if(n[0]==2&&param1==-1){
    	fi=fi/180*PI;
    	fi=fi*rad;
    }
    float fi1;
    l1=(float)(length(b.x,b.y,end.x,end.y)/2);
    l2=(float)(sqrt(rad*rad-l1*l1));

     fi1=2*theta(l1,l2);

    if(n[2]==3&&param2==-1)
    {
        fi1=fi1/180*PI;
    	fi1=fi1*rad;
    }
    if(n[2]==3&&param2==1)
    {
    	fi1=(360-fi)/180*PI;
    	fi1=fi1*rad;

    }
    float length=2*l + fi + fi1 ;
    return length;

}


class dubin{
public:
	float csc(pt start,pt end,Stheta fi,float radius)
	{
		pt centreS;
		pt centreE;
		pt mp;
		float l1;
		centreS.x=start.x-radius*cos(90-fi.start);
		centreS.y=start.y+radius*sin(90+fi.start);
		centreE.x=end.x-radius*cos(90-fi.end);
		centreE.y=end.y+radius*sin(90+fi.end);
		mp.x=(float)((centreS.x + centreE.x)/2);
		mp.y=(float)((centreS.y + centreE.y)/2);
		l1=length(centreS.x,centreS.y,mp.x,mp.y);
		float a=(float)(sqrt(l1*l1-radius*radius));
        float angle=theta(radius,a);
        float angle1=theta(centreE.y-centreS.y,centreE.x-centreS.x);

        float param=qcheck( centreS,centreE);
        //
         angle=thetacalc(angle,angle1,param);
        pt X = findpointS( centreS,angle,radius,param);
        pt Y = findpointS( centreE,angle,radius,param);
        pt1 a1=markerupdate( X, centreS);
        pt1 b1=markerupdate( Y, centreE);
    printf("marker%f\n",a1.m );

        float f=pathtype( a1,param);
        printf("%f\n",f);
        float length1=pathlength(X,Y,start,end,centreS,centreE,l1,radius,f);
        printf("Answer%f",length1);
        printf("hello");


	}
};

	int main()
	{
		pt start,end;
		Stheta fi;
		float radius=1;
		start.x=0;
		start.y=2;
		end.x=25;
		end.y=25;
		fi.start=30;
		fi.end=30;
		dubin check;
		float y=check.csc(start,end,fi,radius);
        //printf("%f\n",y);
        

	}