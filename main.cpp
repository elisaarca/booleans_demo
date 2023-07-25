
#ifdef _MSC_VER // Workaround for known bugs and issues on MSVC
#define _HAS_STD_BYTE 0  // https://developercommunity.visualstudio.com/t/error-c2872-byte-ambiguous-symbol/93889
#define NOMINMAX // https://stackoverflow.com/questions/1825904/error-c2589-on-stdnumeric-limitsdoublemin
#endif

#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>
#include "booleans.h"
#include <cinolib/profiler.h>
#include <cinolib/meshes/meshes.h>


void operazioni(std::vector<std::string> a,std::vector<double> b ,std::vector<uint> c,std::vector<uint> d );

int main(int argc, char **argv)
{
    //mesh iniziali
    std::vector<std::string> files;
    files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/bunny.obj");
    files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/cow.obj");
    files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/sfera.obj");

    using namespace cinolib;

    //coniglio
    DrawableTrimesh<> m(files[0].c_str());
    //mucca
    DrawableTrimesh<> m2(files[1].c_str());
    //sfera
    DrawableTrimesh<> m3(files[2].c_str());

    DrawableTrimesh<> arr_mesh[2];

    DrawableTrimesh<> m1;

    DrawableTrimesh<> mresult;

    GLcanvas gui;
    SurfaceMeshControls<DrawableTrimesh<>> mesh_controls(&m, &gui);
    float current_size = 0.1 / m.bbox().diag();

    //le due mesh vengono pushate nella gui
    gui.push(&arr_mesh[0]);
    gui.push(&arr_mesh[1]);

    arr_mesh[0].updateGL();
    arr_mesh[1].updateGL();

    m.show_vert_color();
    m2.show_vert_color();

    //le mesh vengono colorate
    arr_mesh[0].poly_set_color(cinolib::Color::PASTEL_PINK());
    arr_mesh[1].poly_set_color(cinolib::Color::PASTEL_VIOLET());


    //tutto questo mi serve per salvare le informazioni delle mesh su cui sto lavorando
    std::vector<double> in_coords, bool_coords;
    std::vector<uint> in_tris, bool_tris;
    std::vector<uint> in_labels;
    std::vector<std::bitset<NBIT>> bool_labels;

    //"riempie i vettori" usando le mesh presenti in files. Dovrà essere caricato su una mesh
    loadMultipleFiles(files, in_coords, in_tris, in_labels);
    m.updateGL();
    initFPU();

    point_arena arena;
    std::vector<genericPoint*> arr_verts; // <- it contains the original expl verts + the new_impl verts
    std::vector<uint> arr_in_tris, arr_out_tris;
    std::vector<std::bitset<NBIT>> arr_in_labels;
    std::vector<DuplTriInfo> dupl_triangles;
    Labels labels;
    std::vector<phmap::flat_hash_set<uint>> patches;
    cinolib::FOctree octree; // built with arr_in_tris and arr_in_labels


    customArrangementPipeline(in_coords, in_tris, in_labels, arr_in_tris, arr_in_labels, arena, arr_verts,
                                arr_out_tris, labels, octree, dupl_triangles);

      FastTrimesh tm(arr_verts, arr_out_tris, true);

      computeAllPatches(tm, labels, patches, true);

      // the informations about duplicated triangles (removed in arrangements) are restored in the original structures
      addDuplicateTrisInfoInStructures(dupl_triangles, arr_in_tris, arr_in_labels, octree);

      // parse patches with octree and rays
      cinolib::vec3d max_coords(octree.nodes[0].bbox.max.x() +0.5, octree.nodes[0].bbox.max.y() +0.5, octree.nodes[0].bbox.max.z() +0.5);
      computeInsideOut(tm, patches, octree, arr_verts, arr_in_tris, arr_in_labels, max_coords, labels);

      //operazioni(files, in_coords, in_tris, in_labels, &labels);
      uint num_tris_in_final_solution;

    //test(arr_mesh);

    gui.callback_app_controls = [&]()
    {

        if(ImGui::Button("mucca")) {
            current_size =  0.1 / m.bbox().diag();
            m1 = m2;
            gui.pop(&m1);
            m1.scale(0.1 / m.bbox().diag());
            m1.updateGL();
        }

        if(ImGui::Button("sfera")) {
            current_size =  0.1 / m.bbox().diag();
            m1 = m3;
            gui.pop(&m1);
            m1.scale(0.1 / m.bbox().diag());;
            m1.updateGL();
        }


            num_tris_in_final_solution = boolIntersection(tm, labels);
            computeFinalExplicitResult(tm, labels, num_tris_in_final_solution, bool_coords, bool_tris, bool_labels, true);
            mresult = DrawableTrimesh(bool_coords, bool_tris);
            mresult.poly_set_color(cinolib::Color::PASTEL_YELLOW());

            gui.pop(&m);
            gui.pop(&m1);
            gui.push(&mresult);

        /*if(ImGui::Button("UNION")) {
            num_tris_in_final_solution = boolUnion(tm, labels);
            computeFinalExplicitResult(tm, labels, num_tris_in_final_solution, bool_coords, bool_tris, bool_labels, true);
            m2 = DrawableTrimesh(bool_coords, bool_tris);
            m2.poly_set_color(cinolib::Color::PASTEL_GREEN());
            //m2.bbox().diag();
            //m2.scale();
            //m2.translate();

            gui.pop(&m);
            gui.pop(&m1);
            gui.push(&m2);
        }*/

        /*if(ImGui::Button("SUBTRACTION")) {
            num_tris_in_final_solution = boolSubtraction(tm, labels);
            computeFinalExplicitResult(tm, labels, num_tris_in_final_solution, bool_coords, bool_tris, bool_labels, true);
            mresult = DrawableTrimesh(bool_coords, bool_tris);
            mresult.poly_set_color(cinolib::Color::PASTEL_YELLOW());

            gui.pop(&m);
            gui.pop(&m1);
            gui.push(&mresult);
        }*/

        ///Scale
        ImGui::Text("Stencil size");
        if(ImGui::SliderFloat("##size", &current_size, m.bbox().diag()*0.01, m.bbox().diag())){

            m1.scale( current_size / m1.bbox().diag());
            m1.updateGL();
        }

        ///Reset
        if(ImGui::SmallButton("Reset"))
        {
            gui.pop(&m);
            gui.pop(&m1);

            files.clear();

            files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/bunny.obj");
            files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/sfera.obj");
            m = DrawableTrimesh("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/bunny.obj");
            m2= DrawableTrimesh("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/cow.obj");
            m3 = DrawableTrimesh("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/sfera.obj");

            gui.push(&m);
            m.updateGL();
        }
    };

    //trovo la posizione del centro della sfera e la sottraggo alle coordinate del punto in cui clicco.
    //A questo punto sarò in grado di sapere di quanto devo traslare la sfera

    ///Picker
    Profiler profiler;
    gui.callback_mouse_left_click = [&](int modifiers) -> bool
    {
        gui.pop(&m1);
        if(modifiers & GLFW_MOD_SHIFT)
        {
            vec3d p;
            vec2d click = gui.cursor_pos();

            if(gui.unproject(click, p)) // transform click in a 3d point
            {
                //profiler.push("Vertex pick"); -> probabilmente serve per verificare le prestazioni
                uint vid = m.pick_vert(p);
                //profiler.pop(); -> probabilmente serve per verificare le prestazioni
                std::cout << "ID " << vid << std::endl; //stampa l'id del vertice ottenuto nella console

                //coordinate del centro della sfera
                vec3d center = m1.bbox().center();

                vec3d reference_point = m.vert(vid);
                vec3d delta = (m1.bbox().center() - reference_point)*-1;

                m1.translate(delta);

                //m.vert_data(vid).color = Color::RED();

                gui.push(&m1);

               //m.updateGL();
               m1.updateGL();

            }
        }
        return false;
    };

    return gui.launch();
}


    /*Se l'estensione è ".obj" o ".OBJ", la funzione legge il file OBJ utilizzando cinolib::read_OBJ,
     * memorizza i vertici e le facce in tmp_verts e tmp_tris, rispettivamente. Quindi, le coordinate
     * dei vertici sono estratte e memorizzate in coords, e gli identificatori dei vertici per ciascuna
     * faccia sono serializzati e assegnati a tris.*/


/*
inline void loadMultipleFiles(const cinolib::DrawableTrimesh<> mesh[], std::vector<double> &coords, std::vector<uint> &tris, std::vector<uint> &labels)
{
    for(uint f_id = 0; f_id < files.size(); f_id++)
    {
        std::vector<double> tmp_coords;
        std::vector<uint> tmp_tris;
