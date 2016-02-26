#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include <cairo/cairo.h>

#define WIDTH 500
#define HEIGHT 500


typedef struct {
    //cairo_surface_t *surface;
    //cairo_t *cr;
    //unsigned char img[WIDTH * HEIGHT * 4];
    unsigned error;
    unsigned char *img;
    unsigned width, height;
    //cairo_pattern_t *linpat, *radpat;
    GLuint texName;
} UserData;

UserData g_data;

//void draw(cairo_t *cr, UserData *gd) 
//{
//    cairo_set_source_rgba(cr, 1, 1, 1, 0.0);
//    cairo_paint(cr);
//    cairo_set_source_rgb(cr, 1, 1, 1);
//    cairo_set_line_width(cr, 4.0);
//    cairo_arc(cr, WIDTH / 2, HEIGHT / 2, WIDTH / 3, 0, M_PI);
//    cairo_arc(cr, WIDTH / 2, HEIGHT / 2, WIDTH / 3, M_PI, 0);
//    cairo_stroke(cr);
//    cairo_mask(cr, gd->radpat);
//}

void init(UserData *gd)
{
    glEnable(GL_BLEND);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    //int stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, WIDTH);
    //gd->surface = 
    //cairo_image_surface_create_for_data ((unsigned char *)gd->img, CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT, stride);
    //gd->linpat = cairo_pattern_create_linear(0, 0, 1, 1);

    //cairo_pattern_add_color_stop_rgb(gd->linpat, 0, 0, 0.3, 0.6);
    ///cairo_pattern_add_color_stop_rgb(gd->linpat, 1, 0, 0.6, 0.3);

    //gd->radpat = cairo_pattern_create_radial (0.5, 0.5, 0.25, 0.5, 0.5, 0.75);
    //cairo_pattern_add_color_stop_rgba(gd->radpat, 0, 0, 0, 0, 1);
    //cairo_pattern_add_color_stop_rgba(gd->radpat, 0.5, 0, 0, 0, 0);
    
    //gd->cr = cairo_create (gd->surface);
    //draw(gd->cr, gd);
    //cairo_destroy(gd->cr);

    gd->error = lodepng_decode32_file(
            &gd->img, 
            &gd->width,
            &gd->height,
            "rad.png");

    if(gd->error) {
        printf("error %u: %s\n", gd->error, lodepng_error_text(gd->error));
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &gd->texName);
    glBindTexture(GL_TEXTURE_2D, gd->texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, 
                HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                gd->img);
    //glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}

void clean(UserData *gd)
{
    free(gd->img);
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1);
    GLfloat yOff = 0;
    GLfloat xOff = 0.5;
    float size = 1.0;
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, g_data.texName);

    glBlendFunc(GL_ONE, GL_ONE);
    glBegin(GL_QUADS);
        glColor4f(0, 1.0, 0, 0.5);
        glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
    glEnd();
    
    glBegin(GL_QUADS);
        glColor4f(1, 0.0, 0, 0.5);
        glTexCoord2f(0.0, 0.0); glVertex3f(-2.0 + xOff, -1.0 + yOff, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-2.0 + xOff, 1.0 + yOff, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0 + xOff, 1.0 + yOff, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0 + xOff, -1.0 + yOff, 0.0);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -3.6);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         //clean(&g_data);
         exit(0);
   }
}

void idleFunc( )
{
    /* render the scene */
    glutPostRedisplay( );
}

int main (int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init(&g_data);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idleFunc);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

