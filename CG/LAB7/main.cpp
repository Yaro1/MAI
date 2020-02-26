#include <iostream>
#include <GL/glut.h>
using namespace std;

double x1[6] = {0,0,0,0,0,0};
double y1[6] = {0,0,0,0,0,0};
double Lagrange(double var)
{
    double s, L;
   // double x1[6] = {-1.0, -0.6, -0.3, 0.3, 1.0, 0.5};
   // double y1[6] = {0.5, 1.0, 0.4, 0.1, 0.5, 0.2};
    L = 0;
 
    for(int i = 0;i < 6;i++){
        s = 1.0;
 
        for(int j = 0;j < 6;j++)
            if(j != i)
                s *= ((var - x1[j]) / (x1[i] - x1[j]));
 
        L += y1[i] * s;
    }
 
    return L;
}
 
void Initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5, 5, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void Draw()
{
    double x;
 
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
 
    glVertex2d(-5, 0);
    glVertex2d(5, 0);
    glVertex2d(0, -5);
    glVertex2d(0, 5);
    glVertex2d(5, 0);
    glVertex2d(4.7, 0.2);
    glVertex2d(5, 0);
    glVertex2d(4.7, -0.2);
    glVertex2d(0, 5);
    glVertex2d(-0.1, 4.7);
    glVertex2d(0, 5);
    glVertex2d(0.1, 4.7);

    for(int i = -5; i < 5; i += 1) {
        glVertex2d(i ,0);
        glVertex2d(i ,0.1);
    }

    for(int i = -5; i < 5; i += 1) {
        glVertex2d(0 ,i);
        glVertex2d(0.1 ,i);
    }
    glEnd(); 
 
    glColor3f(1, 0, 0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
 
    for(x = -6.0;x < 6.0;x += 0.001)
    {
        glVertex2d(x, Lagrange(x));
    }
 
    glEnd();
    glFlush();
}
 
int main(int argc, char**argv)
{
   cout << "Please, enter 6 points in <x> <y>.\n";
    for(int i = 0; i < 6;++i) {
        cin >> x1[i] >> y1[i];
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Lagrange");
    glutDisplayFunc(Draw);
    Initialize();
    glutMainLoop();
    return 0;
}
