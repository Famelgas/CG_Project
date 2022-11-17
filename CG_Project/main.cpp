#pragma GCC diagnostic ignored "-Wdeprecated-declarations"


#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#define PI         3.14159

// Cores
#define RED      1.0, 0.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define BLUE     0.0, 0.0, 1.0, 1.0
#define YELLOW   1.0, 1.0, 0.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define CYAN     0.0, 1.0, 1.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.3, 0.3, 0.3, 1.0


GLint        wScreen = 700, hScreen = 600;
GLfloat        SIZE = 10.0;



GLfloat pos[] = { 0., 0., 0.};

GLfloat rotation = 0.;
GLfloat speed = 1.;
GLfloat rodMov = -23.5;
GLfloat cable = 0.3;

GLint alwaysON = 0;
GLfloat altura = 0.;
GLfloat incALT = 0.1;
GLint faceVisivel = 0;
GLfloat wheelRadius = 0.7;
GLfloat wheelHeight = 0.3;
GLint view = 0;



GLfloat rVisao = 8, aVisao = -0.5 * PI, incVisao = 3;
GLfloat obsP[] = { rVisao * cos(aVisao), 2.0, rVisao * sin(aVisao) };
float anguloZ = 35;



GLint     msec = 50;



static GLuint cima[] = { 8, 11, 10, 9 };
static GLuint baixo[] = { 12, 13, 14, 15 };
static GLuint esquerda[] = { 0, 1, 2, 3 };
static GLuint direita[] = { 4, 5, 6, 7 };
static GLuint frente[] = { 16, 17, 18, 19 };
static GLuint tras[] = { 20, 21, 22, 23 };

GLfloat tam = 0.25;
static GLfloat vertices[] = {
    //Esquerda
    -tam,  -tam,  tam,    // 0
    -tam,   tam,  tam,    // 1
    -tam,   tam, -tam,    // 2
    -tam,  -tam, -tam,    // 3
    //Direita
    tam,  -tam,  tam,    // 4
    tam,   tam,  tam,    // 5
    tam,   tam, -tam,    // 6
    tam,  -tam, -tam,    // 7
    //Cima
    -tam,  tam,  tam,    // 8
    -tam,  tam, -tam,    // 9
    tam,  tam, -tam,    // 10
    tam,  tam,  tam,    // 11
    //Baixo
    -tam, -tam, tam,    //12
    -tam, -tam, -tam,    //13
    tam, -tam, -tam,    //14
    tam, -tam, tam,        //15
    //Frente
    -tam, -tam, tam,    //12
    -tam, tam, tam,        //13
    tam, tam, tam,        //14
    tam, -tam, tam,        //15
    //Tras
    -tam, -tam, -tam,    //12
    -tam, tam, -tam,    //13
    tam, tam, -tam,        //14
    tam, -tam, -tam,    //15
};

static GLfloat normais[] = {
    //Esquerda
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    -1.0,  0.0,  0.0,
    //Direita
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    1.0,  0.0,  0.0,
    //Cima
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    0.0,  1.0,  0.0,
    //Baixo
    0.0,  -1.0,  0.0,
    0.0,  -1.0,  0.0,
    0.0,  -1.0,  0.0,
    0.0,  -1.0,  0.0,
    //Frente
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,
    0.0,  0.0,  1.0,
    //Tras
    0.0,  0.0,  -1.0,
    0.0,  0.0,  -1.0,
    0.0,  0.0,  -1.0,
    0.0,  0.0,  -1.0,
};

static GLfloat colors[] = {
    //Esquerda
    1,  0, 0,// 0
    1,  0, 0,// 1
    1,  0, 0,// 2
    1,  0, 0,// 3
    //Direita
    1,  0, 0,// 4
    1,  0, 0,// 5
    1,  0, 0,// 6
    1,  0, 0,// 7
    //Cima
    1,  0, 0,// 8
    1,  0, 0,// 9
    1,  0, 0,// 10
    1,  0, 0,// 11
    //Baixo
    1,  0, 0,// 12
    1,  0, 0,// 13
    1,  0, 0,// 14
    1,  0, 0,// 15
    //Frente
    1,  0, 0,// 16
    1,  0, 0,// 17
    1,  0, 0,// 18
    1,  0, 0,// 19
    //Tras
    1,  0, 0,// 20
    1,  0, 0,// 21
    1,  0, 0,// 22
    1,  0, 0,// 23
};


void draw_cylinder(GLfloat radius, GLfloat height) {
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat z              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    // Tube
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    // Circle on top
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
    
    // Circle on the bottom
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , z);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}

void draw_cube() {
    glPushMatrix();
    
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
    glPushMatrix();
}

void draw_wheels() {
//    glTranslatef(-1., 0., -1.);
    glPushMatrix();
    draw_cylinder(wheelRadius, wheelHeight);
    glPopMatrix();
}


void draw_truck() {
    
    
    
}


void initialize(void)
{
    glClearColor(BLACK);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
    
}



void drawEixos() {
    glColor4f(ORANGE);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0.5 * SIZE, 0, 0);
    glEnd();
    glColor4f(GREEN);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0.5 * SIZE, 0);
    glEnd();
    glColor4f(BLUE);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 0.5 * SIZE);
    glEnd();

}

void drawScene() {
    if (alwaysON) {
        rotation = rotation + 1;
        altura = altura + incALT;
        if (altura > 3) incALT = -incALT;
        if (altura < -1) incALT = -incALT;
    }

    glPushMatrix();
    glTranslatef(pos[0], altura, 0.0);
    glTranslatef(0.0, altura, pos[2]);
    glRotatef(rotation, 0.0, 1.0, 0.0);
    glScalef(2.5, 2.0, 2.5);
    
    // draw base
    glColor4f(BLUE);
    glPushMatrix();
    glTranslatef(0., 0., 0.);
    glScalef(4., 1., 2.);
    draw_cube();
    glPopMatrix();

    glColor4f(YELLOW);
    // draw cabine
    glPushMatrix();
    glTranslatef(-0.3, 0.5, 0.);
    glScalef(1., 1., 2.);
    draw_cube();
    glPopMatrix();
    
    // draw rod
    glColor4f(RED);
    glPushMatrix();
    glTranslatef(-0.03, 0.3, 0.);
    glRotatef(90., 0., 1., 0.);
    glTranslatef(0.03, -0.3, 0.);
    glRotatef(rodMov, 0., 0., 0.);
    glTranslatef(-0.03, 0.3, 0.);
    draw_cylinder(0.1, 1.4);
    
    
    // draw cable
    glColor4f(GREEN);
    glTranslatef(0., -0.1, 1.35);
    glRotatef(90., 0., 0., 0.);
    glRotatef(-rodMov, 0., 0., 0.);
    
    draw_cylinder(0.01, cable);
    // draw winch
    glColor4f(CYAN);
    glTranslatef(0., 0., cable);
    draw_cylinder(0.025, 0.1);
    
    glPopMatrix();
    
    // front left
    glColor4f(WHITE);
    glPushMatrix();
    glTranslatef(-0.5, -0.25, 0.45);
    draw_cylinder(0.2, 0.1);
    glPopMatrix();
    
    // back left
    glColor4f(WHITE);
    glPushMatrix();
    glTranslatef(0.5, -0.25, 0.45);
    draw_cylinder(0.2, 0.1);
    glPopMatrix();
    
    // front right
    glColor4f(WHITE);
    glPushMatrix();
    glTranslatef(-0.5, -0.25, -0.55);
    draw_cylinder(0.2, 0.1);
    glPopMatrix();
    
    // back right
    glColor4f(WHITE);
    glPushMatrix();
    glTranslatef(0.5, -0.25, -0.55);
    draw_cylinder(0.2, 0.1);
    glPopMatrix();
    
    
    glPopMatrix();

    glColor4f(YELLOW);
    glTranslatef(0, tam + 0.3, 0.0);
}


void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glViewport(0,0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 85, (float)wScreen / hScreen, 0.1, 9999);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (!view) {
        gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
    }
    else {
        gluLookAt(0, 10, 0, 0, 0, 0, obsP[0], 0, obsP[2]);
    }
    
    drawEixos();
    drawScene();

    glutSwapBuffers();
}


void Timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


    switch (key) {
    case 'A': case 'a':
        rotation += 3.;
        glutPostRedisplay();
        break;
            
    case 'D': case 'd':
        rotation -= 3.;
        glutPostRedisplay();
        break;
            
    case 'W': case 'w':
        pos[0] = pos[0] - speed * cos(rotation * PI / 180.);
        pos[2] = pos[2] + speed * sin(rotation * PI / 180.);
        glutPostRedisplay();
        break;
    
    case 'S': case 's':
        pos[0] = pos[0] + speed * cos(rotation * PI / 180.);
        pos[2] = pos[2] - speed * sin(rotation * PI / 180.);
        glutPostRedisplay();
            break;
    
    case 'Q': case 'q':
        rodMov -= 3.;
        glutPostRedisplay();
        break;
    
    case 'E': case 'e':
        rodMov += 3.;
        glutPostRedisplay();
        break;
        
    case 'R': case 'r':
        cable -= 0.05;
        glutPostRedisplay();
        break;
   
    case 'F': case 'f':
        cable += 0.05;
        glutPostRedisplay();
        break;
       
    
    case 'C': case 'c':
        if (view) {
            view = 0;
        }
        else {
            view = 1;
        }
        glutPostRedisplay();
        break;
       
        
    case 27:
        exit(0);
        break;
    }

}



void teclasNotAscii(int key, int x, int y) {
    
    //=========================================================
    //  <><><><><><>  Movimento do observador  ???
    //=========================================================
    if (key == GLUT_KEY_UP) {
        obsP[1] += 0.5;
    }
    if (key == GLUT_KEY_DOWN) {
        obsP[1] -= 0.5;
    }
    if (key == GLUT_KEY_LEFT) {
        aVisao += incVisao;
    }
    if (key == GLUT_KEY_RIGHT) {
        aVisao -= incVisao;
    }
    obsP[0] = rVisao * cos(aVisao * PI / 180.);
    obsP[2] = rVisao * sin(aVisao * PI / 180.);

    glutPostRedisplay();
}



//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Filipe Mendes");

    initialize();

    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(msec, Timer, 1);

    glutMainLoop();

    return 0;
}



