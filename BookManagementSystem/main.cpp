#include "main.h"

int main(int argc, char *argv[])
{
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8");//情况2
    //QTextCodec::setCodecForTr(codec);
    //QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);

    QCoreApplication::addLibraryPath("/Users/zuhxs/Qt5.9.3_2/5.9.3/clang_64/plugins/sqldrivers");

    //QSqlQuery query(db);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


