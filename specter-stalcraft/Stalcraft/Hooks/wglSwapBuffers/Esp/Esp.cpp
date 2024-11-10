#include "Esp.h"
#include "../Render/Render.h"
#include "../Render/Menu/Menu.h"

auto Esp::draw() -> void
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (Menu::items_esp) {
        for (auto& item : items) {
            draw_model(item.projection_matrix, item.modelview_matrix, Menu::items_esp_color, { 0.35f,0.35f,0.35f });
        }  
    }
    items.clear();


    glPopMatrix();
    glPopAttrib();
}

void Esp::add_drawing_model(std::vector<drawables>& models, Vector3 offset) {

    GLfloat modelview_matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

    GLfloat projection_matrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix);

    // Применяем смещение к модели
    modelview_matrix[12] += offset.x;
    modelview_matrix[13] += offset.y;
    modelview_matrix[14] += offset.z;
    models.push_back({ projection_matrix, modelview_matrix });
}

auto Esp::draw_model(const GLfloat projection_matrix[16],const GLfloat modelview_matrix[16],const ImVec4& color,const Vector3& box_size) -> void
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();


    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection_matrix);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(modelview_matrix);

    glLineWidth(1.0f);
    glColor4f(color.x, color.y, color.z, color.w);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_LINES);
    glVertex3f(box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glVertex3f(box_size.x / 2, box_size.y / 2, box_size.z / 2);

    glVertex3f(-box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glVertex3f(box_size.x / 2, -box_size.y / 2, box_size.z / 2);

    glVertex3f(-box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glVertex3f(-box_size.x / 2, box_size.y / 2, box_size.z / 2);

    glVertex3f(-box_size.x / 2, box_size.y / 2, box_size.z / 2);
    glVertex3f(box_size.x / 2, box_size.y / 2, box_size.z / 2);

    glVertex3f(box_size.x / 2, box_size.y / 2, box_size.z / 2);
    glVertex3f(box_size.x / 2, box_size.y / 2, -box_size.z / 2);

    glVertex3f(box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glVertex3f(box_size.x / 2, -box_size.y / 2, -box_size.z / 2);

    glVertex3f(box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glVertex3f(-box_size.x / 2, box_size.y / 2, -box_size.z / 2);

    glVertex3f(-box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glVertex3f(-box_size.x / 2, box_size.y / 2, box_size.z / 2);

    glVertex3f(-box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glVertex3f(-box_size.x / 2, -box_size.y / 2, -box_size.z / 2);

    glVertex3f(-box_size.x / 2, -box_size.y / 2, -box_size.z / 2);
    glVertex3f(box_size.x / 2, -box_size.y / 2, -box_size.z / 2);

    glVertex3f(-box_size.x / 2, -box_size.y / 2, -box_size.z / 2);
    glVertex3f(-box_size.x / 2, -box_size.y / 2, box_size.z / 2);

    glVertex3f(box_size.x / 2, -box_size.y / 2, -box_size.z / 2);
    glVertex3f(box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glEnd();

    glColor4f(color.x, color.y, color.z, color.w * 0.2f);

    glBegin(GL_POLYGON);
    glVertex3f(box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glVertex3f(box_size.x / 2, -box_size.y / 2, -box_size.z / 2);
    glVertex3f(-box_size.x / 2, -box_size.y / 2, -box_size.z / 2);
    glVertex3f(-box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(box_size.x / 2, box_size.y / 2, box_size.z / 2);
    glVertex3f(box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glVertex3f(-box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glVertex3f(-box_size.x / 2, box_size.y / 2, box_size.z / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glVertex3f(box_size.x / 2, -box_size.y / 2, -box_size.z / 2);
    glVertex3f(box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glVertex3f(box_size.x / 2, box_size.y / 2, box_size.z / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-box_size.x / 2, box_size.y / 2, box_size.z / 2);
    glVertex3f(-box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glVertex3f(-box_size.x / 2, -box_size.y / 2, -box_size.z / 2);
    glVertex3f(-box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glVertex3f(box_size.x / 2, -box_size.y / 2, -box_size.z / 2);
    glVertex3f(-box_size.x / 2, -box_size.y / 2, -box_size.z / 2);
    glVertex3f(-box_size.x / 2, -box_size.y / 2, box_size.z / 2);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glVertex3f(box_size.x / 2, box_size.y / 2, box_size.z / 2);
    glVertex3f(-box_size.x / 2, box_size.y / 2, box_size.z / 2);
    glVertex3f(-box_size.x / 2, box_size.y / 2, -box_size.z / 2);
    glEnd();

    glPopMatrix();
}

