#include <iostream>
#include <string>
#include "httplib.h"
using namespace std;

int main(int argc, char **argv){
    int port = 1234;
    if (argc >= 2){
        // argv[0]が実行ファイル名 [1]以降が実行時の引数
        port = atoi(argv[1]);
    }
    printf("port:%d\n", port);

    // http server
    httplib::Server svr;
    svr.Get("/", [](const httplib::Request &, httplib::Response &res)
            { res.set_content("Hello World!", "text/plain"); });

    svr.Get("/hello", [](const httplib::Request &, httplib::Response &res)
            { res.set_content("Hello", "text/plain"); });

    svr.Get("/world", [](const httplib::Request &, httplib::Response &res)
            { res.set_content("World!", "text/plain"); });
    // 終了処理
    svr.Get("/stop", [&](const httplib::Request &, httplib::Response &res)
            {res.set_content("server stop", "text/plain");svr.stop(); });
    // マルチスレッドでサーバを起動
    std::thread th([&](){ svr.listen("0.0.0.0", port); });

    bool run = true;
    char path[256];
    while (run){    
        char svName[256];
        printf("address:");
        scanf("%s",svName);

        // http client
        httplib::Client cli(svName);

        printf("path: ");
        scanf("%s", path);
        // ループの停止
        if (strcmp(path, "/stop") == 0){
            run = false;
        }
        // Getリクエスト
        auto res = cli.Get(path);
        // Getリクエストの結果を表示
        std::cout << res->status << std::endl;
        std::cout << res->body << std::endl;
    }
    // サーバの終了を待機
    th.join();
    return 0;
}