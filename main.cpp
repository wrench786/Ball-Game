#include <iostream>
#include<windows.h>
#include<mmsystem.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>
using namespace std;

int x=20;
int y=20;

int speed=5;
int high = 200;

int left_limit;
int right_limit;
int up_limit;

bool up = false;
bool move_left = false;
bool move_right = false;

bool reset=false;

int dum=true;

int point=0;

int box=7;
int boxx[]={150, 400, 700, 500, 900,300, 50};
int boxy[]={100, 200, 250, 320, 370, 470, 520};
int box_move[]={0, 1, 0, 1, 0, 1,0};

int coin=7;
int coin_count[]={1, 1, 1, 1, 1,1, 1};

void myInit ()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 1200, 0,600, -10.0, 10.0);
}

void circle(float x,float y)
{
    float x1,y1,x2,y2;
    float radius=20;
    x1=x;
    y1=y;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(254,0,0);
    glVertex2f(x1,y1);
    float angle;
    for (angle=0; angle<=360; angle+=0.5)
    {
        x2 = x1+sin((angle*3.1416)/180)*radius;
        y2 = y1+cos((angle*3.1416)/180)*radius;
        glVertex2f(x2,y2);
    }
    glEnd();
}

void circle2(float x,float y)
{
    float x1,y1,x2,y2;
    float radius=10;
    x1=x;
    y1=y;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(rand()%255,rand()%255,rand()%255);
    glVertex2f(x1,y1);
    float angle;
    for (angle=0; angle<=360; angle+=0.5)
    {
        x2 = x1+sin((angle*3.1416)/180)*radius;
        y2 = y1+cos((angle*3.1416)/180)*radius;
        glVertex2f(x2,y2);
    }
    glEnd();
}
void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);  // Set the raster position for text rendering

    // Loop through each character in the text
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);  // Render each character using GLUT bitmap fonts
    }
}

void rectangle(){

    for(int i=0;i<box;i++){
        int xx = boxx[i];
        int yy = boxy[i];

        glBegin(GL_QUADS);  // Begin drawing a quadrilateral
        if(i==0) glColor3ub(235,64,52);
        if(i==1) glColor3ub(128, 52, 235);
        if(i==2) glColor3ub(235, 220, 52);
        if(i==3) glColor3ub(235, 52, 137);
        if(i==4) glColor3ub(52, 235, 89);
        if(i==5) glColor3ub(52, 235, 211);
        if(i==6) glColor3ub(235, 52, 147);

        glVertex2f( xx, yy);  // Define the vertices of the rectangle
        glVertex2f(xx+140, yy);
        glVertex2f(xx+140, yy+20);
        glVertex2f(xx, yy+20);

        glEnd();
    }
}

void coins(){
    for(int i=0;i<coin;i++){
        int xx = boxx[i];
        int yy = boxy[i];
        if(coin_count[i]) circle2(xx+70,yy+30);
    }
}

void kata(){
        glBegin(GL_TRIANGLES);  // Begin drawing a quadrilateral

        glColor3ub(rand()%255,rand()%255,rand()%255);

        for(int i=150;i<=1170;i+=30){
            glVertex2f(i, 0);  // Define the vertices of the rectangle
            glVertex2f(i+15, 20);
            glVertex2f(i+30, 0);
        }

        glEnd();
}

void text_print(){
    renderText(1000, 580, "Your Total Point Is");

    char numberString[32];
    sprintf(numberString, "%d", point);
    renderText(1100, 560, numberString);
}

void display ()
{
    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT);

    if (reset)
    {
        renderText(500, 300, "Game Over");
        renderText(480, 280, "Press 'x' to restart");
        glFlush();
        return;
    }

    text_print();
    circle( x ,y);
    rectangle();
    coins();
    kata();

    if(x>=150 && x<=1170 && y<=20) reset = true;

    for(int i=0;i<coin;i++){

        if(coin_count[i]==0)continue;

        int xx = boxx[i]+70;
        int yy = boxy[i]+30;

        double dis = sqrt((xx-x)*(xx-x)+(yy-y)*(yy-y));
        if(dis<=25.0){
            coin_count[i]=0;
            point++;
        }
    }
    for(int i=0;i<box;i++){
        if(box_move[i]){
            boxx[i]+=2;
            if(boxx[i]==1050) box_move[i]=0;
        }
        else{
            boxx[i]-=2;
            if(boxx[i]==10) box_move[i]=1;
        }
    }

    if(up){
        int cnt=0;

        for(int i=0;i<box;i++){
            int xx = boxx[i];
            int yy = boxy[i];

            if(x>=xx && x<=xx+140 && y==yy-20){
                cnt++;
            }
        }
        if(cnt==0){
            y+=speed;
            if(y==up_limit){
                up = false;
            }
        }
        else{
            up = false;
        }
    }
    if(!up){
        int cnt=0;

        for(int i=0;i<box;i++){
            int xx = boxx[i];
            int yy = boxy[i];

            if(x>=xx && x<=xx+140 && y==yy+40){
                cnt++;
                dum= true;
            }
        }
        if(cnt==0){
            y-=speed;
            if(y<=20){
                y = 20;
                dum=true;
            }
        }
    }

    if(move_right){
        x+=5;
        if(x>right_limit ){
            move_right = false;
        }
    }
    if(move_left){
        x-=5;
        if(x<left_limit ){
            move_left = false;
        }
    }

    glFlush();
}


void keyboardFunc(unsigned char key, int a, int b){
    if(reset){
        if (key == 'x' || key == 'X')
        {
            x=20;
            y=20;

            up = false;
            move_left = false;
            move_right = false;

            dum=true;

            point=0;

            boxx[0]=150;
            boxx[1]= 400;
            boxx[2]= 700;
            boxx[3]= 500;
            boxx[4]= 900;
            boxx[5]= 300;
            boxx[6]= 50;

            boxy[0]= 100;
            boxy[1]= 200;
            boxy[2]= 250;
            boxy[3]= 320;
            boxy[4]= 370;
            boxy[5]= 470;
            boxy[6]= 520;
            for(int i=0;i<box;i++){
                box_move[i] = i%2;
                coin_count[i]=1;
            }

            reset = false;
        }
    }
    else{
        if(key=='d' || key=='D'){
            move_right= true;
            move_left = false;
            right_limit = min(x+100,1180);
        }
        else if(key=='a' || key == 'A'){
            move_left = true;
            move_right = false;
            left_limit = max(20,x-100);
        }
        else if(key=='w' || key=='W'){
            if(dum){
                up=true;
                dum=false;
                up_limit = min(y+200,600);
            }
        }
        else if(key=='r' || key=='R'){
            reset= true;
        }
    }


    glutPostRedisplay();

}
void update(int val)
{

    glutPostRedisplay();
    glutTimerFunc(2, update, 0);
}
int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // giving window size in X- and Y- direction
    glutInitWindowSize(1200, 600);
    glutInitWindowPosition(0, 0);

    // Giving name to window
    glutCreateWindow("Game 71");
    myInit();

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    update(0);

    sndPlaySound("sound.wav",SND_ASYNC);
    glutKeyboardFunc(keyboardFunc);
    glutMainLoop();
}
