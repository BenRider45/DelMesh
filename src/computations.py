import math
import matplotlib.pyplot as plt
def compCC(A,B):


    denom = B.perpM - A.perpM
    X_Num = (B.perpM*B.midPt.x) - (A.perpM*A.midPt.x) + (A.midPt.y - B.midPt.y)
    Y_Num = (pow(B.perpM,2)*B.midPt.x) - (A.perpM*B.perpM*A.midPt.x) + B.perpM*(A.midPt.y - B.midPt.y)
    Y_Res = -B.perpM*B.midPt.x + B.midPt.y
        
    CircCenter_X =  X_Num / denom
    CircCenter_Y = (Y_Num /denom) + Y_Res
    CirclePoint = (CircCenter_X,CircCenter_Y)
    CircleRadius = math.sqrt(pow((CircCenter_X - A.a.x),2)+ pow((CircCenter_Y - A.a.y),2))
    output = (CirclePoint,CircleRadius)
    return output


class point2D:
    def __init__(self,x,y):
        self.x = x
        self.y = y
        self.V = [x,y]


class LINE:
    def __init__(self,a,b):
        self.a = a
        self.b = b
        self.midPt = point2D((a.x+b.x)/2,(a.y+b.y)/2)
        self.m = (b.y-a.y)/(b.x - a.x)
        self.perpM = -1/self.m

class Triangle:
    def __init__(self,a,b,c):
        self.a = a
        self.b = b
        self.c = c
        self.PointArrX = [self.a,self.b,self.c]
        self.AB = LINE(a,b)
        self.BC = LINE(b,c)
        self.CA = LINE(c,a)
def main():

    A = point2D(-15.0,5.0)
    B = point2D(15.0,4.0)
    C = point2D(0.0,10.0)
    AC = LINE(A,C)
    BC = LINE(B,C)
    CA = LINE(C,A)
    plt.plot(A.V[0],A.V[1], marker="o")
    plt.plot(B.V[0],B.V[1], marker = "o")
    plt.plot(C.V[0],C.V[1],marker="o")

    

    plt.plot([A.V[0],C.V[0],B.V[0],A.V[0]],[A.V[1],C.V[1],B.V[1],A.V[1]],linestyle='dotted')

    ccpt = compCC(AC,BC) 
    print(ccpt[0])
    print(ccpt[1])
    plt.plot(ccpt[0][0],ccpt[0][1],marker ="o")
    # ccircle = plt.Circle(ccpt[0][0],ccpt[1],color = 'r')
    # print(ccircle)
    # ax = plt.gca()
    # ax.add_patch(ccircle)


    
    #print(compCC(AC,BC))

    plt.show()

    return 0

main()