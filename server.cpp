#include <nodepp/nodepp.h>
#include <nodepp/crypto.h>
#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    app.USE( express::http::file("./View") );

    app.listen("localhost",8000,[=](...){
        console::log("-> http://localhost:8000");
    });
    
}