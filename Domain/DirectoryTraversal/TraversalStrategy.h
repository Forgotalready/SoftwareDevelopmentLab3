#ifndef TRAVERSALSTRATEGY_H
#define TRAVERSALSTRATEGY_H

#include <QMap>

QMap<QString, double> formOtherGroup(QMap<QString, double>& stat, double border = 1.0);

class TraversalStrategy
{
public:
    virtual ~TraversalStrategy() = default;

    virtual QMap<QString, double> execute(const QString& path) = 0;
};

#endif // TRAVERSALSTRATEGY_H
