#include<vector>
#include<cmath>
using namespace std;

class point {
    public:
	    double x,y;
      	    point(double a, double b): x(a), y(b) {}
	    point(point p): x(p.x), y(p.y) {}
	    void rotate(double angle){
		    double x = this.x*cos(angle) - this.y*sin(angle);
		    double y = this.x*sin(angle) + this.y*cos(angle);
		    this.x = x; this.y = y;
	    }
	    point rotateCopy(double angle){
		    return point(this.x*cos(angle) - this.y*sin(angle), this.x*sin(angle) + this.y*cos(angle));
	    }
}

class line {
    public:
	    point fst,snd;
      	    line(point a, point b): x(a), y(b) : {}
	    intersection(const point &loc,const double &angle){ // either distance or 0
		//do stuff
		i
	    }
}


typedef char colors;//8 bits, R=0,G=1; the three first bits are botton, middle, top colors, the fourth is if it's empty
typedef pair<point,colors> stack;

inline int bottom(stack s){
    return (s.snd&1);
}

inline int middle(stack s){
	    return (s.snd&2)>>1;
}

inline int top(stack s){
	    return (s.snd&4)>>2;
}

inline int isOn(stack s){
	    return (s.snd&8)>>3;
}


class State{
    public:
    vector<line> walls;
    vector<line> plataforms;
    vector<stack> stacks;
    point location;
    vector<stack> stacks;
    double angle; // wrt to north, direction (0,0) -> (0,1), anticlockwise
    void setDir(double angle) { this.angle = angle; } //Make current be w/e
    void turn(double angle} { this.angle += angle; }
    double distance(void angle) {
        double d = 0;
        for(const line &border: walls){
	    //check if point to angle direction crosses that border, and if it does return it
	    d = border.intersection(this.location,this.angle);
	    if(d) return d;
	}

        for(const line &border: plataforms){
	    //check if point to angle direction crosses that border, and if it does return it
	    d = border.intersection(this.location,this.angle);
	    if(d) return d;
	}
	// should never happen	
	return 0;
    }

};
