#include <GL/glut.h>
#include <math.h>

// Variabel global
float angle = 0.0;
float sunPositionY = 6.0; 
float moonPositionY = 6.0; 
float scaleSun = 1.0f;
float scaleMoon = 1.0f;
GLfloat lightPosition[] = {0.0, -5.0, 0.0, 1.0};
GLfloat lightAmbient[] = {0.2, 0.2, 0.2, 1.0}; 
GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0}; 
GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};
float mountainScale = 1; 
bool isDay = true; // Mode siang/malam
bool showCartecius = false; // tampilkan garis kartesius


void gunung(float offsetX) {
    glPushMatrix();
    glTranslatef(offsetX, 0.0, 0.0); 
    glScalef(mountainScale, mountainScale, mountainScale); 

    // Sisi depan gunung
    glBegin(GL_TRIANGLES);
    glColor3f(0.7, 0.2, 0.2); // Merah bata di bagian bawah
    glVertex3f(-3, 0.0, -4.0);
    glColor3f(0.9, 0.5, 0.3); // Oranye di tengah
    glVertex3f(0.0, 5.0, 0.0);
    glColor3f(1.0, 0.8, 0.6); // Krem di puncak
    glVertex3f(3, 0.0, -4.0);
    glEnd();

    // Sisi belakang gunung
    glBegin(GL_TRIANGLES);
    glColor3f(0.7, 0.2, 0.2); 
    glVertex3f(0.0, 5.0, 0.0);
    glColor3f(0.9, 0.5, 0.3);
    glVertex3f(3, 0.0, 4.0);
    glVertex3f(-3, 0.0, 4.0);
    glEnd();

    // Sisi kanan gunung
    glBegin(GL_TRIANGLES);
    glColor3f(0.7, 0.2, 0.2); 
    glVertex3f(0.0, 5.0, 0.0);
    glColor3f(0.9, 0.5, 0.3);
    glVertex3f(3, 0.0, 4.0);
    glVertex3f(3, 0.0, -4.0);
    glEnd();

    // Sisi kiri gunung
    glBegin(GL_TRIANGLES);
    glColor3f(0.7, 0.2, 0.2); 
    glVertex3f(0.0, 5.0, 0.0);
    glColor3f(0.9, 0.5, 0.3);
    glVertex3f(-3, 0.0, -4.0);
    glVertex3f(-3, 0.0, 4.0);
    glEnd();

    // Dasar gunung
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.1, 0.1); // Merah gelap untuk dasar
    glVertex3f(-3.0, 0.0, -4.0);
    glVertex3f(3.0, 0.0, -4.0);
    glVertex3f(3.0, 0.0, 4.0);
    glVertex3f(-3.0, 0.0, 4.0);
    glEnd();

    glPopMatrix();
}

void jalan() {
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0); 
    glVertex3f(1.5, 0.1, 4.0);
    glVertex3f(-1.5, 0.1, 4.0);
    glVertex3f(-2.0, 0.1, 10.0);
    glVertex3f(2.0, 0.1, 10.0);
    glEnd();
}

void matahari() {
    glPushMatrix();
    glTranslatef(0.0, sunPositionY, -5.0);
    glScalef(scaleSun,scaleSun,scaleSun);
    glColor3f(1.0, 1.0, 0.0); 
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

void bulan() {
    glPushMatrix();
    glTranslatef(0.0, moonPositionY, -5.0);
    glScalef(scaleMoon, scaleMoon,scaleMoon);
    glColor3f(1.0, 1.0, 1.0); 
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

void drawBackground() {
    // Langit bagian atas
    glBegin(GL_QUADS);
    if (isDay) {
        glColor3f(0.5, 0.7, 1.0); // Siang: biru muda
    } else {
        glColor3f(0.0, 0.0, 0.2); // Malam: biru gelap
    }
    glVertex3f(-10.0, 10.0, -10.0);
    glVertex3f(10.0, 10.0, -10.0);
    glVertex3f(10.0, 0.0, -10.0);
    glVertex3f(-10.0, 0.0, -10.0);
    glEnd();

    // Langit bagian bawah (hijau tetap ada)
    glBegin(GL_QUADS); 
    glColor3f(0.0, 0.6, 0.0); // Warna hijau untuk tanah
    glVertex3f(10.0, 0.0, 10.0);
    glVertex3f(-10.0, 0.0, 10.0);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(10.0, 0.0, -10.0);
    glEnd();
}

void drawCartecius() {
    glLineWidth(5.0); // Atur ketebalan garis menjadi lebih tebal
    glColor3f(1.0, 0.0, 0.0); // Warna garis merah
    glBegin(GL_LINES);

    // Sumbu X
    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);

    // Sumbu Y
    glVertex3f(0.0, -50.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);

    // Sumbu Z
    glVertex3f(0.0, 0.0, -50.0);
    glVertex3f(0.0, 0.0, 50.0);

    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
        10.0 * sin(angle), 5.0, 10.0 * cos(angle), 
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Gambar garis kartesius jika aktif
    if (showCartecius) {
        drawCartecius();
    }

    drawBackground();
    gunung(-1.5);
    gunung(1.5);

    if (isDay) {
        matahari();
    } else {
        bulan();
    }

    jalan();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, (GLfloat)width/(GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.5, 0.7, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING); 
    glEnable(GL_COLOR_MATERIAL);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            angle += 0.1;
            break;
        case 'd':
            angle -= 0.1;
            break;
        case '1': // Siang
            isDay = true;
            glClearColor(0.5, 0.7, 1.0, 0.0);
            break;
        case '2': // Malam
            isDay = false;
            glClearColor(0.0, 0.0, 0.2, 0.0);
            break;
        case '=':
            scaleSun += 0.1f;
            break;
        case '-':
            scaleSun -= 0.1f;
            break;
        case ']':
            scaleMoon += 0.1f;
            break;
        case '[':
            scaleMoon -= 0.1f;
            break;
        case 'c': // Toggle garis kartesius
            showCartecius = !showCartecius;
            break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:    
            sunPositionY += 0.1;
            break;
        case GLUT_KEY_DOWN:  
            sunPositionY -= 0.1;
            break;
        case GLUT_KEY_LEFT:  
            moonPositionY += 0.1;
            break;
        case GLUT_KEY_RIGHT: 
            moonPositionY -= 0.1;
            break;
    }
    glutPostRedisplay(); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600); 
    glutCreateWindow("TB kelompok 1");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}