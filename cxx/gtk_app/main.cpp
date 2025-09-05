#include <gtk/gtk.h>

static void on_button_clicked(GtkWidget *widget, gpointer data)
{
    g_print("Hello, GTK4!\n");
}

static void on_activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK4 Demo");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    GtkWidget *button = gtk_button_new_with_label("Click Me!");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_window_set_child(GTK_WINDOW(window), button);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new("com.example.gtk4demo", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}