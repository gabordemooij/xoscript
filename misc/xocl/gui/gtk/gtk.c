#include <stdio.h>
#include <xocl.h>
#include <gui/gtk/gtk.h>
#include <gtk/gtk.h>
GtkBuilder* builder;

static void on_submit(GtkButton *button,  gpointer user_data) {
	GSList *objects = gtk_builder_get_objects(builder);
	json_start();
	json_key("submit");
	json_string(gtk_widget_get_name(GTK_WIDGET(button)));
	for (GSList *l = objects; l; l = l->next) {
		GObject *obj = l->data;
		if (GTK_IS_WIDGET(obj)) {
			if (GTK_IS_ENTRY(obj)) {
				json_key(gtk_buildable_get_buildable_id(GTK_BUILDABLE(obj)));
				json_string(gtk_editable_get_text(GTK_EDITABLE(obj)));
			}
			if (GTK_IS_CHECK_BUTTON(obj)) {
				json_key(gtk_buildable_get_buildable_id(GTK_BUILDABLE(obj)));
				if (gtk_check_button_get_active(GTK_CHECK_BUTTON(obj))) {
					json_string("on");
				} else {
					json_string("off");
				}
			}
		}
	}
	json_close();
	g_slist_free(objects);
	g_application_quit(G_APPLICATION(user_data));
	g_object_unref(builder);
}

static void activate(GtkApplication *gtk_app, gpointer user_data) {
	char* xmlui;
	builder = gtk_builder_new();
	if (readxml(&xmlui) != 0) {
		g_printerr("Unable to read xml file.\n");
		return;
	}
	GtkCssProvider *provider = gtk_css_provider_new();
	gtk_css_provider_load_from_file(
		provider,
		g_file_new_for_path("style.css")
	);
	gtk_style_context_add_provider_for_display(
		gdk_display_get_default(),
		GTK_STYLE_PROVIDER(provider),
		GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
	);
	GError *error = NULL;
	gtk_builder_add_from_string(builder,xmlui,-1,&error);
	if (error){
		g_printerr("XML Error: %s\n", error->message);
		g_error_free(error);
		return;
	}
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "submit"));
	gtk_window_set_application(GTK_WINDOW(window), gtk_app);
	GSList *objects = gtk_builder_get_objects(builder);
	for (GSList *l = objects; l != NULL; l = l->next) {
		GObject *obj = G_OBJECT(l->data);
		if (GTK_IS_BUTTON(obj)) {
			GtkButton *button = GTK_BUTTON(obj);
			g_signal_connect(obj, "clicked", G_CALLBACK(on_submit), gtk_app);
		}
	}
	gtk_window_present(GTK_WINDOW(window));
}

int gui_gtk_start(void) {
	int status = 0;
	GtkApplication *app = gtk_application_new(getenv("XOCL_APPLICATION_ID"), G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), 0, NULL);
	g_object_unref(app);
	return status;
}
