//https://www.reddit.com/svc/shreddit/edit-avatar-accessories-tab/Tops

#include <nodepp/nodepp.h>
#include <nodepp/https.h>
#include <nodepp/path.h>
#include <nodepp/fs.h>

using namespace nodepp;

void get_svg_list( const string_t& path, const string_t& htap ) {

    auto file = fs::readable( path + ".html" );
    auto fout = fs::writable( htap + ".txt" );
    auto data = stream::await( file );

    auto list = regex::match_all( data, "snoo_assets[^.]+\\.svg" );

    for( auto x=list.size(); x--; ){
         fout.write( list[x] + ( x>0 ? "\n" : "" ) );
    }

}

void onMain(){

    for( auto &x: fs::read_folder("./List") ){
        auto base = path::basename(x,"\\..+");
        get_svg_list( 
            path::join( "./List", base ),
            path::join( "./Done", base )
        );  console::done( "->", x );
    }

}