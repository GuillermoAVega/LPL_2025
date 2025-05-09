#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "../sucursal/sucursal.h"
#include "../cliente/cliente.h"
#include "../banco/banco.h"
#include "../medio_pago/medio_pago.h"
#include "../factura/factura.h"
#include "../bulto/bulto.h"

#include "track_viaje.h"

THIS(obj_TrackViaje)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
char* toString_TrackViajeImpl(void *self)
{
     obj_TrackViaje *obj=this(self);      
    
     obj_Sucursal *sucO = obj->getSucursalObjO(obj);
     obj_Sucursal *sucD = obj->getSucursalObjD(obj);
     int size = snprintf(NULL, 0, "cod track:%d - cod bulto: %d Sucursal origen: %d - %s - Sucursal Destino: %d - %s Fecha ingreso: %s - Fecha salida: %s\n",
	 							 obj->getCodigo(obj),obj->getCodBulto(obj),sucO->getCodigo(sucO),sucO->getNombre(sucO), sucD->getCodigo(sucD),sucD->getNombre(sucD),
								  obj->getFIngreso(obj), obj->getFSalida(obj)); 
     
	 char *resultado = malloc(size +1);
     if (resultado == NULL) return NULL;
     sprintf(resultado, "cod track:%d - cod bulto: %d Sucursal origen: %d - %s - Sucursal Destino: %d - %s Fecha ingreso: %s - Fecha salida: %s\n",
	 							 obj->getCodigo(obj),obj->getCodBulto(obj),sucO->getCodigo(sucO),sucO->getNombre(sucO), sucD->getCodigo(sucD),sucD->getNombre(sucD),
								  obj->getFIngreso(obj), obj->getFSalida(obj)); 
     
     destroyObj(sucO);
     destroyObj(sucD);
     return resultado;  
}

static int getCodigoTrackViaje_Impl(void *self)
{ return  *((int *) getValue(self,POS_CODIGO_TRA));}
//----------------------------------------------------

static int getCodSucOTrackViaje_Impl(void *self)
{ return  *((int *) getValue(self,POS_COD_SUC_O_TRA));}
//----------------------------------------------------

static int getCodSucDTrackViaje_Impl(void *self)
{ return  *((int *) getValue(self,POS_COD_SUC_D_TRA));}
//----------------------------------------------------

static int getCodBultoTrackViaje_Impl(void *self)
{ return  *((int *) getValue(self,POS_COD_BULTO_TRA));}
//----------------------------------------------------

static char * getFIngresoTrackViaje_Impl(void *self)
{ return  (char *) getValue(self,POS_F_INGRESO_TRA);}
//----------------------------------------------------

static char * getHIngresoTrackViaje_Impl(void *self)
{ return  (char *) getValue(self,POS_H_INGRESO_TRA);}
//----------------------------------------------------

static char * getFSalidaTrackViaje_Impl(void *self)
{ return  (char *) getValue(self,POS_F_SALIDA_TRA);}
//----------------------------------------------------

static char * getHSalidaTrackViaje_Impl(void *self)
{ return  (char *) getValue(self,POS_H_SALIDA_TRA);}
//----------------------------------------------------

static char * getDetalleTrackViaje_Impl(void *self)
{ return  (char *) getValue(self,POS_DETALLE_TRA);}
//----------------------------------------------------


static void setCodigoTrackViaje_Impl(void *self,int val)
{ setValue(self,POS_CODIGO_TRA,&val); }
//----------------------------------------------------

static void setCodSucOTrackViaje_Impl(void *self,int val)
{ setValue(self,POS_COD_SUC_O_TRA,&val); }
//----------------------------------------------------

static void setCodSucDTrackViaje_Impl(void *self,int val)
{ setValue(self,POS_COD_SUC_D_TRA,&val); }
//----------------------------------------------------

static void setCodBultoTrackViaje_Impl(void *self,int val)
{ setValue(self,POS_COD_BULTO_TRA,&val); }
//----------------------------------------------------

static void setFIngresoTrackViaje_Impl(void *self,char * val)
{ setValue(self,POS_F_INGRESO_TRA,val); }
//----------------------------------------------------

static void setHIngresoTrackViaje_Impl(void *self,char * val)
{ setValue(self,POS_H_INGRESO_TRA,val); }
//----------------------------------------------------

static void setFSalidaTrackViaje_Impl(void *self,char * val)
{ setValue(self,POS_F_SALIDA_TRA,val); }
//----------------------------------------------------

static void setHSalidaTrackViaje_Impl(void *self,char * val)
{ setValue(self,POS_H_SALIDA_TRA,val); }
//----------------------------------------------------

static void setDetalleTrackViaje_Impl(void *self,char * val)
{ setValue(self,POS_DETALLE_TRA,val); }
//----------------------------------------------------

//----------------------------------------------------
static void destroyInternalTRA_Impl(void *self)
{
	obj_TrackViaje *obj = this(self);	
	// finalizar cada referencia inicializada - no NULL
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
obj_Sucursal *getTrackViaje_SucursalObjO_Impl(void *self)
{
 obj_TrackViaje *obj = this(self);        //acceso a la informacion relacionada   
 obj->sucursal_o = Sucursal_new();
 
 if(obj->sucursal_o->findbykey(obj->sucursal_o,obj->getCodSucO(obj))==NOT_FOUND)
   return NULL;
 return obj->sucursal_o;
}

obj_Sucursal *getTrackViaje_SucursalObjD_Impl(void *self)
{
 obj_TrackViaje *obj = this(self);        //acceso a la informacion relacionada   
 obj->sucursal_d = Sucursal_new();
 
 if(obj->sucursal_d->findbykey(obj->sucursal_d,obj->getCodSucD(obj))==NOT_FOUND)
   return NULL;
 return obj->sucursal_d;
}

obj_Bulto *getTrackViaje_BultoObj_Impl(void *self)
{
 obj_TrackViaje *obj = this(self);        //acceso a la informacion relacionada   
 obj->bulto = Bulto_new();
 
 if(obj->bulto->findbykey(obj->bulto,obj->getCodBulto(obj))==NOT_FOUND)
   return NULL;
 return obj->bulto;
}

//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_TrackViaje(void *self)
{
  obj_TrackViaje *obj      = this(self);
  obj->ds  			    = &table_TrackViaje;
  obj->constructor 	    = TrackViaje_new;
  obj->sizeObj 		    = sizeof(obj_TrackViaje*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
  obj->sucursal_o   = NULL;
  obj->sucursal_d   = NULL;
  obj->bulto   = NULL;

  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_TrackViajeImpl;
  // Inicializar handlers de getters y setters
  /// getters
    
	obj->getCodigo = getCodigoTrackViaje_Impl;
  
	obj->getCodSucO = getCodSucOTrackViaje_Impl;
  
	obj->getCodSucD = getCodSucDTrackViaje_Impl;
  
	obj->getCodBulto = getCodBultoTrackViaje_Impl;
  
	obj->getFIngreso = getFIngresoTrackViaje_Impl;
  
	obj->getHIngreso = getHIngresoTrackViaje_Impl;
  
	obj->getFSalida = getFSalidaTrackViaje_Impl;
  
	obj->getHSalida = getHSalidaTrackViaje_Impl;
  
	obj->getDetalle = getDetalleTrackViaje_Impl;

  /// setters  
    
	obj->setCodigo = setCodigoTrackViaje_Impl;
  
	obj->setCodSucO = setCodSucOTrackViaje_Impl;
  
	obj->setCodSucD = setCodSucDTrackViaje_Impl;
  
	obj->setCodBulto = setCodBultoTrackViaje_Impl;
  
	obj->setFIngreso = setFIngresoTrackViaje_Impl;
  
	obj->setHIngreso = setHIngresoTrackViaje_Impl;
  
	obj->setFSalida = setFSalidaTrackViaje_Impl;
  
	obj->setHSalida = setHSalidaTrackViaje_Impl;
  
	obj->setDetalle = setDetalleTrackViaje_Impl;

  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalTRA_Impl;
  //---- acceso a relaciones  
    obj->getSucursalObjO  = getTrackViaje_SucursalObjO_Impl;
  obj->getSucursalObjD  = getTrackViaje_SucursalObjD_Impl;
  obj->getBultoObj  = getTrackViaje_BultoObj_Impl;

  return obj;
}
//----------------------------------------------------
//constructor de TrackViaje
obj_TrackViaje *TrackViaje_new()
{
  return (obj_TrackViaje *)init_obj(sizeof(obj_TrackViaje), init_TrackViaje);
}
//----------------------------------------------------

