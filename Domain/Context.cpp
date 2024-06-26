#include "Context.h"

Context::Context(std::shared_ptr<TraversalStrategy> &strategy)
    : strategy(strategy){}

void Context::setStrategy(std::shared_ptr<TraversalStrategy> &strategy)
{
    this->strategy = strategy;
}

QMap<QString, double> Context::executeStrategy(const QString &path)
{
    Q_ASSERT_X(strategy != nullptr, "Context execute", "Strategy isn't initilize");

    if(strategy != nullptr) return strategy->execute(path);
    else return QMap<QString, double>();
}
