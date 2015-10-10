#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

GLubyte rasters[24] = {
   0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
   0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
   0xff, 0xc0, 0xff, 0xc0};

//GLubyte img[4][4][3];
GLubyte img[] = {
255, 0, 0,    
0, 255, 0,    
0, 0, 255,    
255, 0, 0,    
255, 0, 255,    
255, 0, 0,    
255, 0, 0,    
255, 0, 0,    
255, 0, 0,    
255, 0, 0,    
255, 0, 0,    
255, 0, 0,    
255, 0, 0,    
255, 0, 0,    
255, 0, 0,    
255, 0, 0 
};

void makeImg() 
{
    //int i, x, y;
    //for(i = 0; i < 16; i++) {
    //    x = i % 4;
    //    y = i / 4;
    //    img[x][y][0] = 255;
    //    img[x][y][1] = 0;
    //    img[x][y][2] = 0;
    //}
}

void init(void)
{
   glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glRasterPos2i (20, 20);
   //glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   //glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   //glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
   glPixelZoom(8.0, 8.0);
   glDrawPixels(4, 4, GL_RGB, GL_UNSIGNED_BYTE, img);
   //glCopyPixels(0, 0, 10, 12, GL_COLOR);
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, w, 0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(100, 100);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   makeImg();
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
