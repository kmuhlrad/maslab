#include<vector>
using namespace std;
typedef pair<double, double> point;
typedef pair<point, point> line;
typedef vector<line> borders;
typedef char colors;//8 bits, R=0,G=1; the three first bits are botton, middle, top colors, the fourth is if it's empty
typedef pair<point,colors> stack;

inline bottom(stack s)

struct MaslabMap {
    borders walls;
    borders plataforms;
    vector<stack> stacks;

};
