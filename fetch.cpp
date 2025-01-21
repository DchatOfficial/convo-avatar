#include <nodepp/nodepp.h>
#include <nodepp/encoder.h>
#include <nodepp/https.h>
#include <nodepp/path.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain(){

    for( auto item: fs::read_folder( "./Done" ) ){ ulong idx = 0;
         auto name=::path::basename(item,"\\..+");
         auto path=::path::join( "./Done", name );
         auto list= regex::split( fs::read_file( path + ".txt" ), "\n" );
         auto file= fs::writable( "./View/assets/css/" + name + ".css" );
    for( auto data: list ){
     
         fetch_t args; ssl_t ssl;
                 args.method = "GET";
                 args.url    = "https://i.redd.it/snoovatar/" + data;
                 args.headers= header_t({ { "User-Agent", "Linux" } });
         
         auto fetch = https::fetch( args, &ssl ).await();
         if( !fetch.has_value() )         { continue; }
         if( fetch.value().status != 200 ){ continue; }

         auto cli = fetch.value(); auto raw = stream::await(cli);
              raw = regex::replace( raw, "lime", "white" );
         auto b64 = encoder::base64::get( raw );

         file.write( regex::format( _STRING_ (
            body:has(input[avatar-${0}][value="${0}-${1}"]:checked) avatar[${0}], 
            avatar[name="${0}-${1}"]{
         ), name, idx ) );

         file.write( "background-repeat: no-repeat;" );
         file.write( "background-image:url(\""       );
         file.write( "data:image/svg+xml;base64, "   ); file.write( b64 );
         
         file.write( regex::format("\"); }") );

         console::log( "->", name, idx ); idx++;
    }}

}