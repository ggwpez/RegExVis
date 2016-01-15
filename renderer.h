#ifndef LINES_H
#define LINES_H

#include <QGLWidget>
#include <QVector2D>

#include "vec3.h"
#include "point3f.h"

#define DOT_SIZE 2.f
#define LINE_SIZE 1.f

#define CLR_BLK .2f, .2f, .2f, .1f
#define CLR_DOT   127,255,0,0
#define CLR_LINE  0, 0, 0, 0

const float pi = 3.141592653f;
const float twoPi = 2.0f * pi;
const float piBy2 = 0.5f * pi;
const float degToRad = pi / 180.0f;
const float radToDeg = 180.0f / pi;

class Lines : public QGLWidget
{
    Q_OBJECT

public:
    Lines( QWidget* parent = 0 );
    ~Lines();
    void set_data(std::vector<point3f> *Lines);

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();

    virtual void keyPressEvent( QKeyEvent* e );
    virtual void wheelEvent(QWheelEvent* e);
    //virtual void mouseMoveEvent(QMouseEvent* e);

private:
    float m_theta;  /**< Rotation about x-axis */
    float m_phi;    /**< Rotation about y-axis */
    float m_rho;    /**< Rotation about z-axis */

    vec3 bb, dim;
    point3f* points;
    point3f* lines;
    size_t lines_c = 0;
    float scale = 1.f;
};

#endif // LINES_H
