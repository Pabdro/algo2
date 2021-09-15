#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;
double DEG_to_RAD(double d) { return d*M_PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / M_PI; }
struct point { double x, y;   
  point() { x = y = 0.0; }              
  point(double _x, double _y) : x(_x), y(_y) {}        
  bool operator == (point other) const {
   return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); } 
  bool operator <(const point &p) const {
   return x < p.x || (abs(x-p.x) < EPS && y < p.y); } };
struct vec { double x, y;  
  vec(double _x, double _y) : x(_x), y(_y) {} };
vec toVec(point a, point b) {       
  return vec(b.x-a.x, b.y-a.y); }
double dist(point p1, point p2) {               
  return hypot(p1.x-p2.x, p1.y-p2.y); }              
double perimeter(const vector<point> &P) {  
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      
    ans += dist(P[i], P[i+1]);              
  return ans;
}
double area(const vector<point> &P) {
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)
    ans += (P[i].x*P[i+1].y - P[i+1].x*P[i].y);
  return fabs(ans)/2.0;                        
}
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }
double angle(point a, point o, point b) {  
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }
double area_alternative(const vector<point> &P) {
  double ans = 0.0; point O(0.0, 0.0);        
  for (int i = 0; i < (int)P.size()-1; ++i)   
    ans += cross(toVec(O, P[i]), toVec(O, P[i+1]));
  return fabs(ans)/2.0;
}
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}
bool isConvex(const vector<point> &P) {
  int n = (int)P.size();
  if (n <= 3) return false;
  bool firstTurn = ccw(P[0], P[1], P[2]);      
  for (int i = 1; i < n-1; ++i)               
    if (ccw(P[i], P[i+1], P[(i+2) == n ? 1 : i+2]) != firstTurn)
      return false;                            
  return true;                                   
}
int insidePolygon(point pt, const vector<point> &P) {
  int n = (int)P.size();
  if (n <= 3) return -1;                       
  bool on_polygon = false;
  for (int i = 0; i < n-1; ++i)                  
    if (fabs(dist(P[i], pt) + dist(pt, P[i+1]) - dist(P[i], P[i+1])) < EPS)
      on_polygon = true;
  if (on_polygon) return 0;                
  double sum = 0.0;                       
  for (int i = 0; i < n-1; ++i) {
    if (ccw(pt, P[i], P[i+1]))
      sum += angle(P[i], pt, P[i+1]);  
    else
      sum -= angle(P[i], pt, P[i+1]);         
  }
  return fabs(sum) > M_PI ? 1 : -1;             
}
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y-A.y, b = A.x-B.x, c = B.x*A.y - A.x*B.y;
  double u = fabs(a*p.x + b*p.y + c);
  double v = fabs(a*q.x + b*q.y + c);
  return point((p.x*v + q.x*u) / (u+v), (p.y*v + q.y*u) / (u+v));
}
vector<point> cutPolygon(point A, point B, const vector<point> &Q) {
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); ++i) {
    double left1 = cross(toVec(A, B), toVec(A, Q[i])), left2 = 0;
    if (i != (int)Q.size()-1) left2 = cross(toVec(A, B), toVec(A, Q[i+1]));
    if (left1 > -EPS) P.push_back(Q[i]);        
    if (left1*left2 < -EPS)                 
      P.push_back(lineIntersectSeg(Q[i], Q[i+1], A, B));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());                     
  return P;
}
vector<point> CH_Graham(vector<point> &Pts) {    
  vector<point> P(Pts);                         
  int n = (int)P.size();
  if (n <= 3) {                         
    if (!(P[0] == P[n-1])) P.push_back(P[0]);    
    return P;                                    
  }
  int P0 = min_element(P.begin(), P.end())-P.begin();
  swap(P[0], P[P0]);                            
  sort(++P.begin(), P.end(), [&](point a, point b) {
    return ccw(P[0], a, b);                     
  });
  vector<point> S({P[n-1], P[0], P[1]});         
  int i = 2;                                     
  while (i < n) {                                
    int j = (int)S.size()-1;
    if (ccw(S[j-1], S[j], P[i]))                
      S.push_back(P[i++]);                       
    else                                         
      S.pop_back();                              
  }
  return S;                                      
}
vector<point> CH_Andrew(vector<point> &Pts) {   
  int n = Pts.size(), k = 0;
  vector<point> H(2*n);
  sort(Pts.begin(), Pts.end());                  
  for (int i = 0; i < n; ++i) {                  
    while ((k >= 2) && !ccw(H[k-2], H[k-1], Pts[i])) --k;
    H[k++] = Pts[i];
  }
  for (int i = n-2, t = k+1; i >= 0; --i) {
    while ((k >= t) && !ccw(H[k-2], H[k-1], Pts[i])) --k;
    H[k++] = Pts[i];
  }
  H.resize(k);
  return H;
}
int main() {
    int x,y;
    vector<point>pB;
    for (int i = 0; i < 4; i++) {
        cin>>x>>y;
        pB.emplace_back(x,y);
    }
    double area2 = area(pB);
    vector<point>pA;
    for (int i = 0; i < 4; i++) {
        cin>>x>>y;
        pA.emplace_back(x,y);
    }
    double area1 = area(pA);
    if(area1 < area2) {
        cout<<"terreno A";
    }
    if(area1 == area2) {
        cout<<"terreno B";
    }
    if(area1 > area2) {
        cout<<"terreno B";
    }
  return 0;
}