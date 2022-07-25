#include "httplib.h"
int main(void){
using namespace httplib; // httplib:: を省略可能
Server svr; // httplib::Server
svr.Get("/", [](const Request& req, Response& res) {
res.set_content("Hello World!", "text/plain");
});

svr.Get("/hello", [](const Request& req, Response& res) {
res.set_content("hello", "text/plain");
});
svr.Get("/stop", [&](const Request& req, Response& res) {
svr.stop(); // サーバの停止
});
svr.listen("0.0.0.0", 8080);
return 0;
}