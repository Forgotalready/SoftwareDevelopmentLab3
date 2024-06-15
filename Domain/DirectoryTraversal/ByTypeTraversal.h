#ifndef BYTYPETRAVERSAL_H
#define BYTYPETRAVERSAL_H

#include "TraversalStrategy.h"
#include<QDir>

class ByTypeTraversal : public TraversalStrategy
{
private:
    void directoryTraversal(QDir&, QMap<QString, double>&);
public:
    QMap<QString, double> execute(const QString &path);
};

#endif // BYTYPETRAVERSAL_H
