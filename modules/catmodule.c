/*  gcc -fPIC -shared -o cat.so -I./../ catmodule.c catobject.c `pkg-config --cflags --libs glib-2.0 gio-2.0 gmodule-2.0` */
#include <gmodule.h>
#include <glib-object.h>

#include "animalobject.h"
#include "catobject.h"


static const gchar *id = "CAT";

G_MODULE_EXPORT const gchar* 
animal_object_module_get_id (void)
{
  return id;
}


G_MODULE_EXPORT void 
animal_object_module_init (GTypeModule *type_module)
{
  cat_object_module_register_type (type_module);
}


G_MODULE_EXPORT void
animal_object_module_exit (void)
{
}

G_MODULE_EXPORT AnimalObject*
animal_object_module_create (void)
{
  return ANIMAL_OBJECT(g_object_new(CAT_TYPE_OBJECT, NULL));
}
