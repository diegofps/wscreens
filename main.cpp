#include <QRegularExpression>
#include <QDesktopWidget>
#include <QApplication>
#include <QProcess>
#include <QScreen>
#include <QDir>

#include <wup/wup.hpp>

using namespace wup;

WUP_STATICS;

const char *
getBaseFilepath(Params & params)
{
    auto defaultPrefixout = cat(QDir::homePath(), "/Pictures/screenshot_", time_milli());
    return params.getString("o", defaultPrefixout.c_str());
}

void
screenshotFull(QApplication & a, Params & params)
{
    for (int i=0;i!=a.screens().size();++i)
    {
        auto filepath = QString(cat(getBaseFilepath(params), "_", i, "_full.png").c_str());
        auto & screen = *a.screens().at(i);
        auto r = screen.geometry();

        auto shot = screen.grabWindow(QDesktopWidget().winId(), r.x(), r.y(), r.width(), r.height());

        shot.save(filepath);

        print(filepath);
    }
}

void
screenshotWindow(QApplication & a, Params & params)
{
    QString filepath(getBaseFilepath(params));
    filepath += "_window.png";

    int offX = params.getInt("offX", 0);
    int offY = params.getInt("offY", 0);
    int offW = params.getInt("offW", 0);
    int offH = params.getInt("offH", 0);

    QProcess p;
    p.start("xdotool getactivewindow getwindowgeometry");
    p.waitForFinished();
    QString output(p.readAllStandardOutput());
    p.close();

    QRegularExpression re1("Position: (\\d+),(\\d+)");
    QRegularExpression re2("Geometry: (\\d+)x(\\d+)");

    auto m1 = re1.match(output);
    auto m2 = re2.match(output);

    if (m1.hasMatch() && m2.hasMatch())
    {
        int x0 = m1.capturedStart(1);
        int x1 = m1.capturedEnd(1);

        int y0 = m1.capturedStart(2);
        int y1 = m1.capturedEnd(2);

        int w0 = m2.capturedStart(1);
        int w1 = m2.capturedEnd(1);

        int h0 = m2.capturedStart(2);
        int h1 = m2.capturedEnd(2);

        int x = QString(output.data() + x0, x1 - x0).toInt() + offX;
        int y = QString(output.data() + y0, y1 - y0).toInt() + offY;
        int w = QString(output.data() + w0, w1 - w0).toInt() + offW;
        int h = QString(output.data() + h0, h1 - h0).toInt() + offH;

        auto shot = a.screens().at(0)->grabWindow(QDesktopWidget().winId(), x, y, w, h);

        shot.save(filepath);

        print(filepath);
    }
    else
    {
        error("Failed to acquire current window position");
    }
}

void
screenshotRegion(QApplication & a, Params & params)
{
    notImplemented();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Params params(argc, argv);

    if (params.has("f"))
        screenshotFull(a, params);

    else if (params.has("w"))
        screenshotWindow(a, params);

    else if (params.has("r"))
        screenshotRegion(a, params);

    else
        error("Missing action parameter: -w, -f, -r");

    return 0;
}
