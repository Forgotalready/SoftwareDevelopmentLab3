#include "TraversalStrategy.h"


QMap<QString, double> formOtherGroup(QMap<QString, double> &stat, double border){
    QMap<QString, double> newStat;
    double all = 0.0;
    for(auto x : stat)
        all += x;


    foreach(auto x, stat.keys()){
        double procent = (stat[x] / all) * 100;
        if(procent <= border){
            if(newStat.count("Other") != 0) newStat["Other"] += procent;
            else newStat["Other"] = procent;
        }else{
            newStat[x] = procent;
        }
    }
    return newStat;
}
