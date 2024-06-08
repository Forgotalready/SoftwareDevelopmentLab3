#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include "DirectoryTraversal/TraversalStrategy.h"

class Context
{
private:
    std::shared_ptr<TraversalStrategy> strategy;
public:
    Context() = default;
    Context(std::shared_ptr<TraversalStrategy>&);

    void setStrategy(std::shared_ptr<TraversalStrategy>&);
    QMap<QString, double> executeStrategy(const QString&);
};

#endif // CONTEXT_H
