#ifndef __ANIMAL_OBJECT_H__
#define __ANIMAL_OBJECT_H__

#include <glib-object.h>

#define ANIMAL_TYPE_OBJECT                (animal_object_get_type ())
#define ANIMAL_OBJECT(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), ANIMAL_TYPE_OBJECT, AnimalObject))
#define ANIMAL_OBJECT_CLASS(klass)        (G_TYPE_CHECK_CLASS_CAST ((klass), ANIMAL_TYPE_OBJECT, AnimalObjectClass))
#define ANIMAL_IS_OBJECT(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ANIMAL_TYPE_OBJECT))
#define ANIMAL_IS_OBJECT_CLASS(klass)     (G_TYPE_CHECK_CLASS_TYPE ((klass), ANIMAL_TYPE_OBJECT))
#define ANIMAL_OBJECT_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS ((obj), ANIMAL_TYPE_OBJECT, AnimalObjectClass))

typedef struct _AnimalObject AnimalObject;
typedef struct _AnimalObjectClass AnimalObjectClass;


struct _AnimalObject
{
  GObject parent_instance;
};

struct _AnimalObjectClass
{
  GObjectClass parent_class;

  /* virtual table */
  void          (*sound_request)        (AnimalObject   *animal,
                                         const gchar    *id);

  /* signal */
  void          (*play)                 (AnimalObject   *animal,
                                         const gchar     *str);
};

GType           animal_object_get_type          (void);

void            animal_object_sound_request     (AnimalObject   *animal,
                                                 const gchar    *id);


#endif
