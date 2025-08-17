import math
def compCC(A,B):


    denom = B.perpM - A.perpM;
    X_Num = (B.perpM*B.midPt.x) - (A.perpM*A.midPt.x) + (A.midPt.y - B.midPt.y);
    Y_Num = (pow(B.perpM,2)*B.midPt.x) - (A.perpM*B.perpM*A.midPt.x) + B.perpM*(A.midPt.y - B.midPt.y);
    Y_Res = -B.perpM*B.midPt.x + B.midPt.y;
        
    CircCenter_X =  X_Num / denom;
    CircCenter_Y = (Y_Num /denom) + Y_Res;
    CirclePoint = (CircCenter_X,CircCenter_Y);
    CircleRadius = math.sqrt(pow((CircCenter_X - A.a.x),2)+ pow((CircCenter_Y - A.a.y),2));
    output = (CirclePoint,CircleRadius);
    return output


class point2D:
    def __init__(self,x,y):
        self.x = x
        self.y = y


class LINE:
    def __init__(self,a,b):
        self.a = a
        self.b = b
        self.midPt = point2D((a.x+b.x)/2,(a.y+b.y)/2)
        self.m = (b.y-a.y)/(b.x - a.x)
        self.perpM = -1/self.m

def main():

    A = point2D(-15.0,5.0)
    B = point2D(15.0,0.0)
    C = point2D(0.0,10.0)
    
    AB = LINE(A,B)
    AC = LINE(A,C)
    BC = LINE(B,C)
    print(compCC(AC,BC))

    return 0

main()