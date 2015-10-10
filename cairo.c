#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cairo/cairo.h>

#define WIDTH 120
#define HEIGHT 120


typedef struct {
    cairo_surface_t *surface;
    cairo_t *cr;
    unsigned char img[WIDTH * HEIGHT * 4];
    cairo_pattern_t *linpat, *radpat;
} UserData;

UserData g_data;

void init(UserData *gd)
{
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    int stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, WIDTH);
    gd->surface = 
    cairo_image_surface_create_for_data ((unsigned char *)gd->img, CAIRO_FORMAT_ARGB32, WIDTH, HEIGHT, stride);
    gd->linpat = cairo_pattern_create_linear(0, 0, 1, 1);

    cairo_pattern_add_color_stop_rgb(gd->linpat, 0, 0, 0.3, 0.6);
    cairo_pattern_add_color_stop_rgb(gd->linpat, 1, 0, 0.6, 0.3);

    gd->radpat = cairo_pattern_create_radial (0.5, 0.5, 0.25, 0.5, 0.5, 0.75);
    cairo_pattern_add_color_stop_rgba(gd->radpat, 0, 0, 0, 0, 1);
    cairo_pattern_add_color_stop_rgba(gd->radpat, 0.5, 0, 0, 0, 0);

}

void clean(UserData *gd)
{
    cairo_surface_destroy(gd->surface);
    cairo_pattern_destroy(gd->linpat);
    cairo_pattern_destroy(gd->radpat);
}

void draw(cairo_t *cr, UserData *gd) 
{
	cairo_scale(gd->cr, WIDTH, HEIGHT);
    cairo_set_source(cr, gd->linpat);
    cairo_mask(cr, gd->radpat);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLint m_viewport[4];
    g_data.cr = cairo_create (g_data.surface);
    draw(g_data.cr, &g_data);
    cairo_destroy(g_data.cr);

    glColor3f (1.0, 1.0, 1.0);
    glGetIntegerv(GL_VIEWPORT, m_viewport); 
    glRasterPos2i ((m_viewport[2] - WIDTH) * 0.5 , (m_viewport[3] - HEIGHT)  * 0.5);
    glPixelZoom(1.0, 1.0);
    glDrawPixels(WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, g_data.img);
    glFlush();
}

void reshape(int w, int h)
{
    int i;
    for(i = 0; i < WIDTH*HEIGHT*4; i++) g_data.img[i] = 0;
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
         clean(&g_data);
         exit(0);
   }
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
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

