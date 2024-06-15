#include <QCoreApplication>
#include <QDir>
#include <memory>
#include <QTextStream>
#include "Domain./DirectoryTraversal/BySizeTraversal.h"
#include "Domain./DirectoryTraversal/ByTypeTraversal.h"
#include "Domain/Context.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream cout(stdout);

    Context context;

    std::shared_ptr<TraversalStrategy> strategy = std::make_shared<BySizeTraversal>();
    context.setStrategy(strategy);
    auto res = context.executeStrategy(QDir::current().absolutePath());
    res = formOtherGroup(res);
    foreach(auto x , res.keys())
        cout << x << " " << res[x] << Qt::endl;

    cout << Qt::endl;

    strategy = std::make_shared<ByTypeTraversal>();
    context.setStrategy(strategy);
    res = context.executeStrategy(QDir::current().absolutePath());
    res = formOtherGroup(res);
    foreach(auto x , res.keys())
        cout << x << " " << res[x] << Qt::endl;

    return app.exec();
}
