import math
import matplotlib.pyplot as plt
import numpy as np
import sys
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
        if self.m!=0:
            self.perpM = -1/self.m

class Triangle:
    def __init__(self,a=[],b=[],c=[], pntList = []):

        if a == b == c == []:
            print("got here")
            self.a = pntList[0]
            self.b = pntList[1]
            self.c = pntList[2]
        else:
            print("got to else")
            self.a = a
            self.b = b
            self.c = c
        print(type(a))
        print(type(b))
        print(type(c))

        self.PointArr = np.array([self.a.V,self.b.V,self.c.V,self.a.V])
        self.AB = LINE(self.a,self.b)
        self.BC = LINE(self.b,self.c)
        self.CA = LINE(self.c,self.a)

    def output(self,ax):
        ax.plot(self.a.V[0],self.a.V[1], marker="o")
        ax.plot(self.b.V[0],self.b.V[1], marker = "o")
        ax.plot(self.c.V[0],self.c.V[1],marker="o")
        ax.plot(self.PointArr[:,0],self.PointArr[:,1],linestyle='dotted')

        
class Polygon:
    def __init__(self,PntLst):
        self.pointList = np.array([pnt.V for pnt in PntLst] + [PntLst[0].V])
    def output(self,ax):
        for point in self.pointList:
            ax.plot(point[0], point[1], marker="o")

        ax.plot(self.pointList[:,0],self.pointList[:,1],linestyle="dotted")
    

        
def findOccurrences(s, ch):
    return [i for i, letter in enumerate(s) if letter == ch]


def parsePolygon(polyString):
    leftParenOccur = findOccurrences(polyString,"(")
    rightParenOccur = findOccurrences(polyString,")")
    commaOccur = findOccurrences(polyString,",")

    if len(leftParenOccur) != len(rightParenOccur):
        print("ERROR: Mismatched parenthesis in triangle string")
        return
    pntList = []
    for i in range(len(leftParenOccur)):
        lp = leftParenOccur[i]
        rp = rightParenOccur[i]
        c = commaOccur[i]

        x = float(polyString[lp+1:c])
        y = float(polyString[c+1:rp])
        p = point2D(x,y)
        pntList.append(p)
    #Triangle Time!
    if len(pntList) ==3:
        return Triangle(pntList=pntList)
    return Polygon(pntList)



def main():

    n = len(sys.argv)
    print("len: %d",n)
    print(sys.argv[1])
    for str in sys.argv[1].split("\n"):
        outputPoly = parsePolygon(sys.argv[1])
        print(outputPoly)
    # A = point2D(-15.0,5.0)
    # B = point2D(15.0,4.0)
    # C = point2D(0.0,10.0)
    
    # t = Triangle(A,B,C)
        ax = plt.subplot()
        outputPoly.output(ax)

    ax.set_xbound(-20,20)
    ax.set_ybound(-20,20)
    plt.show()
    # #t.output(ax)
    # AC = LINE(A,C)
    # BC = LINE(B,C)
    # CA = LINE(C,A)


    # plt.plot(A.V[0],A.V[1], marker="o")
    # plt.plot(B.V[0],B.V[1], marker = "o")
    # plt.plot(C.V[0],C.V[1],marker="o")


    # plt.plot([A.V[0],C.V[0],B.V[0],A.V[0]],[A.V[1],C.V[1],B.V[1],A.V[1]],linestyle='dotted')

    # ccpt = compCC(AC,BC) 
    # print(ccpt[0])
    # print(ccpt[1])
    # D = point2D(ccpt[0][0],ccpt[0][0])
    # poly = Polygon([A,D,B,C])
    # poly.output(ax)
    # ax.plot(ccpt[0][0],ccpt[0][1],marker ="o")
    # ccircle = plt.Circle(ccpt[0][0],ccpt[1],color = 'r')
    # print(ccircle)
    # ax = plt.gca()
    # ax.add_patch(ccircle)


    
    #print(compCC(AC,BC))

    plt.show()

    return 0

main()