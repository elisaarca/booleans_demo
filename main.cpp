
#ifdef _MSC_VER // Workaround for known bugs and issues on MSVC
#define _HAS_STD_BYTE 0  // https://developercommunity.visualstudio.com/t/error-c2872-byte-ambiguous-symbol/93889
#define NOMINMAX // https://stackoverflow.com/questions/1825904/error-c2589-on-stdnumeric-limitsdoublemin
#endif

#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>
#include <cinolib/extrude_mesh.h>
#include "booleans.h"
#include <cinolib/profiler.h>
#include <cinolib/meshes/meshes.h>



int main(int argc, char **argv)
{
    //mesh iniziali
    std::vector<std::string> files;
    files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/bunny.obj");
    //files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/cow.obj");
    files.push_back("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/sfera.obj");

    using namespace cinolib;

    DrawableTrimesh<> m(files[0].c_str());
    DrawableTrimesh<> m1(files[1].c_str());
    DrawableTrimesh<> m2;

    GLcanvas gui;
    SurfaceMeshControls<DrawableTrimesh<>> mesh_controls(&m, &gui);
    float stencil_size = 0.01f;

    //le due mesh vengono pushate nella gui
    gui.push(&m);
    gui.push(&m1);

    m.show_vert_color();
    //m1.show_vert_color();

    //le mesh vengono colorate
    m.poly_set_color(cinolib::Color::PASTEL_PINK());
    m1.poly_set_color(cinolib::Color::PASTEL_VIOLET());

    std::vector<double> in_coords, bool_coords;
    std::vector<uint> in_tris, bool_tris;
    std::vector<uint> in_labels;
    std::vector<std::bitset<NBIT>> bool_labels;

    //"riempie i vettori" usando le mesh presenti in files. Dovrà essere caricato su una mesh
    loadMultipleFiles(files, in_coords, in_tris, in_labels);

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

    uint num_tris_in_final_solution;


    DrawableTrimesh<> m4 ("/Users/elisa/Desktop/I.obj");
    extrude_mesh(m4, vec3d(0,0,1));


    gui.callback_app_controls = [&]()
    {

        if(ImGui::Button("INTERSECTION")) {
            num_tris_in_final_solution = boolIntersection(tm, labels);
            computeFinalExplicitResult(tm, labels, num_tris_in_final_solution, bool_coords, bool_tris, bool_labels, true);
            m2 = DrawableTrimesh(bool_coords, bool_tris);
            m2.poly_set_color(cinolib::Color::PASTEL_RED());

            gui.pop(&m);
            gui.pop(&m1);
            gui.push(&m2);
        }

        if(ImGui::Button("UNION")) {
            num_tris_in_final_solution = boolUnion(tm, labels);
            computeFinalExplicitResult(tm, labels, num_tris_in_final_solution, bool_coords, bool_tris, bool_labels, true);
            m2 = DrawableTrimesh(bool_coords, bool_tris);
            m2.poly_set_color(cinolib::Color::PASTEL_GREEN());
            m2.bbox().diag();
            //m2.scale();
            //m2.translate();

            gui.pop(&m);
            gui.pop(&m1);
            gui.push(&m2);
        }

        if(ImGui::Button("SUBTRACTION")) {
            num_tris_in_final_solution = boolSubtraction(tm, labels);
            computeFinalExplicitResult(tm, labels, num_tris_in_final_solution, bool_coords, bool_tris, bool_labels, true);
            m2 = DrawableTrimesh(bool_coords, bool_tris);
            m2.poly_set_color(cinolib::Color::PASTEL_YELLOW());

            gui.pop(&m);
            //gui.pop(&m1);
            gui.push(&m2);
        }

        int n_points = 1000;
        ImGui::Text("Brush size");
        if(ImGui::SliderFloat("##size", &stencil_size, 0.1f, 5.0f)){
            m1.scale(stencil_size);
            m1.updateGL();
        };

        if(ImGui::SmallButton("Reset"))
        {
            m.vert_set_color(Color::WHITE());
            gui.pop(&m);
            gui.pop(&m1);
            m1 = DrawableTrimesh("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/sfera.obj");
            gui.push(&m);
            gui.push(&m1);
            m.updateGL();
            m1.updateGL();
        }


    };

    Profiler profiler;
    gui.callback_mouse_left_click = [&](int modifiers) -> bool
    {
        if(modifiers & GLFW_MOD_SHIFT)
        {
            vec3d p;
            vec2d click = gui.cursor_pos();
            if(gui.unproject(click, p)) // transform click in a 3d point
            {
                profiler.push("Vertex pick");
                uint vid = m.pick_vert(p);
                profiler.pop();
                std::cout << "ID " << vid << std::endl;
                m.vert_data(vid).color = Color::RED();
                m.updateGL();
            }
        }
        return false;
    };

    return gui.launch();
}
