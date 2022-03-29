#include "glos.h"
#include <gl.h>
#include <glu.h>
#include <glaux.h>


void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);

void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);

void CALLBACK RotesteSursaStanga(void);
void CALLBACK RotesteSursaDreapta(void);

void CALLBACK RotesteVentilatorSus(void);
void CALLBACK RotesteVentilatorJos(void);

void CALLBACK RotesteDreapta(void);
void CALLBACK RotesteStanga(void);

void CALLBACK MutaSus(void);
void CALLBACK MutaJos(void);


static GLfloat x = 0;
static GLfloat a = 0;
static GLfloat alfa1 = 0;
static GLfloat alfa = 0;
static GLfloat beta = 0;

void myinit (void) {

    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat local_view[] = { 0.0 };

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_DEPTH_TEST);  //activare test de ascundere

    glEnable(GL_LIGHTING);  //activare iluminare 
    glEnable(GL_LIGHT0);    //activare sursa 0

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);   //setari pt sursa de lumina
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    //functii care permit iluminarea culorilor setate cu glColor3f
    //glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);  //se vad culorile mai sterse
}


void CALLBACK MutaStanga(void)
{
	x = x - 10;
}

void CALLBACK MutaDreapta(void)
{
	x = x + 10;
}

void CALLBACK RotesteSursaStanga(void)
{
    alfa1 = alfa1 - 2;
}

void CALLBACK RotesteSursaDreapta(void)
{
    alfa1 = alfa1 + 2;
}

void CALLBACK RotesteStanga(void)
{
    beta = beta + 40;
}
void CALLBACK RotesteDreapta(void)
{
    beta = beta - 40;
}
void CALLBACK MutaSus(void)
{
    a = a + 10;
}

void CALLBACK MutaJos(void)
{
    a = a - 10;
}

void CALLBACK RotesteVentilatorSus(void)
{
    alfa = alfa - 20;
}

void CALLBACK RotesteVentilatorJos(void)
{
    alfa = alfa + 20;
}


void CALLBACK display (void)
{
    GLfloat position[] = { 0.0, 120.0, 80.0, 1.0 };       //pozitia sursei
   
    GLfloat mat_ambient1[] = { 0.0, 0.0, 0.54, 0.0 };
    GLfloat mat_ambient2[] = { 1.0, 0.16, 0.16, 0.0 };
    GLfloat mat_diffuse1[] = { 0.0, 0.0, 0.54, 0.0 };
    GLfloat mat_diffuse2[] = { 1.0, 0.16, 0.16, 0.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };

    GLUquadricObj* q;
    q = gluNewQuadric();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //test de ascundere
    
    glPushMatrix();

        glPushMatrix();
            glRotatef(alfa1, 0, 1, 0);
            glLightfv(GL_LIGHT0, GL_POSITION, position);

            //desenarea sferei (sursa de lumina)
            glPushMatrix();
                glTranslatef(0.0, 120.0, 80.0);
                glColor3f(1.0, 1.0, 0.0);
                glDisable(GL_LIGHTING);  //dezactivare iluminare 
                auxSolidSphere(15.0);
                glEnable(GL_LIGHTING);  //activare iluminare 
            glPopMatrix();
            glPopMatrix();



            glTranslatef(x, 0, 0.0);  //translatarea obiectului stanga-dreapta
            glTranslatef(0, a, 0);    //translatarea obiectului sus-jos
            glRotatef(alfa, 1, 0, 0); //rotirea obiectului sus-jos
      

            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


            //cilindru
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);

                glColor3f(0.0, 0.0, 0.54);
                glRotatef(90.0, 1.0, 0.0, 0.0);      //rotim fata de axa x ca sa vedem cilindrul in picioare
                gluCylinder(q, 10.0, 10.0, 120.0, 30.0, 1); //q, raza baza mare, raza baza mica, inaltimea, nr. felii slices=felii tort ,stacks=cilindrii unul peste altul
            glPopMatrix();

        
            glPushMatrix();
               glTranslatef(0, 60, 0);
               glRotatef(beta, 0, 0 , 1);
               glTranslatef(0, -60, 0);

            //cerc
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
                glColor3f(0.0, 0.0, 0.54);
                glTranslatef(0, 60, 0.0);
                gluDisk(q, 55, 60, 80, 20);
            glPopMatrix();

            //sfera interior cerc
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
                glColor3f(1.0, 0.16, 0.16);
                glTranslatef(0, 60, 0.0);
                gluSphere(q, 10, 100, 100);
            glPopMatrix();


            //sector de cerc 1 dreapta
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
                glColor3f(1.0, 0.16, 0.16);
                glTranslatef(10, 60, 0.0);
                gluPartialDisk(q, 0, 40, 50, 20, 50, 80);
            glPopMatrix();


            //sector de cerc 2 jos
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
                glColor3f(1.0, 0.16, 0.16);
                glTranslatef(0, 50, 0.0);
                gluPartialDisk(q, 0, 40, 50, 20, 500, 80);
            glPopMatrix();


            //sector de cerc 3 stanga
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
                glColor3f(1.0, 0.16, 0.16);
                glTranslatef(-10, 60, 0.0);
                gluPartialDisk(q, 0, 40, 50, 20, -500, 80);
            glPopMatrix();


            //sector de cerc 4 sus
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
                glColor3f(1.0, 0.16, 0.16);
                glTranslatef(0, 70, 0.0);
                gluPartialDisk(q, 0, 40, 50, 20, 5000, 80);
            glPopMatrix();

    glPopMatrix();
        
    glPopMatrix();
    glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)	
{
    if (!h) return;
    glViewport(0, 0, w, h);	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)		
    glOrtho (-150.0, 150.0, -150.0*(GLfloat)h/(GLfloat)w,   //dimensiunile ferestrei x=-150 y=150, la fel si jos
        150.0*(GLfloat)h/(GLfloat)w, -1000.0, 1000.0);
    else 
    glOrtho (-150.0*(GLfloat)w/(GLfloat)h, 
        150.0*(GLfloat)w/(GLfloat)h, -150.0, 150.0, -1000.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB);  
    auxInitPosition (0, 0, 500, 500);
    auxInitWindow ("Ventilator");
    myinit ();

    //translateaza ventilatorul
	auxKeyFunc (AUX_LEFT, MutaStanga);
	auxKeyFunc (AUX_RIGHT, MutaDreapta);

    //rotirea sursei de lumina
    auxKeyFunc(AUX_A, RotesteSursaStanga);
    auxKeyFunc(AUX_S, RotesteSursaDreapta);
    auxKeyFunc(AUX_a, RotesteSursaStanga);
    auxKeyFunc(AUX_s, RotesteSursaDreapta);

    //rotirea elicelor ventilatorului
    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, RotesteStanga);
    auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, RotesteDreapta);

    auxKeyFunc(AUX_d, RotesteVentilatorSus);
    auxKeyFunc(AUX_f, RotesteVentilatorJos);

    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);

    auxReshapeFunc (myReshape);
    auxMainLoop(display);
    return(0);
}
