
#ifdef _MSC_VER // Workaround for known bugs and issues on MSVC
#define _HAS_STD_BYTE 0  // https://developercommunity.visualstudio.com/t/error-c2872-byte-ambiguous-symbol/93889
#define NOMINMAX // https://stackoverflow.com/questions/1825904/error-c2589-on-stdnumeric-limitsdoublemin
#endif
#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>
#include "booleans.h"


int main(int argc, char **argv)
{
    std::vector<std::string> files;
    files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/bunny.obj");
    files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/cow.obj");
    using namespace cinolib;
    DrawableTrimesh<> m(files[0].c_str());
    DrawableTrimesh<> m1(files[1].c_str());

    GLcanvas gui;
    SurfaceMeshControls<DrawableTrimesh<>> mesh_controls(&m, &gui);

    //le due mesh vengono pushate nella gui
    gui.push(&m);
    gui.push(&m1);

    //le mesh vengono colorate
    m.poly_set_color(cinolib::Color::PASTEL_PINK());
    m1.poly_set_color(cinolib::Color::PASTEL_VIOLET());

    BoolOp op;
    std::string file_out;

    //operazioni booleane possibili
    //op = INTERSECTION;
    //op = UNION;
    op = SUBTRACTION;
    //op = XOR;

    gui.callback_app_controls = [&]()
    {
        if(ImGui::Button("Operazione booleana"))
        {
            //button clicked:
            //fai l'operazione booleana tra le mesh
            //metti il risultato in m2

            //mi dichiaro questi
            std::vector<double> in_coords, bool_coords;
            std::vector<uint> in_tris, bool_tris;
            std::vector<uint> in_labels;
            std::vector<std::bitset<NBIT>> bool_labels;

            //poi faccio partire questa che "riempie i vettori" mette tutto in un file. Io lo dovrò caricare su una mesh
            loadMultipleFiles(files, in_coords, in_tris, in_labels);
            booleanPipeline(in_coords, in_tris, in_labels, op, bool_coords, bool_tris, bool_labels);

            cinolib::write_OBJ(file_out.c_str(), bool_coords, bool_tris, {});


            //togli m e m1 dalla gui e inserisci m2
            gui.pop(&m);
            gui.pop(&m1);
            //gui.push(&m2);
        }
    };
    return gui.launch();
}
    /*


    if(argc < 5)
    {
        std::cout << "syntax error!" << std::endl;
        std::cout << "./exact_boolean BOOL_OPERATION (intersection OR union OR subtraction) input1.obj input2.obj output.obj" << std::endl;
        return -1;
    }
    else
    {
        if (strcmp(argv[1], "intersection") == 0)       op = INTERSECTION;
        else if (strcmp(argv[1], "union") == 0)         op = UNION;
        else if (strcmp(argv[1], "subtraction") == 0)   op = SUBTRACTION;
        else if (strcmp(argv[1], "xor") == 0)           op = XOR;
    }*/

    /*for(int i = 2; i < (argc -1); i++)
        files.emplace_back(argv[i]);

    file_out = argv[argc-1];*/

    /*
    std::vector<double> in_coords, bool_coords;
    std::vector<uint> in_tris, bool_tris;
    std::vector<uint> in_labels;
    std::vector<std::bitset<NBIT>> bool_labels;

    loadMultipleFiles(files, in_coords, in_tris, in_labels);

    booleanPipeline(in_coords, in_tris, in_labels, op, bool_coords, bool_tris, bool_labels);

    cinolib::write_OBJ(file_out.c_str(), bool_coords, bool_tris, {});*/

   // return 0;
//}