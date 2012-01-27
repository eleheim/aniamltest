#ifndef __DOG_OBJECT_H__
#define __DOG_OBJECT_H__

#include <glib-object.h>

#include "animalobject.h"

#define DOG_TYPE_OBJECT                (dog_object_get_type ())
#define DOG_OBJECT(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), DOG_TYPE_OBJECT, DogObject))
#define DOG_OBJECT_CLASS(klass)        (G_TYPE_CHECK_CLASS_CAST ((klass), DOG_TYPE_OBJECT, DogObjectClass))
#define DOG_IS_OBJECT(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DOG_TYPE_OBJECT))
#define DOG_IS_OBJECT_CLASS(klass)     (G_TYPE_CHECK_CLASS_TYPE ((klass), DOG_TYPE_OBJECT))
#define DOG_OBJECT_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS ((obj), DOG_TYPE_OBJECT, DogObjectClass))

typedef struct _DogObject DogObject;
typedef struct _DogObjectPrivate DogObjectPrivate;
typedef struct _DogObjectClass DogObjectClass;


struct _DogObject
{
  AnimalObject parent_instance;

  DogObjectPrivate *priv;
};

struct _DogObjectClass
{
  AnimalObjectClass  parent_class;
};

GType           dog_object_get_type                     (void);


void            dog_object_module_register_type         (GTypeModule    *type_module);

#endif
