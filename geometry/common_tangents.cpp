#include<bits/stdc++.h>
#define LD long double
const LD PI=3.1415926535897932384626433;
using namespace std;

struct line {LD a, b, c;};


struct pt {
    LD x, y;
    int id;
    pt(){id=x=y=0;}
    pt(LD x,LD y):x(x),y(y),id(0){}
    bool operator == (pt const& t) const {return x == t.x && y == t.y;}
    pt operator- (pt p) const {return pt(x-p.x,y-p.y);}
    pt operator+ (pt p) const {return pt(x+p.x,y+p.y);}
    void scale(LD val){x*=val;y*=val;}
    LD norm() const{return sqrtl(x*x+y*y);}
    LD dis_to_point(pt other) const{return (*this-other).norm();}
    LD crp(pt other) const{return x*other.y-y*other.x;}
    void normalize(){
        LD _norm=norm();
        x/=_norm,y/=_norm;
    }
    LD dis_to_line(line &l) const{
        return fabs(l.a*x+l.b*y+l.c)/sqrtl(l.a*l.a+l.b*l.b);
    }
    pt project_on_line(line &l) const{
        LD s=dis_to_line(l);
        auto norm=pt(l.a,l.b);norm.normalize(),norm.scale(s);
        pt p1=*this+norm,p2=*this-norm;
        if(p1.dis_to_line(l)<p2.dis_to_line(l))return p1;
        return p2;
    }
    LD fnd_angle() const{ /// angle x o p  (rad%2PI)
        LD len=norm();
        LD angle=acos(fabs(x)/len);
        if(y<0){
            if(x>=0)angle=2*PI-angle;
            else angle+=PI;
        }
        else if(x<0)angle=PI-angle;
        return angle;
    }
};


struct circle : pt {
    LD r;
};


const double EPS = 1E-9;


pt circle_line_intersection(line &l,circle &c){
    auto center=pt(c.x,c.y);
    return center.project_on_line(l);
}

void tangents (pt c, LD r1, LD r2, vector<line> & ans) {
    LD r = r2 - r1;
    LD z = c.x*c.x + c.y*c.y;
    LD d = z - r*r;
    if (d < -EPS)  return;
    d = sqrt (abs (d));
    line l;
    l.a = (c.x * r + c.y * d) / z;
    l.b = (c.y * r - c.x * d) / z;
    l.c = r1;
    ans.push_back (l);
}
vector<line> tangents (circle a, circle b) {
    vector<line> ans;
    for (int i=-1; i<=1; i+=2)
        for (int j=-1; j<=1; j+=2){
            pt dff(b.x,b.y);dff.x-=a.x,dff.y-=a.y;
            tangents (dff, a.r*i, b.r*j, ans);
        }
    for (size_t i=0; i<ans.size(); ++i)
        ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;

    return ans;
}

vector<pt> get_tangent_points(vector<circle> circles){ // each point has its corresponding circle id
    vector<pt> points;
    for(int i=0;i<(int)circles.size();i++){
        for(int j=i+1;j<(int)circles.size();j++){
            auto _tangents=tangents(circles[i],circles[j]);
            for(auto l:_tangents){
                pt itr=circle_line_intersection(l,circles[i]);
                itr.id=i;
                points.push_back(itr);

                itr=circle_line_intersection(l,circles[j]);
                itr.id=j;
                points.push_back(itr);
            }
        }
    }
    return points;
}