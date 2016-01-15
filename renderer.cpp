#include "renderer.h"
#include "teapot.h"

#include <QCoreApplication>
#include <QDebug>
#include <QKeyEvent>
#include <math.h>
#include <GL/glu.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_VEC3(v1, v2) (vec3(MAX((v1).x, (v2).x), MAX((v1).y, (v2).y), MAX((v1).z, (v2).z)))

Lines::Lines( QWidget* parent )
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent ),
      m_theta( 0.0f ),
      m_phi( 0.0f ),
      m_rho( 0.0f )
{
    points = nullptr;
};

Lines::~Lines()
{
    if (points)
    {
        cfree(points);
        points = nullptr;
    }
};

void Lines::set_data(std::vector<point3f>* Lines)
{
    bb = vec3(1, 1, 1);

    if (points)
    {
        cfree(points);
        points = nullptr;
    }

    lines = Lines->data();
    lines_c = Lines->size();

    for (size_t i = 0; i < lines_c; i++)
    {
        bb = MAX_VEC3(bb, lines[i]);                //### pretty slow, patch
        lines[i].set_clr(CLR_LINE);
    }

    dim = vec3(bb.x == 1 ? 0 : 1, bb.y == 1 ? 0 : 1, bb.z == 1 ? 0 : 1);
    bb = bb +dim;
    int i = 0;
    points = (point3f*)calloc(bb.x*bb.y*bb.z, sizeof(point3f));

    for (int x = 0; x < bb.x; x++)
        for (int y = 0; y < bb.y; y++)
            for (int z = 0; z < bb.z; z++)
                points[i++] = point3f(x,y,z, CLR_DOT);

    qDebug() << "Lines:" << lines_c << "\nBB:" << bb.x << bb.y << bb.z;
    qDebug().nospace() << "Dim: " << dim.x << '/' << dim.y << '/' << dim.z << " as " << dim.x+dim.y+dim.z << 'd';
};

void Lines::initializeGL()
{
};

void Lines::resizeGL( int w, int h )
{
    // Prevent a divde by zero
    if (!h)
        h = 1;

    // Set the viewport to window dimensions
    glViewport(0, 0, w, h);

    // reset the coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    double r = w / (double)h;
    gluPerspective(60.d, r, .1d, 500.d);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
};

void Lines::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(CLR_BLK);
    glPushMatrix();

    gluLookAt(1, 1, 1, 10,10,10, 0,1,0);
    glRotatef( m_theta, 1.0f, 0.0f, 0.0f);
    glRotatef( m_phi,   0.0f, 1.0f, 0.0f);
    glRotatef( m_rho,   0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, scale);

    //draw points
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(point3f), &points[0].x);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(point3f), &points[0].r);
    glPointSize(DOT_SIZE);
    glDrawArrays(GL_POINTS, 0, bb.x*bb.y*bb.z);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    //draw lines
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(point3f), &lines[0].x);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(point3f), &lines[0].r);
    glLineWidth(LINE_SIZE);
    glDrawArrays(GL_LINES, 0, lines_c);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glPopMatrix();
};

void Lines::wheelEvent(QWheelEvent* e)
{
    float d = e->delta() *-.01f;

    GLdouble view[16];
    glGetDoublev(GL_PROJECTION_MATRIX, view);

    glTranslated(view[2] *d, view[6] *d, view[10] *d);
    updateGL();
};

void Lines::keyPressEvent( QKeyEvent* e )
{
    switch ( e->key() )
    {
        case Qt::Key_Escape:
            QCoreApplication::instance()->quit();
            break;

        case Qt::Key_A:
            m_phi -= 1.0f;
            updateGL();
            break;

        case Qt::Key_D:
            m_phi += 1.0f;
            updateGL();
            break;

        case Qt::Key_W:
            m_theta -= 1.0f;
            updateGL();
            break;

        case Qt::Key_S:
            m_theta += 1.0f;
            updateGL();
            break;

        case Qt::Key_Y:
            m_rho -= 1.0f;
            updateGL();
            break;

        case Qt::Key_C:
            m_rho += 1.0f;
            updateGL();
            break;

        case Qt::Key_Space:
            m_rho = m_theta = m_phi = 0.f;
            scale = 1.f;
            updateGL();
            break;

        case Qt::Key_Q:
            scale -= .1f;
            updateGL();
            break;

        case Qt::Key_E:
            scale += .1f;
            updateGL();
            break;

        default:
            QGLWidget::keyPressEvent( e );
    }
};
