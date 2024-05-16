#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GL/glut.h>

void mydisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.0, 0.5);
    glVertex2f(0.0, -0.5);
    glEnd();
    glFlush();
}

void init(void){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("20011675 류태호");
    glutDisplayFunc(mydisplay);
    init();
    glutMainLoop();
}

