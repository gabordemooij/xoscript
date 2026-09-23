#include <stdio.h>
#include <xocl.h>
#include <gui/gtk/gtk.h>
#include <gtk/gtk.h>
GtkBuilder* builder;
GtkWidget *window;
GtkApplication *app;

static void on_submit(GtkButton *button,  gpointer user_data) {
	char* xmlui;
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
			if (GTK_IS_TEXT_VIEW(obj)) {
				json_key(gtk_buildable_get_buildable_id(GTK_BUILDABLE(obj)));
				GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(obj));
				GtkTextIter start, end;
				gtk_text_buffer_get_bounds(buffer, &start, &end);
				char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
				json_string(text);
				g_free(text);
			}
			if (GTK_IS_CHECK_BUTTON(obj)) {
				char* key = gtk_buildable_get_buildable_id(GTK_BUILDABLE(obj));
				gboolean checked = gtk_check_button_get_active(GTK_CHECK_BUTTON(obj));
				if (strncmp("_RG", key, 3)==0) {
					if (checked) {
						char* keycopy  = strdup(key);
						char* tok = strtok(keycopy, "_");
						json_key(tok+2);
						tok=strtok(NULL,"_");
						json_string(tok);
					}
					continue;
				}
				json_key(key);
				if (checked) {
					json_string("on");
				} else {
					json_string("off");
				}
			}
		}
	}
	
	json_close();
	g_object_unref(builder);
	builder = gtk_builder_new();
	int r = readxml(&xmlui, "</interface>");
	if (r != 0) {
		g_printerr("Unable to read xml file: %d \n", r);
		exit(0);
		return;
	}
	GError *error = NULL;
	gtk_builder_add_from_string(builder,xmlui,-1,&error);
	if (error){
		g_printerr("XML Error: %s\n", error->message);
		g_error_free(error);
		return;
	}
	GtkWidget* nwindow = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	GtkWidget* new_content = gtk_widget_get_first_child(nwindow);
	g_object_ref(new_content);
	gtk_window_set_child(GTK_WINDOW(nwindow), NULL);
	g_object_unref(new_content);
	gtk_window_set_child(GTK_WINDOW(window), new_content);
	GSList* nobjects = gtk_builder_get_objects(builder);
	for (GSList *l = nobjects; l != NULL; l = l->next) {
		GObject *obj = G_OBJECT(l->data);
		if (GTK_IS_BUTTON(obj)) {
			g_signal_connect(obj, "clicked", G_CALLBACK(on_submit), app);
		}
	}
}

static void activate(GtkApplication *gtk_app, gpointer user_data) {
	char* xmlui;
	builder = gtk_builder_new();
	if (readxml(&xmlui, "</interface>") != 0) {
		g_printerr("Unable to read xml file.\n");
		exit(0);
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
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
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
	app = gtk_application_new(getenv("XOCL_APPLICATION_ID"), G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), 0, NULL);
	
	return status;
}
