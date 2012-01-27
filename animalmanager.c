#include "animalmanager.h"
#include "animalmodule.h"
#include "animalobject.h"


#define DEFAULT_PATH "modules"

struct _AnimalManagerPrivate
{
  GHashTable *table;
  gchar *path;
};


static void     animal_manager_real_sound_request       (AnimalObject   *animal,
                                                         const char     *id); 

static void     animal_manager_real_play                (AnimalObject   *animal,
                                                         const gchar    *str); 

static void     animal_manager_object_play_callback     (AnimalObject   *animal,
                                                         const gchar    *str,
                                                         AnimalManager  *animal_manager);

static void     animal_manager_signal_handlers_disconnect       (gpointer       key,
                                                                 gpointer       value,
                                                                 gpointer       user_data);

static void     animal_manager_finalize                 (GObject        *object);


G_DEFINE_TYPE (AnimalManager, animal_manager, ANIMAL_TYPE_OBJECT)


static void
animal_manager_class_init (AnimalManagerClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS(klass);
  AnimalObjectClass *animal_class = ANIMAL_OBJECT_CLASS(klass);

  animal_class->sound_request = animal_manager_real_sound_request;
  animal_class->play = animal_manager_real_play;

  object_class->finalize = animal_manager_finalize;

  g_type_class_add_private(object_class, sizeof(AnimalManagerPrivate));
}

static void
animal_manager_init (AnimalManager *animal_manager)
{
  AnimalManagerPrivate *priv;

  animal_manager->priv = G_TYPE_INSTANCE_GET_PRIVATE (animal_manager, ANIMAL_TYPE_MANAGER, AnimalManagerPrivate);

  priv = animal_manager->priv;

  priv->table = NULL;
  priv->path = NULL;
}

static void
animal_manager_finalize (GObject *object)
{
  AnimalManager *animal_manager = ANIMAL_MANAGER(object);
  AnimalManagerPrivate *priv;

  priv = animal_manager->priv;

  if (priv->table)
    {
      g_hash_table_foreach (priv->table, 
                            animal_manager_signal_handlers_disconnect,
                            animal_manager);
      g_hash_table_destroy (priv->table);
    }
  
  G_OBJECT_CLASS(animal_manager_parent_class)->finalize (object);
}

static void
animal_manager_real_sound_request (AnimalObject  *animal,
                                   const gchar *id)
{
  AnimalManager *animal_manager;
  AnimalManagerPrivate *priv;
  AnimalObject *obj;

  g_return_if_fail (ANIMAL_IS_MANAGER(animal));

  animal_manager = ANIMAL_MANAGER(animal);

  priv = animal_manager->priv;

  if (id == NULL)
    {
      g_warning("id is NULL");
      return;
    }
  
  if (priv->table == NULL)
    {
      g_warning("module list does not loaded\n");
      return;
    }

  obj = g_hash_table_lookup (priv->table, id); 

  if (obj == NULL)
    {
      g_warning ("no matched AnimalObject id: %s\n", id);
      return;
    }

  animal_object_sound_request(obj, id);

}

static void
animal_manager_real_play (AnimalObject *animal,
                          const gchar *str)
{
}

static void
animal_manager_object_play_callback (AnimalObject *animal,
                                     const gchar *str,
                                     AnimalManager *animal_manager)
{
  g_return_if_fail (ANIMAL_IS_MANAGER(animal_manager));

  g_signal_emit_by_name (animal_manager, "play", str);
}

static void
animal_manager_signal_handlers_disconnect (gpointer key,
                                           gpointer value,
                                           gpointer user_data)
{
  g_return_if_fail ((ANIMAL_IS_OBJECT(value) && ANIMAL_IS_MANAGER(user_data)));

  g_signal_handlers_disconnect_by_func (value, animal_manager_object_play_callback, user_data);
}

/* public APIs */
void
animal_manager_set_path (AnimalManager *animal_manager,
                         const gchar *str)
{
  AnimalManagerPrivate *priv;

  g_return_if_fail (ANIMAL_IS_MANAGER(animal_manager));

  priv = animal_manager->priv;

  if (priv->path)
    {
      g_free(priv->path);
      priv->path = NULL;
    }

  if (str)
    priv->path = g_strdup(str);
  else
    priv->path = g_strdup(DEFAULT_PATH);
}

void 
animal_manager_load (AnimalManager *animal_manager)
{
  AnimalManagerPrivate *priv;

  GDir *dir = NULL;
  GError *error = NULL;

  const gchar *str = NULL;

  g_return_if_fail (ANIMAL_IS_MANAGER(animal_manager));

  priv = animal_manager->priv;

  if (priv->table)
    {
      g_hash_table_foreach (priv->table, 
                            animal_manager_signal_handlers_disconnect,
                            animal_manager);
      g_hash_table_destroy (priv->table);
    }

  priv->table = g_hash_table_new_full (g_str_hash, g_str_equal,
                                       (GDestroyNotify) g_free,
                                       (GDestroyNotify) g_object_unref);

  dir = g_dir_open (priv->path, 0, &error);

  if (dir == NULL)
    {
      g_warning ("%s : %s\n", error->message, priv->path);
      return;
    }

  while ((str = g_dir_read_name(dir)))
    {
      if (g_str_has_suffix(str, "."G_MODULE_SUFFIX))
        {
          AnimalModule *animal_module =NULL;
          AnimalObject *animal = NULL;

          gchar *full_path = NULL;
          gchar *id = NULL;

          full_path = g_build_filename (priv->path, str, NULL);

          if (g_file_test(full_path, G_FILE_TEST_IS_REGULAR) == FALSE)
            continue;

          animal_module = animal_module_new (full_path);

          g_type_module_use (G_TYPE_MODULE(animal_module));

          id = (gchar *)animal_module->get_id();

          if (g_hash_table_lookup (priv->table, id))
            {
              g_warning("%s: already registered id %s\n", full_path, id);
              continue;
            }

          animal  = animal_module->create();

          g_signal_connect(animal, "play", 
                           G_CALLBACK(animal_manager_object_play_callback), 
                           animal_manager);


          g_hash_table_insert (priv->table, id, animal);

          g_type_module_unuse(G_TYPE_MODULE(animal_module));
        }
    }

  g_dir_close(dir);
}

GList*
animal_manager_get_ids (AnimalManager *animal_manager)
{
  AnimalManagerPrivate *priv;

  g_return_val_if_fail (ANIMAL_IS_MANAGER(animal_manager), NULL);

  priv=animal_manager->priv;

  if (priv->table)
    return g_hash_table_get_keys(priv->table);
  else
    return NULL;
}
