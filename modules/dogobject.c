#include "dogobject.h"

struct _DogObjectPrivate
{
  gchar *sound;
};

static void     dog_object_real_sound_request    (AnimalObject  *animal_object,
                                                  const gchar   *id);

static void     dog_object_real_play            (AnimalObject   *animal_object,
                                                 const gchar    *str);

static void     dog_object_finalize             (GObject        *object);


G_DEFINE_DYNAMIC_TYPE (DogObject, dog_object, ANIMAL_TYPE_OBJECT)

static void
dog_object_class_init (DogObjectClass *klass)
{
  AnimalObjectClass *animal_class = ANIMAL_OBJECT_CLASS(klass);
  GObjectClass *object_class = G_OBJECT_CLASS(klass);

  animal_class->sound_request  = dog_object_real_sound_request;
  animal_class->play  = dog_object_real_play;

  object_class->finalize = dog_object_finalize;

  g_type_class_add_private(object_class, sizeof(DogObjectPrivate));

}

static void
dog_object_class_finalize (DogObjectClass *klass)
{
}

static void
dog_object_init (DogObject *dog)
{
  DogObjectPrivate *priv;

  dog->priv = G_TYPE_INSTANCE_GET_PRIVATE(dog, DOG_TYPE_OBJECT, DogObjectPrivate);

  priv = dog->priv;

  priv->sound = g_strdup("Bark bark");
}

static void
dog_object_finalize (GObject  *object)
{
  DogObject *dog = DOG_OBJECT(object);
  DogObjectPrivate *priv = dog->priv;

  if(priv->sound)
    g_free(priv->sound);

  G_OBJECT_CLASS(dog_object_parent_class)->finalize(object);

}

static void
dog_object_real_sound_request (AnimalObject *animal_object,
                               const gchar *id)
{
  DogObject *dog;
  DogObjectPrivate *priv;

  g_return_if_fail (DOG_IS_OBJECT(animal_object));

  dog = DOG_OBJECT(animal_object);

  priv=dog->priv;

  g_signal_emit_by_name (dog, "play", priv->sound);
}

static void
dog_object_real_play (AnimalObject *animal_object,
                      const gchar    *str)
{
}


/* public APIs */
void
dog_object_module_register_type (GTypeModule *type_module)
{
  dog_object_register_type (type_module);
}

