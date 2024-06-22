#ifndef TRAVERSALSTRATEGY_H
#define TRAVERSALSTRATEGY_H

#include <QMap>
#include <memory>

QMap<QString, double> formOtherGroup(QMap<QString, double>& stat, double border = 1.0);

class TraversalStrategy
{
public:
    virtual ~TraversalStrategy() = default;

    virtual std::shared_ptr<QMap<QString, double>> execute(const QString& path) = 0;
};

#endif // TRAVERSALSTRATEGY_H
