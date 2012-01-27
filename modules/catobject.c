#include "catobject.h"

struct _CatObjectPrivate
{
  gchar *sound;
};

static void     cat_object_real_sound_request    (AnimalObject  *animal_object,
                                                  const gchar   *id);

static void     cat_object_real_play            (AnimalObject   *animal_object,
                                                 const gchar    *str);

static void     cat_object_finalize             (GObject        *object);


G_DEFINE_DYNAMIC_TYPE (CatObject, cat_object, ANIMAL_TYPE_OBJECT)

static void
cat_object_class_init (CatObjectClass *klass)
{
  AnimalObjectClass *animal_class = ANIMAL_OBJECT_CLASS(klass);
  GObjectClass *object_class = G_OBJECT_CLASS(klass);

  animal_class->sound_request  = cat_object_real_sound_request;
  animal_class->play  = cat_object_real_play;

  object_class->finalize = cat_object_finalize;

  g_type_class_add_private(object_class, sizeof(CatObjectPrivate));

}

static void
cat_object_class_finalize (CatObjectClass *klass)
{
}

static void
cat_object_init (CatObject *cat)
{
  CatObjectPrivate *priv;

  cat->priv = G_TYPE_INSTANCE_GET_PRIVATE(cat, CAT_TYPE_OBJECT, CatObjectPrivate);

  priv = cat->priv;

  priv->sound = g_strdup("Mew~");
}

static void
cat_object_finalize (GObject  *object)
{
  CatObject *cat = CAT_OBJECT(object);
  CatObjectPrivate *priv = cat->priv;

  if(priv->sound)
    g_free(priv->sound);

  G_OBJECT_CLASS(cat_object_parent_class)->finalize(object);

}

static void
cat_object_real_sound_request (AnimalObject *animal_object,
                               const gchar *id)
{
  CatObject *cat;
  CatObjectPrivate *priv;

  g_return_if_fail (CAT_IS_OBJECT(animal_object));

  cat = CAT_OBJECT(animal_object);

  priv=cat->priv;

  g_signal_emit_by_name (cat, "play", priv->sound);
}

static void
cat_object_real_play (AnimalObject *animal_object,
                      const gchar    *str)
{
}


/* public APIs */
void
cat_object_module_register_type (GTypeModule *type_module)
{
  cat_object_register_type (type_module);
}

