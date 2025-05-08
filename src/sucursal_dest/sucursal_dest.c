#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "../sucursal/sucursal.h"

#include "sucursal_dest.h"          

THIS(obj_SucursalDest)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
char* toString_SucursalDestImpl(void *self)
{
	
     obj_SucursalDest *obj=this(self);
	 obj_Sucursal *sucO = obj->getSucursalObjO(obj);
	 obj_Sucursal *sucD = obj->getSucursalObjD(obj);
	       
     int size = snprintf(NULL, 0, "Sucursal origen: %d %s - Sucursal Destino:%d %s - Kilometros:%d\n",
	 								sucO->getCodigo(sucO),sucO->getNombre(obj),sucD->getCodigo(obj),sucD->getNombre(obj)); 
     
	 char *resultado = malloc(size +1);
     if (resultado == NULL) return NULL;
     sprintf(resultado, "Sucursal origen: %d %s - Sucursal Destino:%d %s - Kilometros:%d\n",
	 								sucO->getCodigo(sucO),sucO->getNombre(obj),sucD->getCodigo(obj),sucD->getNombre(obj));
     
     return resultado;
     
     
}

static int getCodSucOSucursalDest_Impl(void *self)
{ return  *((int *) getValue(self,POS_COD_SUC_O_SUC));}
//----------------------------------------------------

static int getCodSucDSucursalDest_Impl(void *self)
{ return  *((int *) getValue(self,POS_COD_SUC_D_SUC));}
//----------------------------------------------------


static void setCodSucOSucursalDest_Impl(void *self,int val)
{ setValue(self,POS_COD_SUC_O_SUC,&val); }
//----------------------------------------------------

static void setCodSucDSucursalDest_Impl(void *self,int val)
{ setValue(self,POS_COD_SUC_D_SUC,&val); }
//----------------------------------------------------

static void setKmSucursalDest_Impl(void *self,int val)
{ setValue(self,POS_KM_SUC,&val); }
//----------------------------------------------------

//----------------------------------------------------
static void destroyInternalSUC_Impl(void *self)
{
	obj_SucursalDest *obj = this(self);	
	// finalizar cada referencia inicializada - no NULL
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
obj_Sucursal *getSucursalDest_SucursalObjO_Impl(void *self)
{
 obj_SucursalDest *obj = this(self);        //acceso a la informacion relacionada   
 obj->sucursal_o = Sucursal_new();
 
 if(obj->sucursal_o->findbykey(obj->sucursal_o,obj->getCodSucO(obj))==NOT_FOUND)
   return NULL;
 return obj->sucursal_o;

}

obj_Sucursal *getSucursalDest_SucursalObjD_Impl(void *self)
{
 obj_SucursalDest *obj = this(self);        //acceso a la informacion relacionada   
 obj->sucursal_d = Sucursal_new();
 
 if(obj->sucursal_d->findbykey(obj->sucursal_d,obj->getCodSucD(obj))==NOT_FOUND)
   return NULL;
 return obj->sucursal_d;
}

//----------------------------------------------------
int getKmSucursalDest_Impl(void *self)
 { return  *((int *) getValue(self,POS_KM_SUC));}

//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_SucursalDest(void *self)
{
  obj_SucursalDest *obj      = this(self);
  obj->ds  			    = &table_SucursalDest;
  obj->constructor 	    = SucursalDest_new;
  obj->sizeObj 		    = sizeof(obj_SucursalDest*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
  obj->sucursal_o   = NULL;
  obj->sucursal_d   = NULL;

  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_SucursalDestImpl;
  // Inicializar handlers de getters y setters
  /// getters
    
	obj->getCodSucO = getCodSucOSucursalDest_Impl;
  
	obj->getCodSucD = getCodSucDSucursalDest_Impl;

  /// setters  
    
	obj->setCodSucO = setCodSucOSucursalDest_Impl;
  
	obj->setCodSucD = setCodSucDSucursalDest_Impl;

  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalSUC_Impl;
  //---- acceso a relaciones  
  obj->getSucursalObjO  = getSucursalDest_SucursalObjO_Impl;
  obj->getSucursalObjD  = getSucursalDest_SucursalObjD_Impl;
  obj->getKm            = getKmSucursalDest_Impl;
  obj->setKm            = setKmSucursalDest_Impl;

  return obj;
}
//----------------------------------------------------
//constructor de SucursalDest
obj_SucursalDest *SucursalDest_new()
{
  return (obj_SucursalDest *)init_obj(sizeof(obj_SucursalDest), init_SucursalDest);
}
//----------------------------------------------------

