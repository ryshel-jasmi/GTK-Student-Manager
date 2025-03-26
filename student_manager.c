#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

typedef struct {
    int id;
    char name[50];
    int age;
    char course[50];
    int year;
    char contact[15];
} Student;

GtkWidget *id_entry, *name_entry, *age_entry, *course_entry, *year_entry, *contact_entry;
GtkWidget *status_label;

void add_student(GtkWidget *widget, gpointer data) {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        gtk_label_set_text(GTK_LABEL(status_label), "Error opening file!");
        return;
    }

    Student stu;
    stu.id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));
    strcpy(stu.name, gtk_entry_get_text(GTK_ENTRY(name_entry)));
    stu.age = atoi(gtk_entry_get_text(GTK_ENTRY(age_entry)));
    strcpy(stu.course, gtk_entry_get_text(GTK_ENTRY(course_entry)));
    stu.year = atoi(gtk_entry_get_text(GTK_ENTRY(year_entry)));
    strcpy(stu.contact, gtk_entry_get_text(GTK_ENTRY(contact_entry)));

    fprintf(file, "%d %s %d %s %d %s\n", stu.id, stu.name, stu.age, stu.course, stu.year, stu.contact);
    fclose(file);
    gtk_label_set_text(GTK_LABEL(status_label), "Student added successfully!");
}

void delete_student(GtkWidget *widget, gpointer data) {
    int id_to_delete = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        gtk_label_set_text(GTK_LABEL(status_label), "Error opening file!");
        return;
    }
    Student stu;
    int found = 0;
    while (fscanf(file, "%d %s %d %s %d %s", &stu.id, stu.name, &stu.age, stu.course, &stu.year, stu.contact) == 6) {
        if (stu.id != id_to_delete) {
            fprintf(temp, "%d %s %d %s %d %s\n", stu.id, stu.name, stu.age, stu.course, stu.year, stu.contact);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    gtk_label_set_text(GTK_LABEL(status_label), found ? "Student deleted!" : "Student not found!");
}

void search_student(GtkWidget *widget, gpointer data) {
    int id_to_search = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        gtk_label_set_text(GTK_LABEL(status_label), "Error opening file!");
        return;
    }
    Student stu;
    int found = 0;
    char buffer[256];
    while (fscanf(file, "%d %s %d %s %d %s", &stu.id, stu.name, &stu.age, stu.course, &stu.year, stu.contact) == 6) {
        if (stu.id == id_to_search) {
            sprintf(buffer, "ID: %d\nName: %s\nAge: %d\nCourse: %s\nYear: %d\nContact: %s", stu.id, stu.name, stu.age, stu.course, stu.year, stu.contact);
            found = 1;
            break;
        }
    }
    fclose(file);
    gtk_label_set_text(GTK_LABEL(status_label), found ? buffer : "Student not found!");
}

void view_students(GtkWidget *widget, gpointer data) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        gtk_label_set_text(GTK_LABEL(status_label), "Error opening file!");
        return;
    }
    char buffer[1024] = "";
    Student stu;
    strcat(buffer, "ID\tName\tAge\tCourse\tYear\tContact\n");
    while (fscanf(file, "%d %s %d %s %d %s", &stu.id, stu.name, &stu.age, stu.course, &stu.year, stu.contact) == 6) {
        char line[256];
        sprintf(line, "%d\t%-10s\t%d\t%-10s\t%d\t%s\n", stu.id, stu.name, stu.age, stu.course, stu.year, stu.contact);
        strcat(buffer, line);
    }
    fclose(file);
    gtk_label_set_text(GTK_LABEL(status_label), *buffer ? buffer : "No students found!");
}

void create_main_window() {
    GtkWidget *window, *vbox, *grid, *button;
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Student Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 5);

    id_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("ID:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), id_entry, 1, 0, 1, 1);
    
    name_entry = gtk_entry_new();
    age_entry = gtk_entry_new();
    course_entry = gtk_entry_new();
    year_entry = gtk_entry_new();
    contact_entry = gtk_entry_new();
    
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Name:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Age:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), age_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Course:"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), course_entry, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Year:"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), year_entry, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Contact:"), 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), contact_entry, 1, 5, 1, 1);
    
    button = gtk_button_new_with_label("Add Student");
    g_signal_connect(button, "clicked", G_CALLBACK(add_student), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    
    button = gtk_button_new_with_label("Delete Student");
    g_signal_connect(button, "clicked", G_CALLBACK(delete_student), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    
    button = gtk_button_new_with_label("Search Student");
    g_signal_connect(button, "clicked", G_CALLBACK(search_student), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    
    button = gtk_button_new_with_label("View Students");
    g_signal_connect(button, "clicked", G_CALLBACK(view_students), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    
    status_label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), status_label, FALSE, FALSE, 5);
    
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    create_main_window();
    gtk_main();
    return 0;
}