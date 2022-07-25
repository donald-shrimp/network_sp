#include "httplib.h"
#include <stdlib.h>
int main(int argc, char **argv){
    int port = 1234;
    if (argc >= 2){ // コマンドライン引数によるポート番号の指定
        port = atoi(argv[1]);
    }
    httplib::Server svr;
    std::vector<std::string> uri; // 接続情報の保存先
    svr.Post("/", [&](const httplib::Request &req, httplib::Response &res,
                      const httplib::ContentReader &content_reader)
             {
    if (req.is_multipart_form_data()) {
        httplib::MultipartFormDataItems files;content_reader([&](const httplib::MultipartFormData &file) {
            files.push_back(file);
            return true;
        },
    [&](const char *data, size_t data_length) {
        files.back().content.append(data, data_length);
        return true;
        }
    );

std::cout << files.back().content << std::endl;
if(files.back().name == "stop"){
    svr.stop(); // サーバの停止
}
if(files.back().name == "connection"){
    uri.push_back(files.back().content);// 接続情報の保存
}
if(files.back().name == "msg"){
    for(auto v : uri){ // 保存した接続先すべてにPost
        httplib::Client cli(v);
        cli.Post("/", files); //受信データをそのまま送信
    }
}
} });
    std::thread th([&]()
                   { svr.listen("localhost", port); });
    char http[128];
    sprintf(http, "http://localhost:%d", port); // 接続情報の文字列の生成
    httplib::Client cli(http);
    while (1)
    {
        std::cout << "Remoete URI:";
        char RemoteURI[128];
        scanf("%s", RemoteURI);
        //送信先の指定
        // http://<ホスト名 or IPアドレス>:<ポート番号>
        std::cout << "name:";
        char name[128];
        scanf("%s", name);
        //データの種類の指定
        // stop, connection, msgのどれか
        std::cout << "content:";
        char content[128];
        scanf("%s", content);
        //データ本体の指定

        httplib::MultipartFormDataItems items = {
            {name, content, name, "text/plain"}
            // scanfで取り込んだデータを指定
        };
        httplib::Client cli(RemoteURI);
        // 接続先をscanfで取り込んだ情報に指定
        cli.Post("/", items);
        if (strcmp(name, "stop") == 0)
            break;
        // stopの場合whileを抜ける
    }

    httplib::MultipartFormDataItems stop = {
        {"stop", "stop server", "stop", "text/plain"}};
    cli.Post("/", stop); //サーバ停止の送信
    th.join();
    return 0;
}