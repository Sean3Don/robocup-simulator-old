#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <Geometry/Point2d.hpp>
#include "RobotPath.hpp"
#include "../soccer/Processor.hpp"
#include <log/LogFile.hpp>
#include "log/LogControl.hpp"

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QPointF>
#include <ui_motion.h>
#include <QString>

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT;

    public:
        enum
        {
        DrawingMode,
        RunMode,
    };

    public:
        MainWindow(Team team, QString filename);
        ~MainWindow();

    public Q_SLOTS:
        void on_erase_clicked();
        void on_beizerCurve_clicked();
        void on_line_clicked();
        void on_erasePath_clicked();
        void on_run_clicked();
        void on_stop_clicked();
        void on_startPoint_clicked();
        void on_closePath_clicked();
        void on_arc_clicked();
        void on_close_clicked();
        void on_kp_valueChanged(double value);
        void on_kd_valueChanged(double value);
        void on_saveGains_clicked();
        void setupModules();

    Q_SIGNALS:
        void runTrajectoryGen();
        void stopTrajectoryGen();
        void setPaths(QVector<RobotPath::Path> paths);
        void setPixelFieldSize(Geometry::Point2d size);
        void kpChanged(double kp);
        void kdChanged(double kd);
        //TODO This isn't right. I need to load the config file here so that mainwindow can access it
        void saveGains();

    private:
        Ui::MainWindow ui;

        RobotPath* _rp;

        Team _team;

        int _mode;

        Processor _processor;

        Log::LogFile* _logFile;
        /** This controls the data flow from logger to visualizers **/
        Log::LogControl* _logControl;

        /** Currently the configfile is for motion but others can add to it **/
        QString _configFile;
};

#endif // MAIN_WINDOW_HPP