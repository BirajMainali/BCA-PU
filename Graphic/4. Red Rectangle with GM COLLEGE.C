#include<graphics.h>
#include<conio.h>
int main(){
int gd= DETECT,gm;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
setfillstyle(SOLID_FILL,RED);
rectangle(100,100,250,250);
floodfill(101,101,15);
setcolor(WHITE);
outtextxy(140,170,"GM COLLEGE");
getch();
closegraph();
return 0;
}
