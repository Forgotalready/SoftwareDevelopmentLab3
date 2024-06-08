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
    foreach(auto x , res.keys())
        cout << x << " " << res[x] << Qt::endl;


    strategy = std::make_shared<ByTypeTraversal>();
    context.setStrategy(strategy);
    res = context.executeStrategy(QDir::current().absolutePath());
    foreach(auto x , res.keys())
        cout << x << " " << res[x] << Qt::endl;

    app.exec();
}
