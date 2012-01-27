#include "animalobject.h"


enum
{
  PLAY,
  LAST_SIGNAL
};


static void     animal_object_real_sound_request        (AnimalObject   *animal,
                                                         const gchar    *id);

static void     animal_object_real_play                 (AnimalObject   *animal,
                                                         const gchar    *str);

static void     animal_object_finalize                  (GObject        *object);



static guint signals[LAST_SIGNAL] = { 0 };


G_DEFINE_ABSTRACT_TYPE (AnimalObject, animal_object, G_TYPE_OBJECT)


static void
animal_object_class_init (AnimalObjectClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS(klass);

  klass->sound_request = animal_object_real_sound_request;
  klass->play = animal_object_real_play;

  object_class->finalize = animal_object_finalize;


  signals[PLAY] = g_signal_new("play",
                               G_TYPE_FROM_CLASS(klass),
                               G_SIGNAL_RUN_LAST,
                               G_STRUCT_OFFSET (AnimalObjectClass, play),
                               NULL, NULL,
                               g_cclosure_marshal_VOID__STRING,
                               G_TYPE_NONE, 1,
                               G_TYPE_STRING);
}


static void
animal_object_init (AnimalObject *animal)
{
}

static void
animal_object_finalize  (GObject  *object)
{
  G_OBJECT_CLASS(animal_object_parent_class)->finalize (object);
}

static void
animal_object_real_sound_request (AnimalObject   *animal,
                                  const gchar *id)
{
  g_return_if_reached();
}

static void
animal_object_real_play (AnimalObject  *animal,
                         const gchar *str)
{
  g_return_if_reached();
}

/* public APIs */
void
animal_object_sound_request (AnimalObject *animal,
                             const gchar *id)
{
  g_return_if_fail (ANIMAL_IS_OBJECT(animal));

  ANIMAL_OBJECT_GET_CLASS(animal)->sound_request(animal, id);
}
