#include <QApplication>
#include <QDebug>

#include "renderer.h"
#include "parser.h"
#include "interpreter.h"
#include "state.h"
#include "bruteforce.h"

#define DELOTE_SYSTEM32 delete

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    Lines w;

    bruteforce br;

    qDebug() << "propagating...";
    state start = br.propagate("(0|1|2)+", "012", 4);        //be carefull with values > 4
    qDebug() << "done";
    std::vector<point3f> lines = std::vector<point3f>();
    qDebug() << "calculating lines...";
    start.calc_lines(&lines);
    qDebug() << "done";

    w.set_data(&lines);
    w.showFullScreen();

    /*parser par = parser();
    size_t l = 0;
    /*(0+)|(1+)|(2+), (0+)(1+)(2+), (0|1|2)+
    ast* tree = par.parse("(0+)(1+)(2+)", l);

    if (!tree) qDebug("Parsing string empty?");
    tree->write(qDebug().nospace());

    interpreter inter = interpreter();
    state end_state = inter.propagate(tree, 3);
    std::vector<point3f> lines = std::vector<point3f>();
    end_state.calc_lines(&lines);

    w.set_data(&lines);
    w.showFullScreen();*/

    return a.exec();
};
