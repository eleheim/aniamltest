/* gcc -o animal main.c animalmanager.c animalmodule.c animalobject.c `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0` */

#include <gtk/gtk.h>

#include "animalmanager.h"


static void _set_label (AnimalObject    *object, 
                        const gchar     *str,
                        GtkWidget       *label);

static void _toggled_callback (GtkToggleButton  *togglebutton,
                               AnimalManager    *animal_manager);

static void
_set_label (AnimalObject *object, 
            const gchar *str,
            GtkWidget *label)
{
  g_return_if_fail (GTK_IS_LABEL(label));

  g_printerr("%s %d\n", __FILE__, __LINE__);
  gtk_label_set_label (GTK_LABEL(label), str);
}

static void 
_toggled_callback (GtkToggleButton  *togglebutton,
                   AnimalManager    *animal_manager)
{
  g_return_if_fail (ANIMAL_IS_MANAGER(animal_manager));

  if (gtk_toggle_button_get_active(togglebutton))
    {
      gchar *str = NULL;

      str = g_object_get_data (G_OBJECT(togglebutton), "animal-key");
      g_printerr("%s %d\n", __FILE__, __LINE__);
      animal_object_sound_request (ANIMAL_OBJECT(animal_manager), str);
    }
}

int
main (int argc, char *argv[])
{
  AnimalManager *animal_manager = NULL;

  GtkWidget *window = NULL;
  GtkWidget *vbox = NULL;
  GtkWidget *radio_button = NULL;
  GtkWidget *prev_radio_button = NULL;
  GtkWidget *label = NULL;
  
  
  GList *list = NULL;
  GList *pos = NULL;

  const gchar *path = NULL;

  gtk_init (&argc, &argv);

  path = g_getenv("ANIMAL_MANAGER_PATH");

  animal_manager = g_object_new (ANIMAL_TYPE_MANAGER, NULL);
  
  animal_manager_set_path (animal_manager, path);
  animal_manager_load (animal_manager);

  list = animal_manager_get_ids (animal_manager);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW(window), 300, 200);

  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  label = gtk_label_new(NULL);

  g_signal_connect(G_OBJECT(animal_manager), "play", 
                            G_CALLBACK(_set_label), label);


  for (pos = list ; pos != NULL; pos=pos->next)
    {
      gchar *str;

      str = g_strdup(pos->data);

      if (prev_radio_button == NULL)
        radio_button = gtk_radio_button_new(NULL);
      else
        radio_button = gtk_radio_button_new_from_widget (GTK_RADIO_BUTTON(prev_radio_button));

      gtk_button_set_label (GTK_BUTTON(radio_button),str); 
      gtk_box_pack_start(GTK_BOX(vbox), radio_button, FALSE, FALSE, 0);

      g_object_set_data_full(G_OBJECT(radio_button), "animal-key", str, g_free);

      if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_button)))
        animal_object_sound_request (ANIMAL_OBJECT(animal_manager), str);

      g_signal_connect(G_OBJECT(radio_button), "toggled",
                      G_CALLBACK(_toggled_callback), animal_manager);


      prev_radio_button = radio_button;
    }

  gtk_box_pack_end(GTK_BOX(vbox), label, FALSE, FALSE, 20);

  g_signal_connect(G_OBJECT(window), "destroy", 
                   G_CALLBACK(gtk_main_quit), NULL);


  gtk_widget_show_all (window);

  gtk_main();


  return 0;
}
