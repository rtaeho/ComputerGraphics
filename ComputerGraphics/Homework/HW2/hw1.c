#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GL/glut.h>

void mydisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.4, 0.2);
    glVertex2f(0.0, 0.8);
    glVertex2f(0.4, 0.2);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(-0.8, -0.8);
    glVertex2f(-0.8, -0.2);
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.2, -0.8);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(0.22, -0.8);
    glVertex2f(0.1, -0.45);
    glVertex2f(0.4, -0.2);
    glVertex2f(0.7, -0.45);
    glVertex2f(0.58, -0.8);
    glEnd();
    
    glFlush();
}

void init(void){
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}
void mouseStatus(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x < glutGet(GLUT_WINDOW_WIDTH) / 2) {
            glColor3f(0.0, 0.0, 1.0); // Blue
        }
        else {
            glColor3f(1.0, 0.0, 0.0); // Red
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (y > glutGet(GLUT_WINDOW_HEIGHT) / 2) {
            glColor3f(0.0, 0.0, 0.0); // White
        } else {
            glColor3f(1.0, 1.0, 1.0); // Black
        }
    }
    glutPostRedisplay();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("20011675 류태호");
    glutDisplayFunc(mydisplay);
    glutMouseFunc(mouseStatus);
    init();
    glutMainLoop();
}

