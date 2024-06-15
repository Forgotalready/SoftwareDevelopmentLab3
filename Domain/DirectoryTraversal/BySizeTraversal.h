#ifndef BYSIZETRAVERSAL_H
#define BYSIZETRAVERSAL_H

#include "TraversalStrategy.h"
#include <QDir>

class BySizeTraversal : public TraversalStrategy
{
private:
    void directoryTraversal(QDir&, QMap<QString, double>& stat);
public:
    QMap<QString, double> execute(const QString& path) override;
};

#endif // BYSIZETRAVERSAL_H
