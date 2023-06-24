#include <GL/glut.h>
#include <stdio.h>
/* initial triangle */
typedef GLfloat point[3];
point v[] = { {30.0, 50.0, 100.0}, {0.0, 450.0, -150.0},
 {-350.0, -400.0, -150.0}, {350., -400., -150.0} };
int n; /* number of recursive steps */
void triangle(point a, point b, point c)
{
	glBegin(GL_TRIANGLES); /* display one triangle */
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}
void tetra(point a, point b, point c, point d)
{
	glColor3f(1.0, 0.0, 0.0);
	triangle(a, b, c);
	glColor3f(0.0, 1.0, 0.0);
	triangle(a, c, d);
	glColor3f(0.0, 0.0, 1.0);
	triangle(a, d, b);
	glColor3f(0.0, 0.0, 0.0);
	triangle(b, d, c);
}
void divide_tetra(point a, point b, point c, point d, int m)
{
	/* tretra subdivision using vertex numbers */
	GLfloat mid[6][3];
	int j;
	if (m > 0)
	{
		for (j = 0; j < 3; j++) mid[0][j] = (a[j] + b[j]) / 2;
		for (j = 0; j < 3; j++) mid[1][j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) mid[2][j] = (a[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) mid[3][j] = (b[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) mid[4][j] = (c[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) mid[5][j] = (b[j] + d[j]) / 2;
		divide_tetra(a, mid[0], mid[1], mid[2], m - 1);
		divide_tetra(mid[0], b, mid[3], mid[5], m - 1);
		divide_tetra(mid[1], mid[3], c, mid[4], m - 1);
		divide_tetra(mid[2], mid[5], mid[4], d, m - 1);
	}
	else tetra(a, b, c, d);
}
void display()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	divide_tetra(v[0], v[1], v[2], v[3], n);
	glFlush();
}
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-499.0, 499.0, -499.0, 499.0, -499.0, 499.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
	printf("\n Enter the number of division:\n");
	scanf("%d", &n);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D gasket");
	glEnable(GL_DEPTH_TEST);
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
