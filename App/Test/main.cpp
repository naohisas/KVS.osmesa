#include <iostream>
#include <sstream>
#include <iomanip>
#include <KVS.osmesa/Lib/OSMesa.h>
#include <KVS.osmesa/Lib/Screen.h>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/HydrogenVolumeData>
#include <kvs/RayCastingRenderer>


int main( int argc, char** argv )
{
    std::cout << "OSMesa version: " << kvs::osmesa::Version() << std::endl;

    kvs::StructuredVolumeObject* volume = NULL;
    if ( argc > 1 ) volume = new kvs::StructuredVolumeImporter( std::string( argv[1] ) );
    else            volume = new kvs::HydrogenVolumeData( kvs::Vec3u( 64, 64, 64 ) );

    kvs::StructuredVolumeObject* object = volume;
    kvs::RayCastingRenderer* renderer = new kvs::RayCastingRenderer();

    kvs::osmesa::Screen screen;
    screen.setGeometry( 0, 0, 512, 512 );
    screen.registerObject( object, renderer );

    for ( size_t i = 0; i < 12; i++ )
    {
        std::stringstream num; num << std::setw(3) << std::setfill('0') << i;
        std::string filename = "output_" + num.str() + ".bmp";

        std::cout << "rendering to ... " << std::flush;
        object->multiplyXform( kvs::Xform::Rotation( kvs::Mat3::RotationY( 30 ) ) );
        screen.draw();
        screen.capture().write( filename );
        std::cout << filename << std::endl;
    }

    return 0;
}