
#ifdef _MSC_VER // Workaround for known bugs and issues on MSVC
#define _HAS_STD_BYTE 0  // https://developercommunity.visualstudio.com/t/error-c2872-byte-ambiguous-symbol/93889
#define NOMINMAX // https://stackoverflow.com/questions/1825904/error-c2589-on-stdnumeric-limitsdoublemin
#endif

#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>
#include "booleans.h"
#include <cinolib/profiler.h>
#include <cinolib/meshes/meshes.h>

inline void loadMultipleMesh(const cinolib::DrawableTrimesh<> *mesh, int dim, std::vector<double> &coords, std::vector<uint> &tris, std::vector<uint> &labels);

int main(int argc, char **argv)
{
    int i;
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

    int array_size = 10;
    auto* arr_mesh = new DrawableTrimesh<>[array_size];

    const char* camera; //stringa che contiene le informazioni della camera

    arr_mesh[0] = m; //carica il coniglio
    //arr_mesh[1] = m2; //carica la mucca
    //arr_mesh[2] = m3; //carica la sfera

    int size = 0;

    DrawableTrimesh<> m1;

    DrawableTrimesh<> mresult;

    GLcanvas gui;
    SurfaceMeshControls<DrawableTrimesh<>> mesh_controls(&m, &gui);
    float current_size = 0.1 / m.bbox().diag();

    //le due mesh vengono pushate nella gui
    gui.push(&arr_mesh[0]);
    //gui.push(&arr_mesh[1]);

    //arr_mesh[0].updateGL();
    //arr_mesh[1].updateGL();

    arr_mesh[0].show_vert_color();
    //m.show_vert_color();
    //m2.show_vert_color();

    //le mesh vengono colorate
    arr_mesh[0].poly_set_color(cinolib::Color::PASTEL_PINK());
    //arr_mesh[1].poly_set_color(cinolib::Color::PASTEL_VIOLET());
    arr_mesh[0].updateGL();


    //tutto questo mi serve per salvare le informazioni delle mesh su cui sto lavorando
    std::vector<double> in_coords, bool_coords;
    std::vector<uint> in_tris, bool_tris;
    std::vector<uint> in_labels;
    std::vector<std::bitset<NBIT>> bool_labels;


    gui.callback_app_controls = [&]()
    {

        if(ImGui::Button("mucca")) {
            ++size;
            current_size =  0.1 / m.bbox().diag();
            arr_mesh[size] = m2;
            gui.pop(&arr_mesh[size]);
            arr_mesh[size].scale(0.1 / m.bbox().diag());
            arr_mesh[size].updateGL();
        }

        if(ImGui::Button("sfera")) {
            ++size;
            current_size =  0.1 / m.bbox().diag();
            arr_mesh[size] = m3;
            gui.pop(&arr_mesh[size]);
            arr_mesh[size].scale(0.1 / m.bbox().diag());;
            arr_mesh[size].updateGL();
        }

        if(ImGui::Button("SUBTRACTION")) {

            in_coords.clear();
            bool_coords.clear();
            in_tris.clear();
            bool_tris.clear();
            in_labels.clear();
            bool_labels.clear();

            //stampa size
            std::cout << "size: " << size << std::endl;

            //arr_mesh[1] -> save("/Users/elisa/Desktop/stencil.obj");
            //int arraySize = sizeof(arr_mesh) / sizeof(arr_mesh[0]);
            loadMultipleMesh(arr_mesh, size, in_coords, in_tris, in_labels);

            booleanPipeline(in_coords, in_tris, in_labels, SUBTRACTION, bool_coords, bool_tris, bool_labels);
            mresult = DrawableTrimesh(bool_coords, bool_tris);

            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());


            for (i=0; i <= size; i++) {
                gui.pop(&arr_mesh[i]);
                arr_mesh[i].updateGL();
            }

            gui.push(&mresult);

            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            arr_mesh[0] = mresult;

            arr_mesh[0].updateGL();

            size = 0;
        }


        if(ImGui::Button("UNION")) {

            in_coords.clear();
            bool_coords.clear();
            in_tris.clear();
            bool_tris.clear();
            in_labels.clear();
            bool_labels.clear();

            loadMultipleMesh(arr_mesh, size, in_coords, in_tris, in_labels);

            booleanPipeline(in_coords, in_tris, in_labels, UNION, bool_coords, bool_tris, bool_labels);
            mresult = DrawableTrimesh(bool_coords, bool_tris);

            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());

            for (i=0; i <= size; i++) {
                gui.pop(&arr_mesh[i]);
                arr_mesh[i].updateGL();
            }

            gui.push(&mresult);

            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            arr_mesh[0] = mresult;

            gui.pop(&mresult);
            mresult.updateGL();

            arr_mesh[0].updateGL();

            size = 0;
        }


        ///Scale
        ImGui::Text("Stencil size");
        if(ImGui::SliderFloat("##size", &current_size, arr_mesh[0].bbox().diag()*0.01, arr_mesh[0].bbox().diag())){

            arr_mesh[size].scale( current_size / arr_mesh[size].bbox().diag());
            arr_mesh[size].updateGL();
        }

        ///Reset
        if(ImGui::SmallButton("Reset"))
        {

            for (i=0; i <= size; i++) {
                gui.pop(&arr_mesh[i]);
                arr_mesh[i].updateGL();
            }

            gui.pop(&mresult);
            mresult.updateGL();
            arr_mesh[0] = DrawableTrimesh("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/bunny.obj");
            gui.push(&arr_mesh[0]);
            arr_mesh[0].updateGL();
            size = 0;
        }
    };

    //trovo la posizione del centro della sfera e la sottraggo alle coordinate del punto in cui clicco.
    //A questo punto sarò in grado di sapere di quanto devo traslare la sfera

    ///Picker
    Profiler profiler;
    gui.callback_mouse_left_click = [&](int modifiers) -> bool
    {

        //gui.pop(&m1);
        if(modifiers & GLFW_MOD_SHIFT && size > 0)
        {
            //salva dati camera
            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());

            vec3d p;
            vec2d click = gui.cursor_pos();

            if(gui.unproject(click, p)) // transform click in a 3d point
            {
                //profiler.push("Vertex pick"); -> probabilmente serve per verificare le prestazioni
                uint vid = arr_mesh[0].pick_vert(p);
                //profiler.pop(); -> probabilmente serve per verificare le prestazioni
                std::cout << "ID " << vid << std::endl; //stampa l'id del vertice ottenuto nella console

                //coordinate del centro della mesh
                vec3d center = arr_mesh[size].bbox().center();
                //vec3d center = m1.bbox().center();

                vec3d reference_point = arr_mesh[0].vert(vid);
                vec3d delta = (arr_mesh[size].bbox().center() - reference_point)*-1;

                arr_mesh[size].translate(delta);

                gui.push(&arr_mesh[size]);

                //riporta la base nella corretta posizione
                gui.camera.deserialize(glfwGetClipboardString(gui.window));
                glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
                gui.update_GL_matrices();

                arr_mesh[size].updateGL();
            }
        }
        return false;
    };

    return gui.launch();
}

inline void loadMultipleMesh(const cinolib::DrawableTrimesh<> *mesh, int dim, std::vector<double> &coords, std::vector<uint> &tris, std::vector<uint> &labels)
{

    for(uint f_id = 0; f_id <= dim; f_id++)
    {
        std::vector<double> tmp_coords; //vettore di coordinate 3d temporanee
        std::vector<uint> tmp_tris; //vettore di indici di triangoli

        tmp_coords = cinolib::serialized_xyz_from_vec3d(mesh[f_id].vector_verts());
        tmp_tris = cinolib::serialized_vids_from_polys(mesh[f_id].vector_polys());

        uint off = static_cast<uint>(coords.size() / 3); // prev num verts

        coords.insert(coords.end(), tmp_coords.begin(), tmp_coords.end());

        for(auto &i : tmp_tris) tris.push_back(i + off);

        for(uint i = 0; i < tmp_tris.size() / 3; i++)
            labels.push_back(f_id);
    }
}





