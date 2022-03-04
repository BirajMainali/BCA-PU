#include <graphics.h>
#include <conio.h>
#include<dos.h>
int main()
{
	int gd = DETECT, gm;
	int x = 200, y = 100,i,j;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	setcolor(RED);
	line(x, y, x+200, y);
	setcolor(BLUE);
	rectangle(50,50,100,100);
	setcolor(GREEN);
	for(i=1;i<50;i++)
	{
		for(j=1;j<50;j++){
			delay(0);
			putpixel(x,y,1);
			x++;
		}
		y++; x=200;
	}
	getch();
	closegraph();
	return 0;
}
