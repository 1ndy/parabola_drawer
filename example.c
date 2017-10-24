/*
A simple example of using the gfx library.
CSE 20211
9/7/2011
by Prof. Thain
*/

#include <time.h>
#include <math.h>
#include <stdio.h>
#include "gfx.h"
#include <stdlib.h>

typedef struct point {
	int x;
	int y;
} point;

typedef struct line {
	point p1;
	point p2;
} line;

//point constructor
point pointConstructor(int x, int y) {
	point p;
	p.x = x;
	p.y = y;
	return p;
}

line lineConstructor(point p1, point p2) {
	line l;
	l.p1 = p1;
	l.p2 = p2;
	return l;
}


//calculate the taxicab length of a line
int calcXLength(line l) {
	return l.p2.x - l.p1.x;
}

int calcYLength(line l) {
	return l.p2.y - l.p1.y;
}

/*int round(double d) {
	double s = d % (int) d;
	if(s >= .5)
		return s + 1;
	else
		return s;
}*/

//return an array of points that evenly divide the line
void calcLineDivisions(line l, int numDivs, point p[]) {
	int xLen = calcXLength(l);
	int yLen = calcYLength(l);
	int i = 1;
	int c = numDivs;
	
	int x = l.p2.x;
	int y = l.p2.y;
	p[numDivs-1] = pointConstructor(x,y);

	x = l.p1.x;
	y = l.p1.y;
	p[0] = pointConstructor(x,y);

	printf("Length x y: %d   %d\n", xLen, yLen);
	for(i = 0; i < numDivs; i++) {
		/*x = (int) round(xLen / c-2);
		y = (int) round(yLen / c-2);
		c -= 2;
		p[i] = pointConstructor(l.p1.x+x, l.p1.y+y);
		p[numDivs-i-1] = pointConstructor(l.p2.x-x, l.p2.y-y);
		xLen = calcXLength(lineConstructor(p[i], p[numDivs-i-1]));
		yLen = calcYLength(lineConstructor(p[i], p[numDivs-i-1]));*/

		x +=  (int) round(xLen / numDivs);
		y += (int) round(yLen / numDivs);
		p[i] = pointConstructor(x, y);
	}	

}

double lineLength(line l) {
	return sqrt(pow(calcXLength(l),2)+pow(calcYLength(l),2));
}

//simplify line drawing
void drawLine(point p1, point p2) {
	gfx_line(p1.x, p1.y, p2.x, p2.y);
}

//print all of the points lines are draw to
void printLines(point p[], point o[], int len) {
	int i;
	for(i = 0; i < len; i++) {
		printf("%d   (%d,%d) --> (%d,%d)\n", i, p[i].x, p[i].y, o[len-i-1].x, o[len-i-1].y);
	}
}

int randX() {
	return rand()%1919+1;
}

int randY() {
	return rand()%1079+1;
}

void drawShape(int start1, int start2, int start3, int start4, int end1, int end2, int end3, int end4, int divs) {
	line l1 = lineConstructor(pointConstructor(start1, start2), pointConstructor(end1, end2)); 
	line l2 = lineConstructor(pointConstructor(start3, start4), pointConstructor(end3, end4));

	//printf("l0.p1, l2.p1= %f     l1.p1,l2.p2 = %f\n", lineLength(lineConstructor(l1.p1, l2.p1)), lineLength(lineConstructor(l1.p1, l2.p2)));
	if(abs(lineLength(lineConstructor(l1.p1, l2.p1))) > abs(lineLength(lineConstructor(l1.p2, l2.p1)))) {
		l2 = lineConstructor(l2.p2, l2.p1);
	}

	point line1[divs]; 
	calcLineDivisions(l1, divs, line1);

	point line2[divs];
	calcLineDivisions(l2, divs, line2);
	
	//draw the lines
	int i;
	for(i = 0; i < divs; i++) {
		if(i % 2 == 1)
			gfx_color(0,0,255);
		else
			gfx_color(0,255,0);
		drawLine(line1[i], line2[divs-i-1]);
		printf("(%d,%d) --> (%d,%d)\n", line1[i].x, line1[i].y, line2[divs-i-2].x, line2[divs-i-2].y);
	}
}


void freeDraw() {
	
	int ysize = 1080;
	int xsize = 1920;

	char c;

	int divs;
	int start1,start2,end1,end2;
	int start3,start4,end3,end4;


	srand(time(0));

	printf("Enter number of lines per shape: ");
	scanf("%d", &divs);//rand()%30+10;


	//printLines(line1,line2,divs);

	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Fancy line drawer");

	// Set the current drawing color
	while(1) {
		c = gfx_wait();
		
		if(c == 'b')
			gfx_color(0,0,255);
		else if(c == 'r')
			gfx_color(255,0,0);
		else if(c == 'g')
			gfx_color(0,255,0);
		else if(c == 'w')
			gfx_color(255,255,255);
		else if(c == 'y')
			gfx_color(255, 255,0);
		else if(c == 'p')
			gfx_color(255, 0,255);
		else if(c == 'c')
			gfx_color(0, 255,255);
		else if(c == 'o')
			gfx_color(255, 102,0);
		else if(c = 'l')
			gfx_clear();
		else if(c == 'q')
			exit(0);
		
		c = gfx_wait();	
		start1 = gfx_xpos();//randX();
		//printf("%d\n", start1);
		start2 = gfx_ypos();//randY();	
		
		c = gfx_wait();	
		end1 = gfx_xpos();//randX();
		end2 = gfx_ypos();//randY();

		//gfx_line(start1, start2, end1, end2);

		c = gfx_wait();	
		start3 = gfx_xpos();//randX();
		start4 = gfx_ypos();//randY();
	
		c = gfx_wait();	
		end3 = gfx_xpos();//randX();
		end4 = gfx_ypos();//randY();
	
		//gfx_line(start3, start4, end3, end4);
		drawShape(start1, start2, start3, start4, end1, end2, end3, end4, divs);
	}

}

int main()
{
	freeDraw();
}
