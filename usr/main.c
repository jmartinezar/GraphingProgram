#include <gtk/gtk.h>

// Init a variable that count the page in notebook
static int page_counter = 2;

// Create the callback function for close a page
static void close_page(GtkButton *button, gpointer user_data)
{
  GtkWidget *notebook = GTK_WIDGET(user_data);
  GtkWidget *tab_box = gtk_widget_get_parent(GTK_WIDGET(button));
  gint page_num = gtk_notebook_page_num(GTK_NOTEBOOK(notebook), tab_box);
  gtk_notebook_remove_page(GTK_NOTEBOOK(notebook), page_num);
}

// Function that add new page to notebook

static void add_page(GtkButton *button, gpointer user_data)
{
  GtkWidget *notebook = GTK_WIDGET(user_data);

  // Label into page
  char page_content[10];
  snprintf(page_content, sizeof(page_content), "Page %d", page_counter);
  GtkWidget *new_page = gtk_label_new(page_content);

  // Title of the tab
  char page_title[10];
  snprintf(page_title, sizeof(page_title), "%d", page_counter);
  GtkWidget *new_label = gtk_label_new(page_title);

  // Create close button
  GtkWidget *close_button = gtk_button_new_with_label("x");
  gtk_button_set_relief(GTK_BUTTON(close_button), GTK_RELIEF_NONE);
  gtk_widget_set_can_focus(close_button, FALSE);

  // Create a box for hold the tab and close button
  GtkWidget *tab_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(tab_box), new_label, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(tab_box), close_button, FALSE, FALSE, 0);

  // Connecto the click of the button with the callback function
  g_signal_connect(close_button, "clicked", G_CALLBACK(close_page), notebook);
  
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tab_box, new_page);
  gtk_widget_show_all(tab_box);
  gtk_widget_show_all(notebook);

  page_counter++;
}

static void activation(GtkApplication *app, gpointer user_data)
{
  // Create a window
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Divided window");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
  
  // Create a paned
  GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add(GTK_CONTAINER(window), paned);
  
  // Create a notebook
  
  GtkWidget *notebook = gtk_notebook_new();
  
  // Create pages for the notebook
  
  GtkWidget *page1 = gtk_label_new("Page 1");
  
  // Create labels for pages of the notebook
  
  GtkWidget *page1_label = gtk_label_new("1");

  GtkWidget *button1 = gtk_button_new_with_label("x");
  gtk_button_set_relief(GTK_BUTTON(button1), GTK_RELIEF_NONE);
  gtk_widget_set_can_focus(button1, FALSE);
  GtkWidget *bbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(bbox), page1_label, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(bbox), button1, FALSE, FALSE, 0);
  g_signal_connect(button1, "clicked", G_CALLBACK(close_page), notebook);
  
  // Add the pages to notebook
  
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), bbox, page1);

  gtk_widget_show_all(bbox);
  
  // Create the butto to add new page at notebook
  GtkWidget *button = gtk_button_new_with_label("+");
  
  // Related the action to add page to the button
  g_signal_connect(button, "clicked", G_CALLBACK(add_page), notebook);
  
  // Create a vertical box for add the button and notebook
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
  
  // Add the box to paned
  gtk_paned_pack1(GTK_PANED(paned), vbox, TRUE, FALSE);
  
  // Create the labels for second pane
  GtkWidget *right_label = gtk_label_new("Right side");
  
  // Add labels to paned
  gtk_paned_pack2(GTK_PANED(paned), right_label, TRUE, FALSE);

  // Show the paned
  gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
  GtkApplication *app;
  int status;
  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activation), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);

  g_object_unref(app);
  
  return status;
}
