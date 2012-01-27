#ifndef __ANIMAL_MANAGER_H__
#define __ANIMAL_MANAGER_H__

#include <glib-object.h>

#include "animalobject.h"

#define ANIMAL_TYPE_MANAGER                (animal_manager_get_type ())
#define ANIMAL_MANAGER(obj)                (G_TYPE_CHECK_INSTANCE_CAST ((obj), ANIMAL_TYPE_MANAGER, AnimalManager))
#define ANIMAL_MANAGER_CLASS(klass)        (G_TYPE_CHECK_CLASS_CAST ((klass), ANIMAL_TYPE_MANAGER, AnimalManagerClass))
#define ANIMAL_IS_MANAGER(obj)             (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ANIMAL_TYPE_MANAGER))
#define ANIMAL_IS_MANAGER_CLASS(klass)     (G_TYPE_CHECK_CLASS_TYPE ((klass), ANIMAL_TYPE_MANAGER))
#define ANIMAL_MANAGER_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS ((obj), ANIMAL_TYPE_MANAGER, AnimalManagerClass))

typedef struct _AnimalManager AnimalManager;
typedef struct _AnimalManagerPrivate AnimalManagerPrivate;
typedef struct _AnimalManagerClass AnimalManagerClass;


struct _AnimalManager
{
  AnimalObject parent_instance;
  
  AnimalManagerPrivate *priv;
};


struct _AnimalManagerClass
{
  AnimalObjectClass parent_class;
};

GType           animal_manager_get_type         (void);

void            animal_manager_set_path         (AnimalManager  *animal_manager,
                                                 const gchar    *str);

void            animal_manager_load             (AnimalManager  *animal_manager);

GList*          animal_manager_get_ids          (AnimalManager  *animal_manager);
#endif 


