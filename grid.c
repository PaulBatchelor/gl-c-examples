#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>

void timer(int value);
void initGfx();
void idleFunc();
void displayFunc();
void reshapeFunc( GLsizei width, GLsizei height );
void keyboardFunc( unsigned char, int, int );
void mouseFunc( int button, int state, int x, int y );

/* width and height */
long g_width = 640;
long g_height = 640;
int g_clock = 0;

int main( int argc, char ** argv )
{
    /* initialize GLUT */
    glutInit( &argc, argv );
    /* init gfx */
    initGfx();
    
    /* let GLUT handle the current thread from here */
    glutMainLoop();

    return 0;
}

void initGfx()
{
    /* double buffer, use rgb color, enable depth buffer */
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    /* initialize the window size */
    glutInitWindowSize( g_width, g_height );
    /* set the window postion */
    glutInitWindowPosition( 500, 500);
    /* create the window */
    glutCreateWindow( "simple" );
    
    /* set the idle function - called when idle */
    //glutIdleFunc( idleFunc );
    glutTimerFunc(10, timer, 0);
    /* set the display function - called when redrawing */
    glutDisplayFunc( displayFunc );
    /* set the reshape function - called when client area changes */
    glutReshapeFunc( reshapeFunc );
    /* set the keyboard function - called on keyboard events */
    glutKeyboardFunc( keyboardFunc );
    /* set the mouse function - called on mouse stuff */
    glutMouseFunc( mouseFunc );
    
    /* set clear color */
    glClearColor( 0, 0, 0, 1 );
    /* enable color material */
    glEnable( GL_COLOR_MATERIAL );
    /* enable depth test */
    glEnable( GL_DEPTH_TEST );
}


void reshapeFunc( GLsizei w, GLsizei h )
{
    /* save the new window size */
    g_width = w; g_height = h;
    /* map the view port to the client area */
    glViewport( 0, 0, w, h );
    /* set the matrix mode to project */
    glMatrixMode( GL_PROJECTION );
    /* load the identity matrix */
    glLoadIdentity( );
    /* create the viewing frustum */
    gluPerspective( 45.0, (GLfloat) w / (GLfloat) h, 1.0, 300.0 );
    /* set the matrix mode to modelview */
    glMatrixMode( GL_MODELVIEW );
    /* load the identity matrix */
    glLoadIdentity( );
    /* position the view point */
    gluLookAt( 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );
}

void keyboardFunc( unsigned char key, int x, int y )
{
    switch(key) {
        case 'q': exit(1);
        default:
            break;
    }

    glutPostRedisplay( );
}

void mouseFunc( int button, int state, int x, int y )
{
    if( button == GLUT_LEFT_BUTTON ) {
        /* when left mouse button is down */
        if( state == GLUT_DOWN ) {
            exit(1);
        }
        else {

        }
    }
    else if ( button == GLUT_RIGHT_BUTTON )
    {
        /* when right mouse button down */
        if( state == GLUT_DOWN ) {
        }
        else {
        }
    }
    else {
    }
    
    glutPostRedisplay( );
}

void idleFunc( )
{
    /* render the scene */

    glutPostRedisplay( );
}

void timer(int value)
{
    glutPostRedisplay( );
}

void displayFunc( )
{
    int gridSize = 128;
    unsigned int i;
    float size = 1.0 / (gridSize / 2);
    float pos_x = 1, pos_y = 0;
    /* local state */

    /* clear the color and depth buffers */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    /* line width */
    glLineWidth( 1.0 );
    /* define a starting point */
    GLfloat x = -5;
    /* increment */
    GLfloat xinc = 1;
    
    /* start primitive */
    for(i = 0; i < gridSize * gridSize; i++) {
        pos_x = i % gridSize;
        pos_y = i / gridSize;
        glColor3f(
                ((i % 2) ? 1 : 0), 
                0.6784, 1.0 * i / (gridSize * gridSize));
        glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-1.0f + pos_x * size, -1.0f + pos_y * size);
        glVertex2f(-1.0f + pos_x * size, -1.0f + size + pos_y * size);
        glVertex2f(-1.0f + size + pos_x * size, -1.0f + pos_y * size);
        glVertex2f(-1.0f + size + pos_x * size, -1.0f + size + pos_y * size);
        glEnd();
    }

    /* flush! */
    glFlush( );
    /* swap the double buffer */
    glutSwapBuffers( );
}
