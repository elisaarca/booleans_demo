
#ifdef _MSC_VER // Workaround for known bugs and issues on MSVC
#define _HAS_STD_BYTE 0  // https://developercommunity.visualstudio.com/t/error-c2872-byte-ambiguous-symbol/93889
#define NOMINMAX // https://stackoverflow.com/questions/1825904/error-c2589-on-stdnumeric-limitsdoublemin
#endif

#include <cinolib/gl/glcanvas.h>
#include <cinolib/gl/surface_mesh_controls.h>
#include "booleans.h"
#include <cinolib/profiler.h>
#include <cinolib/meshes/meshes.h>


inline void loadMultipleMesh(std::vector<cinolib::DrawableTrimesh<>> &mesh, int dim, std::vector<double> &coords, std::vector<uint> &tris, std::vector<uint> &labels);

int main(int argc, char **argv)
{

    using namespace cinolib;

    ///Mesh
    //base
    DrawableTrimesh<> m("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/bunny.obj");

    ///letters
    DrawableTrimesh<> letterE("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/letters/letterE.obj");
    DrawableTrimesh<> letterL("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/letters/letterL.obj");
    DrawableTrimesh<> letterI("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/letters/letterI.obj");
    DrawableTrimesh<> letterS("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/letters/letterS.obj");
    DrawableTrimesh<> letterA("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/letters/letterA.obj");

    ///shapes
    DrawableTrimesh<> sphere("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/sphere.obj");
    DrawableTrimesh<> heart("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/shapes/heart.obj");
    DrawableTrimesh<> star("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/shapes/star.obj");
    DrawableTrimesh<> triangle ("/Users/elisa/Desktop/Tirocinio/booleans_demo/data/shapes/triangle.obj");

    int i;
    int index = 0;
    bool flag= true;
    GLcanvas gui;

    DrawableTrimesh<> m1;
    DrawableTrimesh<> mresult;
    std::vector<DrawableTrimesh<>> myvector;
    myvector.push_back(m); //carica il coniglio

    float current_size = 0.1 / m.bbox().diag();
    float current_angle = 0 ;
    //la mesh del coniglio viene pushata nella gui
    gui.push(&myvector[0]);

    //le mesh vengono colorate
    //myvector[0].show_vert_color();
    //myvector[0].show_poly_color();
    //myvector[0].poly_set_color(cinolib::Color::PASTEL_PINK());
    //myvector[0].updateGL();

    //tutto questo mi serve per salvare le informazioni delle mesh su cui sto lavorando
    std::vector<double> in_coords, bool_coords;
    std::vector<uint> in_tris, bool_tris;
    std::vector<uint> in_labels;
    std::vector<std::bitset<NBIT>> bool_labels;

    //opzioni che mi permettono di salvare etc.
    SurfaceMeshControls<DrawableTrimesh<>> mesh_controls(&mresult, &gui, "mesh.obj");
    gui.push(&mesh_controls);

    gui.callback_app_controls = [&]()
    {

        ///Stencils
        ImGui::Text("");
        ImGui::Text("STENCILS");
        ImGui::Text("> letters");
        if(ImGui::Button("E")) {

            //ctrl c - posizione camera
            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());
            ++index;
            current_size =  float(0.1 / myvector[0].bbox().diag());

            for (i=0; i<index; i++) {
                gui.pop(&myvector[i]);
            }

            if (!flag ) {
                myvector.pop_back();
                index--;
            }
            myvector.push_back(letterE);

            for (i=0; i<index; i++) {
                gui.push(&myvector[i]);
            }

            myvector[index].scale(0.01 / myvector[0].bbox().diag());

            //ctrl v - posizione camera
            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            gui.pop(&myvector[index]);
            myvector[i].updateGL();
            flag = false;
        }
        ImGui::SameLine();
        if(ImGui::Button("L")) {

            //ctrl c - posizione camera
            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());
            ++index;
            current_size =  float(0.1 / myvector[0].bbox().diag());

            for (i=0; i<index; i++) {
                gui.pop(&myvector[i]);
            }

            if (!flag ) {
                myvector.pop_back();
                index--;
            }
            myvector.push_back(letterL);

            for (i=0; i<index; i++) {
                gui.push(&myvector[i]);
            }

            myvector[index].scale(0.01 / myvector[0].bbox().diag());

            //ctrl v - posizione camera
            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            gui.pop(&myvector[index]);
            myvector[i].updateGL();
            flag = false;
        }
        ImGui::SameLine();
        if(ImGui::Button("I")) {

            //ctrl c - posizione camera
            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());
            ++index;
            current_size =  float(0.1 / myvector[0].bbox().diag());

            for (i=0; i<index; i++) {
                gui.pop(&myvector[i]);
            }

            if (!flag ) {
                myvector.pop_back();
                index--;
            }
            myvector.push_back(letterI);

            for (i=0; i<index; i++) {
                gui.push(&myvector[i]);
            }

            myvector[index].scale(0.01 / myvector[0].bbox().diag());

            //ctrl v - posizione camera
            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            gui.pop(&myvector[index]);
            myvector[i].updateGL();
            flag = false;
        }
        ImGui::SameLine();
        if(ImGui::Button("S")) {

            //ctrl c - posizione camera
            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());
            ++index;
            current_size =  float(0.1 / myvector[0].bbox().diag());

            for (i=0; i<index; i++) {
                gui.pop(&myvector[i]);
            }

            if (!flag ) {
                myvector.pop_back();
                index--;
            }
            myvector.push_back(letterS);

            for (i=0; i<index; i++) {
                gui.push(&myvector[i]);
            }

            myvector[index].scale(0.01 / myvector[0].bbox().diag());

            //ctrl v - posizione camera
            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            gui.pop(&myvector[index]);
            myvector[i].updateGL();
            flag = false;
        }
        ImGui::SameLine();
        if(ImGui::Button("A")) {

            //ctrl c - posizione camera
            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());
            ++index;
            current_size =  0.01 / myvector[0].bbox().diag();

            for (i=0; i<index; i++) {
                gui.pop(&myvector[i]);
            }

            if (!flag ) {
                myvector.pop_back();
                index--;
            }
            myvector.push_back(letterA);

            for (i=0; i<index; i++) {
                gui.push(&myvector[i]);
            }

            myvector[index].scale(0.01 / myvector[0].bbox().diag());

            //ctrl v - posizione camera
            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            gui.pop(&myvector[index]);
            myvector[i].updateGL();
            flag = false;
        }

        ImGui::Text( "");
        ImGui::Text("> shapes");

        if(ImGui::Button("sphere")) {

            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());
            ++index;
            current_size =  0.1 / myvector[0].bbox().diag();

            for (i=0; i<index; i++) {
                gui.pop(&myvector[i]);
            }
            if (!flag ) {
                myvector.pop_back();
                index--;
            }

            myvector.push_back(sphere);

            for (i=0; i<index; i++) {
                gui.push(&myvector[i]);
            }

            myvector[index].scale(0.1 / myvector[0].bbox().diag());

            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            gui.pop(&myvector[index]);
            myvector[index].updateGL();
            flag = false;
        }

        if(ImGui::Button("heart")) {

            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());
            ++index;
            current_size =  float(0.1 / myvector[0].bbox().diag());

            for (i=0; i<index; i++) {
                gui.pop(&myvector[i]);
            }
            if (!flag ) {
                myvector.pop_back();
                index--;
            }

            myvector.push_back(heart);

            for (i=0; i<index; i++) {
                gui.push(&myvector[i]);
            }

            myvector[index].scale(0.01 / myvector[0].bbox().diag());

            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            gui.pop(&myvector[index]);
            myvector[index].updateGL();
            flag = false;
        }

        if(ImGui::Button("star")) {

            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());
            ++index;
            current_size =  float(0.1 / myvector[0].bbox().diag());

            for (i=0; i<index; i++) {
                gui.pop(&myvector[i]);
            }
            if (!flag ) {
                myvector.pop_back();
                index--;
            }

            myvector.push_back(star);

            for (i=0; i<index; i++) {
                gui.push(&myvector[i]);
            }

            myvector[index].scale(0.01 / myvector[0].bbox().diag());

            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            gui.pop(&myvector[index]);
            myvector[index].updateGL();
            flag = false;
        }

        if(ImGui::Button("triangle")) {

            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());
            ++index;
            current_size =  float(0.1 / myvector[0].bbox().diag());

            for (i=0; i<index; i++) {
                gui.pop(&myvector[i]);
            }
            if (!flag ) {
                myvector.pop_back();
                index--;
            }

            myvector.push_back(triangle);

            for (i=0; i<index; i++) {
                gui.push(&myvector[i]);
            }

            myvector[index].scale(0.01 / myvector[0].bbox().diag());

            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            gui.pop(&myvector[index]);
            myvector[index].updateGL();
            flag = false;
        }

        ///Boolean Operations
        ImGui::Text("");
        ImGui::Text("BOOLEAN OPERATIONS");
        if(ImGui::Button("subtraction")) {

            in_coords.clear();
            bool_coords.clear();
            in_tris.clear();
            bool_tris.clear();
            in_labels.clear();
            bool_labels.clear();

            //stampa size
            std::cout << "size: " << index << std::endl;

            //vengono messi insieme tutti i dati delle mesh
            if (!flag) index = index -1; //se non ho fatto il pick, devo sottrarre 1 all'indice
            loadMultipleMesh(myvector,  index, in_coords, in_tris, in_labels);
            booleanPipeline(in_coords, in_tris, in_labels, SUBTRACTION, bool_coords, bool_tris, bool_labels);
            mresult = DrawableTrimesh(bool_coords, bool_tris);

            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());

            for (i=0; i<=index; i++) {
                gui.pop(&myvector[i]);
            }

            //ripulisce completamente il vettore
            myvector.clear();

            myvector.push_back(mresult);
            gui.push(&myvector[0]);

            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            myvector[0].updateGL();
            index = 0;
            flag = true;
        }

        if(ImGui::Button("union")) {

            in_coords.clear();
            bool_coords.clear();
            in_tris.clear();
            bool_tris.clear();
            in_labels.clear();
            bool_labels.clear();

            //stampa size
            std::cout << "size: " << index << std::endl;

            //vengono messi insieme tutti i dati delle mesh
            if (!flag) index = index -1; //se non ho fatto il pick, devo sottrarre 1 all'indice
            loadMultipleMesh(myvector,  index, in_coords, in_tris, in_labels);
            booleanPipeline(in_coords, in_tris, in_labels, UNION, bool_coords, bool_tris, bool_labels);
            mresult = DrawableTrimesh(bool_coords, bool_tris);

            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());

            //svuotamento gui -> il vector da problemi se ci sono mesh nella gui
            for (i=0; i<=index; i++) {
                gui.pop(&myvector[i]);
            }

            //ripulisce completamente il vettore
            myvector.clear();

            myvector.push_back(mresult);
            gui.push(&myvector[0]);

            gui.camera.deserialize(glfwGetClipboardString(gui.window));
            glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
            gui.update_GL_matrices();

            myvector[0].updateGL();

            index = 0;
            flag = true;
        }


        ///Scale
        //La scalatura si riferisce sempre all'ultima mesh aggiunta
        ImGui::Text("");
        ImGui::Text("STENCIL SCALE");
        if(ImGui::SliderFloat("##size", &current_size, float(myvector[0].bbox().diag()*0.01), float(myvector[0].bbox().diag())) && index > 0){
            myvector[index].scale( current_size / myvector[index].bbox().diag());
            myvector[index].updateGL();
        }


        ///Rotate
        //La rotazione si riferisce sempre all'ultima mesh aggiunta
        ImGui::Text("");
        ImGui::Text("ROTATION ANGLE");

        ImGui::Text("X axis");
        if(ImGui::Button("^")){
            myvector[index].rotate(vec3d(1, 0, 0), 50);
            myvector[index].updateGL();
        }
        ImGui::SameLine();
        if(ImGui::Button("v")){
            myvector[index].rotate(vec3d(1,0 , 0), -50);
            myvector[index].updateGL();
        }

        ImGui::Text("Y axis");
        if(ImGui::Button("<")){
            myvector[index].rotate(vec3d(0, 1, 0), 50);
            myvector[index].updateGL();
        }
        ImGui::SameLine();
        if(ImGui::Button(">")){
            myvector[index].rotate(vec3d(0, 1, 0), -50);
            myvector[index].updateGL();
        }

        ImGui::Text("Z axis");
        if(ImGui::Button("RH")){
            myvector[index].rotate(vec3d(0, 0, 1), 50);
            myvector[index].updateGL();
        }
        ImGui::SameLine();
        if(ImGui::Button("LH")){
            myvector[index].rotate(vec3d(0, 0, 1), -50);
            myvector[index].updateGL();

        }

        ///Reset
        if(ImGui::SmallButton("Reset"))
        {

            for (i=0; i <= index; i++) {
                gui.pop(&myvector[i]);
                myvector[i].updateGL();
            }

            gui.pop(&mresult);
            mresult.updateGL();

            myvector.clear();

            myvector.push_back(m);
            gui.push(&myvector[0]);
            myvector[0].updateGL();
            index = 0;
            flag = true;

        }
    };

    //trovo la posizione del centro della sfera e la sottraggo alle coordinate del punto in cui clicco.
    //A questo punto sarò in grado di sapere di quanto devo traslare la sfera

    ///Picker
    Profiler profiler;
    gui.callback_mouse_left_click = [&](int modifiers) -> bool
    {

        //gui.pop(&m1);
        if(modifiers & GLFW_MOD_SHIFT && index > 0)
        {
            flag = true;
            //salva dati camera
            glfwSetClipboardString(gui.window, gui.camera.serialize().c_str());

            vec3d p;
            vec2d click = gui.cursor_pos();

            if(gui.unproject(click, p)) // transform click in a 3d point
            {
                //profiler.push("Vertex pick"); -> probabilmente serve per verificare le prestazioni
                uint vid = myvector[0].pick_vert(p);
                //profiler.pop(); -> probabilmente serve per verificare le prestazioni
                std::cout << "ID " << vid << std::endl; //stampa l'id del vertice ottenuto nella console

                //coordinate del centro della mesh
                vec3d center = myvector[index].bbox().center();
                //vec3d center = m1.bbox().center();

                vec3d reference_point = myvector[0].vert(vid);
                vec3d delta = (myvector[index].bbox().center() - reference_point)*-1;

                myvector[index].translate(delta);

                gui.push(&myvector[index]);

                //riporta la base nella corretta posizione
                gui.camera.deserialize(glfwGetClipboardString(gui.window));
                glfwSetWindowSize(gui.window, gui.camera.width, gui.camera.height);
                gui.update_GL_matrices();

                myvector[index].updateGL();
            }
        }
        return false;
    };

    return gui.launch();
}

inline void loadMultipleMesh(std::vector<cinolib::DrawableTrimesh<>> &mesh, int dim, std::vector<double> &coords, std::vector<uint> &tris, std::vector<uint> &labels)
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





