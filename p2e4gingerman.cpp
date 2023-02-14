#include <GL/glut.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 480
#define THICKNESS 5
#define M 40
#define MIN_L 1
#define MAX_L 9

int px, py; // previous point
int qx, qy; // current point
int L = MIN_L;

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.78, 0.47, 0.17);
  glPointSize(THICKNESS);
  glBegin(GL_POINTS);

  int i;
  for (i = 0; i < 10000; i++) {
    qx = M * (1 + 2 * L) - py + abs(px - L * M);
    qy = px;

    glVertex2i(qx, qy);

    px = qx;
    py = qy;
  }

  glEnd();
  glFlush();
}

void mouseClick(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    px = x;
    py = HEIGHT - y;
    glutPostRedisplay();
  }
}

void keyPress(unsigned char key, int x, int y) {
  if (key >= '1' && key <= '9') {
    L = key - '0';
    glutPostRedisplay();
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Gingerbread Man");
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, WIDTH, 0, HEIGHT);
  glutDisplayFunc(display);
  glutMouseFunc(mouseClick);
  glutKeyboardFunc(keyPress);
  glutMainLoop();
  return 0;
}
