//#include "roadcadast.h"

//RoadCadast::RoadCadast(QString roads,QString BaseRoads)
//{
//   roadsxlsx= new QXlsx::Document(roads);
//   basexlsx= new QXlsx::Document(BaseRoads);

//   for (int row=1; row<2461; ++row) {
//          if (QXlsx::Cell *cell=roadsxlsx->cellAt(row,2)){
//              QString celledit=cell->value().toString();
//              RoadsList.push_back(celledit);
//          }
//      }
//   SheetBaseList=basexlsx->sheetNames();
//   qDebug()<<RoadsList.size();
//   qDebug()<<SheetBaseList.size();

// }
//void RoadCadast::searchfornumber(UnitTable& unit){
//    for (int row=1; row<10360; ++row) {
//               QXlsx::Cell *cell=basexlsx->cellAt(row, 2);
//                    if(cell->value().toString()==unit.number){
//                    QXlsx::Cell *cellCN=basexlsx->cellAt(row,3);
//                    unit.CadastrNumbers.push_back(cellCN->value().toString());
//                    unit.count++;
//                }

//    }
//}

//bool RoadCadast::searchforname(QString &name){
//    for (int row=1; row<10360; ++row) {
//                QXlsx::Cell *cell=basexlsx->cellAt(row, 1);
//                if(cell->value().toString()==name){
//                   qDebug()<<row<<" RUN Search for Name";
//                   QXlsx::Cell *cellnum=basexlsx->cellAt(row, 2);
//                   UnitTable unit;
//                   unit.name=name;
//                   unit.number=cellnum->value().toString();
//                   numbers.push_back(unit);
//                   return true;
//                }


//    }
//    return false;
//}



//void RoadCadast::SearchMutch(){

//        for(int i=0;i<RoadsList.size();i++){
//            if(searchforname(RoadsList[i])){
//                int row=i+1;
//                QVariant cel=roadsxlsx->read(row,2);
//                QXlsx::Format format;
//                format.setPatternBackgroundColor( Qt::red);
//                roadsxlsx->write(row,2,cel,format);

//            }
//        }
//        if(roadsxlsx->saveAs("D:/OutMatchRoads.xlsx")){
//            qDebug()<<"Save to D:/OutMatchRoads.xlsx";
//        }
//        for (auto& unit:numbers){
//            searchfornumber(unit);

//        }
//        qDebug()<<"Complite";

//}
//void RoadCadast::GetKml(QString &CadastrNumber){
//    std::string com("rosreestr2coord -c ");
//    com+=CadastrNumber.toStdString();
//    if(system(com.c_str())){
//        qDebug()<<"System false";
//    }
//}
//void RoadCadast::AppendKml(){
//    for(auto& i:numbers){
//        i.CadastrNumbers_F=i.CadastrNumbers;
//        i.CadastrNumbers_F.replaceInStrings(":","_");
//        for(auto& c:i.CadastrNumbers){
//           GetKml(c);
//        }
//    }
//}

//void RoadCadast::getNamesKml(){
//    for(auto& i:numbers){
//        i.CadastrNumbers_F=i.CadastrNumbers;
//        i.CadastrNumbers_F.replaceInStrings(":","_");
//         for(auto& c:i.CadastrNumbers_F){
//             QString adress("D:/kml edit/");
//             adress+=c;
//             adress+=".kml";
//             QString adress2("D:/kml edit/edit/");
//             adress2+=c;
//             adress2+=".kml";
//             QFile* file=new QFile(adress);
//             if(file->exists()){
//             if(file->open(QIODevice::WriteOnly|QIODevice::ReadOnly)){
//                 qDebug()<<adress;
//                 QTextStream stream(file);
//                 stream.setCodec(QTextCodec::codecForName("UTF-8"));
//                 QString xml=stream.readAll();
//                 QStringList list=xml.split("<Polygon>");
//                 xml=list[0];
//                 xml+="<Polygon>";
//                 xml+="<name>";
//                 xml+=i.name;
//                 xml+="</name>";
//                 xml+=list[1];
//                 QFile* outfile=new QFile(adress2);
//                 outfile->open(QIODevice::WriteOnly|QIODevice::ReadOnly);
//                 outfile->write(xml.toUtf8());
//                 file->close();
//                 outfile->close();
//             }
//             }

//         }
//    }
//}
