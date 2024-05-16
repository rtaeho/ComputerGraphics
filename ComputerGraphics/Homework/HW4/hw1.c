#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GL/glut.h>

int mouseCurX = -1;
int rotationAngle = 0;

GLfloat light0_position[] = {
    2.0,
    5.0,
    2.0,
    1.0
};
GLfloat light0_diffuse[] = {
    4.5,
    1.0,
    1.0,
    1.0
};
GLfloat light0_ambient[] = {
    0.2,
    0.2,
    0.2,
    1.0
};
GLfloat light0_specular[] = {
    1.0,
    1.0,
    1.0,
    1.0
};

GLfloat light1_position[] = {
    0.0,
    0.0,
    5.0,
    1.0
};
GLfloat light1_diffuse[] = {
    0.0,
    0.0,
    1.0,
    1.0
};
GLfloat light1_ambient[] = {
    0.1,
    0.1,
    0.1,
    1.0
};
GLfloat light1_specular[] = {
    0.0,
    0.0,
    1.0,
    1.0
};

void drawWalls() {
    GLfloat wall_ambient[] = {
        0.9,
        0.7,
        0.1,
        1.0
    };
    GLfloat wall_diffuse[] = {
        0.1,
        0.1,
        0.1,
        1.0
    };
    GLfloat wall_specular[] = {
        0.0,
        0.0,
        0.0,
        1.0
    };
    GLfloat wall_shininess[] = {
        20.0
    };
    glMaterialfv(GL_FRONT, GL_AMBIENT, wall_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wall_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, wall_shininess);
    
    
    glPushMatrix();
    glTranslatef(0.0, -1.5, 0.0);
    glScalef(9.0, 0.1, 7.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    
    glTranslatef(0.0, 0.95, -3.5);
    glScalef(9.0, 5.0, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(4.5, 0.95, 0.0);
    glScalef(0.1, 5.0, 7.0);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawCabinet() {
    
    GLfloat cabinet_ambient[] = {
        0.9,
        0.6,
        0.2,
        1.0
    };
    GLfloat cabinet_diffuse[] = {
        0.3,
        0.3,
        0.3,
        1.0
    };
    GLfloat cabinet_specular[] = {
        0.0,
        0.0,
        0.0,
        1.0
    };
    GLfloat cabinet_shininess[] = {
        20.0
    };
    glMaterialfv(GL_FRONT, GL_AMBIENT, cabinet_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cabinet_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cabinet_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, cabinet_shininess);
    
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            glPushMatrix();
            glTranslatef(-2.3 + j * 1.2, 3.0 - i * 0.6, -3.2);
            glScalef(1.0, 0.05, 0.5);
            glutSolidCube(1.0);
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(-2.3 + j * 1.2, 2.5 - i * 0.6, -3.2);
            glScalef(1.0, 0.05, 0.5);
            glutSolidCube(1.0);
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(-2.8 + j * 1.2, 2.75 - i * 0.6, -3.2);
            glScalef(0.05, 0.5, 0.5);
            glutSolidCube(1.0);
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(-1.8 + j * 1.2, 2.75 - i * 0.6, -3.2);
            glScalef(0.05, 0.5, 0.5);
            glutSolidCube(1.0);
            glPopMatrix();
            
        }
    }
    
}

void drawTable() {
    // 테이블의 재질 설정
    GLfloat table_ambient[] = {
        0.7,
        0.5,
        0.3,
        1.0
    };
    GLfloat table_diffuse[] = {
        0.7,
        0.5,
        0.3,
        1.0
    };
    GLfloat table_specular[] = {
        0.3,
        0.3,
        0.3,
        1.0
    };
    GLfloat table_shininess[] = {
        50.0
    };
    glMaterialfv(GL_FRONT, GL_AMBIENT, table_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, table_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, table_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, table_shininess);
    
    glPushMatrix();
    glTranslatef(-1.3, 0.1, -2.7);
    glScalef(4.5, 0.1, 1.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.9, -0.75, -3.4);
    glScalef(0.1, 1.6, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.9, -0.75, -2.0);
    glScalef(0.1, 1.6, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-3.5, -0.75, -3.4);
    glScalef(0.1, 1.6, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-3.5, -0.75, -2.0);
    glScalef(0.1, 1.6, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
}

void drawChair() {
    
    GLfloat chair_ambient[] = {
        0.6,
        0.4,
        0.1,
        1.0
    };
    GLfloat chair_diffuse[] = {
        0.2,
        0.2,
        0.2,
        1.0
    };
    GLfloat chair_specular[] = {
        0.5,
        0.5,
        0.5,
        1.0
    };
    GLfloat chair_shininess[] = {
        100.0
    };
    glMaterialfv(GL_FRONT, GL_AMBIENT, chair_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, chair_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, chair_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, chair_shininess);
    
    
    glPushMatrix();
    glTranslatef(-2.3, -0.5, -2.0);
    glScalef(1.0, 0.1, 1.2);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(-2.3, 0.3, -1.4);
    glScalef(1.1, 0.5, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(-2.7, -1.0, -2.5);
    glScalef(0.1, 0.8, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2.8, -1.0, -1.4);
    glScalef(0.1, 2.1, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2.3, -1.0, -2.5);
    glScalef(0.1, 0.8, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.8, -1.0, -1.4);
    glScalef(0.1, 2.1, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawBed() {
    
    GLfloat bed_ambient[] = {
        0.7,
        0.5,
        0.1,
        1.0
    };
    GLfloat bed_diffuse[] = {
        0.6,
        0.8,
        0.2,
        1.0
    };
    GLfloat bed_specular[] = {
        0.3,
        0.3,
        0.3,
        1.0
    };
    GLfloat bed_shininess[] = {
        80.0
    };
    glMaterialfv(GL_FRONT, GL_AMBIENT, bed_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bed_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, bed_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, bed_shininess);
    
    
    glPushMatrix();
    glTranslatef(3.2, -1.1, -1.5);
    glScalef(2.5, 0.7, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    GLfloat matrix_ambient[] = {
        0.9,
        0.9,
        0.9,
        1.0
    };
    GLfloat matrix_diffuse[] = {
        0.9,
        0.9,
        0.9,
        1.0
    };
    GLfloat matrix_specular[] = {
        0.3,
        0.3,
        0.3,
        1.0
    };
    GLfloat matrix_shininess[] = {
        50.0
    };
    glMaterialfv(GL_FRONT, GL_AMBIENT, matrix_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matrix_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matrix_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matrix_shininess);
    
    
    glPushMatrix();
    glTranslatef(3.2, -0.7, -1.5);
    glScalef(2.5, 0.2, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(3.2, -0.2, -3.2);
    glRotatef(-30, 0.0, 0.0, 0.0);
    glScalef(1.2, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
    
}

void drawWindow() {
    
    GLfloat frame_ambient[] = {
        0.7,
        0.7,
        0.7,
        1.0
    };
    GLfloat frame_diffuse[] = {
        0.01,
        0.01,
        0.01,
        1.0
    };
    GLfloat frame_specular[] = {
        0.5,
        0.5,
        0.5,
        1.0
    };
    GLfloat frame_shininess[] = {
        50.0
    };
    glMaterialfv(GL_FRONT, GL_AMBIENT, frame_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, frame_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, frame_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, frame_shininess);
    
    
    glPushMatrix();
    glTranslatef(4.45, 1.3, -1);
    glScalef(0.01, 2.5, 3.5);
    glutSolidCube(1.0);
    glPopMatrix();
    
    GLfloat innerframe_ambient[] = {
        0.9,
        0.9,
        0.9,
        1.0
    };
    GLfloat innerframe_diffuse[] = {
        1.0,
        1.0,
        1.0,
        1.0
    };
    GLfloat innerframe_specular[] = {
        0.5,
        0.5,
        0.5,
        1.0
    };
    GLfloat innerframe_shininess[] = {
        50.0
    };
    glMaterialfv(GL_FRONT, GL_AMBIENT, innerframe_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, innerframe_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, innerframe_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, innerframe_shininess);
    
    glPushMatrix();
    glTranslatef(4.44, 1.3, -1.6);
    glScalef(0.01, 2.0, 1.6);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(4.44, 1.3, 0.0);
    glScalef(0.01, 2.0, 1.2);
    glutSolidCube(1.0);
    glPopMatrix();
}



void drawAxes() {
    glDisable(GL_LIGHTING);
    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-5.0, 0.0, 0.0);
    glVertex3f(5.0, 0.0, 0.0);
    glEnd();
    
    
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -5.0, 0.0);
    glVertex3f(0.0, 5.0, 0.0);
    glEnd();
    
    
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -5.0);
    glVertex3f(0.0, 0.0, 5.0);
    glEnd();
    
    glEnable(GL_LIGHTING);
}

void mydisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, 100.0);
    gluLookAt(-6.0, 3.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rotationAngle, 0.0, 1.0, 0.0);
    
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    
    drawWalls();
    drawAxes();
    drawTable();
    drawChair();
    drawBed();
    drawWindow();
    drawCabinet();
    
    glutSwapBuffers();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void mouseMotion(int x, int y) {
    rotationAngle += (x - mouseCurX);
    mouseCurX = x;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseCurX = x;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '0':
            glEnable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            break;
        case '1':
            glEnable(GL_LIGHT1);
            glDisable(GL_LIGHT0);
            break;
        case '2':
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
            break;
        case '3':
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            break;
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char ** argv) {
    glutInit( & argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Room with Furniture");
    glutDisplayFunc(mydisplay);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
