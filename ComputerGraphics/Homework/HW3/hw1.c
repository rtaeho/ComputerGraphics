#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GL/glut.h>

int mouseCurX = -1;
int mouseCurY = -1;
int rightButtonPressed = 0; // 오른쪽 마우스 버튼 상태를 추적하는 플래그
int middleButtonPressed = 0; // 가운데 마우스 버튼 상태를 추적하는 플래그
float rotationAngle = 0.0;
float fov = 90.0; // 초기 시야각 설정
float cameraX = 1.0;
float cameraY = 1.0;
float cameraZ = 1.0;

void drawCube(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidCube(size);
    glPopMatrix();
}

void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
}

void drawCubesAndSpheres() {
    drawCube(-0.5, 0.0, -2.0, 0.4, 1.0, 0.0, 0.0); // 빨간색 큐브
    drawCube(0.5, 0.0, -2.0, 0.3, 0.0, 0.0, 1.0); // 파란색 큐브
    drawSphere(-0.5, 0.1, -4.0, 0.2, 1.0, 1.0, 0.0); // 노란색 구
    drawSphere(0.5, 0.1, -4.0, 0.1, 0.0, 1.0, 0.0); // 초록색 구
}

void mydisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluPerspective(fov, 1.0, 0.01, 100.0);
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rotationAngle, 0.0, 0.0, 1.0);
    //drawAxes();
    drawCubesAndSpheres();
    glutSwapBuffers();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void mouseMotion(int x, int y) {
    if (rightButtonPressed) {
        if (x > mouseCurX || y > mouseCurY) {
            // 오른쪽 혹은 아래로 드래그할 때 확대
            fov -= 1.0;
        } else if (x < mouseCurX || y < mouseCurY) {
            // 왼쪽 혹은 위로 드래그할 때 축소
            fov += 1.0;
        }
        glutPostRedisplay();
    }
    mouseCurX = x;
    mouseCurY = y;
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x > glutGet(GLUT_WINDOW_WIDTH) / 2) {
            // 오른쪽 반쪽을 클릭하면 시계 방향으로 회전
            rotationAngle += 10.0;
        } else {
            // 왼쪽 반쪽을 클릭하면 반시계 방향으로 회전
            rotationAngle -= 10.0;
        }
    } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        // 가운데 버튼 클릭시 카메라 이동
        cameraX = (x - glutGet(GLUT_WINDOW_WIDTH) / 2.0) / (glutGet(GLUT_WINDOW_WIDTH) / 2.0);
        cameraY = -(y - glutGet(GLUT_WINDOW_HEIGHT) / 2.0) / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0);
        cameraZ = 1.0; // z 축은 그대로 유지
    } else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN)
            rightButtonPressed = 1;
        else if (state == GLUT_UP)
            rightButtonPressed = 0;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("20011675 류태호");
    glutDisplayFunc(mydisplay);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    init();
    glutMainLoop();
    return 0;
}
