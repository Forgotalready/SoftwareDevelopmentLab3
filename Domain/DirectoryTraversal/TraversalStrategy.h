#ifndef TRAVERSALSTRATEGY_H
#define TRAVERSALSTRATEGY_H

#include <QMap>
#include <string>

class TraversalStrategy
{
public:
    virtual ~TraversalStrategy() = default;

    virtual QMap<QString, double> execute(const QString& path) = 0;
};

#endif // TRAVERSALSTRATEGY_H
