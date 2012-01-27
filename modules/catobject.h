#ifndef __CAT_OBJECT_H__
#define __CAT_OBJECT_H__

#include <glib-object.h>

#include "animalobject.h"

#define CAT_TYPE_OBJECT                (cat_object_get_type ())
#define CAT_OBJECT(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), CAT_TYPE_OBJECT, CatObject))
#define CAT_OBJECT_CLASS(klass)        (G_TYPE_CHECK_CLASS_CAST ((klass), CAT_TYPE_OBJECT, CatObjectClass))
#define CAT_IS_OBJECT(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CAT_TYPE_OBJECT))
#define CAT_IS_OBJECT_CLASS(klass)     (G_TYPE_CHECK_CLASS_TYPE ((klass), CAT_TYPE_OBJECT))
#define CAT_OBJECT_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS ((obj), CAT_TYPE_OBJECT, CatObjectClass))

typedef struct _CatObject CatObject;
typedef struct _CatObjectPrivate CatObjectPrivate;
typedef struct _CatObjectClass CatObjectClass;


struct _CatObject
{
  AnimalObject parent_instance;

  CatObjectPrivate *priv;
};

struct _CatObjectClass
{
  AnimalObjectClass  parent_class;
};

GType           cat_object_get_type                     (void);


void            cat_object_module_register_type         (GTypeModule    *type_module);

#endif
