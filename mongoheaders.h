#ifndef MONGOHEADERS_H
#define MONGOHEADERS_H


#include <mongocxx/collection.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/gridfs/bucket.hpp>
#include <mongocxx/gridfs/downloader.hpp>
#include <mongocxx/gridfs/uploader.hpp>
#include <mongocxx/result/insert_one.hpp>
#include <mongocxx/result/delete.hpp>
#include <mongocxx/result/update.hpp>
#include <mongocxx/result/replace_one.hpp>
#include <mongocxx/options/find.hpp>


#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>

#include <bsoncxx/exception/exception.hpp>

#endif // MONGOHEADERS_H
