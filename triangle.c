#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>

void initGfx();
void idleFunc();
void displayFunc();
void reshapeFunc( GLsizei width, GLsizei height );
void keyboardFunc( unsigned char, int, int );
void mouseFunc( int button, int state, int x, int y );

/* width and height */
long g_width = 640;
long g_height = 640;


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
    glutInitWindowPosition( 100, 100 );
    /* create the window */
    glutCreateWindow( "simple" );
    
    /* set the idle function - called when idle */
    glutIdleFunc( idleFunc );
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
    gluLookAt( 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );
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

void displayFunc( )
{
    int i;
    /* local state */

    /* clear the color and depth buffers */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    /* line width */
    glLineWidth( 1.0 );

    GLfloat line_color[] = {1.0, 0, 0};

    GLfloat vVerts[] = { 
        0.0, 0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0
    };

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, vVerts);
    //glEnableVertexAttribArray( 0 );

    glEnableClientState(GL_VERTEX_ARRAY);
    //glColorPointer(3, GL_FLOAT, 0, line_color);
    glColor3f(1.0, 0.0, 0.0);  
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBegin(GL_TRIANGLES);
    glVertexPointer(3, GL_FLOAT, 0, vVerts);
        //glVertex3f(0.0, 0.5, 0.0);
        //glVertex3f(-0.5, -0.5, 0.0);
        //glVertex3f(0.5, -0.5, 0.0);
    glEnd();

    /* flush! */
    glFlush( );
    /* swap the double buffer */
    glutSwapBuffers( );
}
