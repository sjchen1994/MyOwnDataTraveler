#include <QCoreApplication>
#include <QAxObject>
#include <QFile>
#include <QDebug>
#include <QtAlgorithms>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QMap<QString, QString> frommap;
    QVector<QString> orimap;
    QMap<QString, QString> tomap;
    QFile filefrom1("C:\\Users\\chenshijun\\Desktop\\bematched.txt");
    QString rl_data;
    if(!filefrom1.open(QIODevice::ReadOnly | QIODevice::Text)){
    }
    QTextStream stream1(&filefrom1);
    while(true){
        rl_data = stream1.readLine();
        if(stream1.atEnd()){
            break;
        }
        QString data;
        QString com_name;
        QString indu_name;

        QString::iterator it = rl_data.begin();
        while(true){
            if(*it == "\t"){
                com_name = data;
                data.clear();
                it++;
            }
            if(it == rl_data.end()){
                indu_name = data;
                data.clear();
                break;
            }
            data += *it;
            it++;
        }
        if(frommap.find(com_name) == frommap.end()){
            frommap.insert(com_name, indu_name);
        }
    }
    filefrom1.close();


    QFile filefrom2("C:\\Users\\chenshijun\\Desktop\\match.txt");
    if(!filefrom2.open(QIODevice::ReadOnly | QIODevice::Text)){
    }
    QTextStream stream2(&filefrom2);

    while(true){
        rl_data = stream2.readLine();
        if(rl_data == ""){
            break;
        }
        orimap.append(rl_data);
    }

    filefrom2.close();

    int matched = 0;

    for(QString compa:orimap){
        for(auto it = frommap.begin(); it != frommap.end(); it++){
            if(it.key() == compa){
                matched = 1;
                tomap.insert(compa, it.value());
                break;
            }
        }
        if(matched == 1){
            matched = 0;
            continue;
        }
        else{
            tomap.insert(compa, "not matched");
        }
    }

    QFile data("C:\\Users\\chenshijun\\Desktop\\final.txt");
    if(data.open(QFile::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        QTextStream out(&data);
        for(auto it = tomap.begin(); it != tomap.end(); it++){
            out<<it.key()<<"\t"<<it.value()<<endl;
        }
    }
    data.close();
    return a.exec();
}
