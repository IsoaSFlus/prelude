#ifndef TIDAL_CORE_H
#define TIDAL_CORE_H

#include <QtCore>
#include <QNetworkAccessManager>
#include <unordered_map>
#include <unordered_set>

#include "album.h"

namespace TidalCore {

class Tidal : public QObject {
    Q_OBJECT

public:
    explicit Tidal(QObject *parent = nullptr);

    void search(QString keywords);
    void searchByUPC(QString upc, QString title);
    void queryAlbum();
    void startRequest(const QUrl &requestedUrl);
    void sortResult();
    void printResult();
    void clear();

signals:
    void searchFinished(uint mask);
    void searchByUPCFinished(std::vector<AlbumCore::Track>, std::string, std::string);

private:
    QNetworkAccessManager* qnam;
//    std::map<uint, TidalCore::Album> albums_map;
//    std::vector<Album> detail_albums;
    std::unordered_set<int> detail_albums;
    std::unordered_map<int, std::string> unchecked_albums; // aid, title
    bool is_search_upc = false;
    bool is_search_upc_step2 = false;
    bool is_search_step1 = true;
    bool is_search_step2 = false;
    std::string upc;
    uint finished_count = 0;
    uint request_count = 0;

private slots:
    void httpFinished(QNetworkReply *reply);
//    void httpReadyRead();

};

}


#endif // TIDAL_CORE_H
