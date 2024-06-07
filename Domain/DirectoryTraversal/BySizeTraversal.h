#ifndef BYSIZETRAVERSAL_H
#define BYSIZETRAVERSAL_H

#include "TraversalStrategy.h"
#include <QDir>
#include <numeric>

class BySizeTraversal : public TraversalStrategy
{
private:
    void directoryTraversal(QDir&, QMap<QString, double>& stat);
    void formOtherGroup(QMap<QString, double>& stat, float pr);
public:
    QMap<QString, double> execute(const QString& path) override;
};

#endif // BYSIZETRAVERSAL_H
