#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "../cliente/cliente.h"
#include "../banco/banco.h"
#include "../medio_pago/medio_pago.h"
#include "../factura/factura.h"
#include "../categoria/categoria.h"
#include "../marca/marca.h"
#include "../producto/producto.h"

#include "det_factura.h"

THIS(obj_DetFactura)// crea definicion de funcion this para este modulo. .. Macro en config.h

char  *toString_DetFacturaImpl(void *self)
{
     obj_DetFactura *obj=this(self);  
	 obj_Producto *prod = Producto_new();    
     int size = snprintf(NULL, 0, "Codigo factura: %d - Producto: %d %s - Precio Unitario: %.2f - Cantidad: %d\n",
	 					 obj->getCodFactura(obj), obj->getCodProducto(obj), prod->getDescripcion(prod),prod->getPrecio(prod),obj->getCantidad(obj));
     
	 char *resultado = malloc(size +1);
     if (resultado == NULL) return NULL;
     sprintf(resultado, "Codigo factura: %d - Producto: %d %s - Precio Unitario: %.2f - Cantidad: %d\n",
	 					 obj->getCodFactura(obj), obj->getCodProducto(obj), prod->getDescripcion(prod),prod->getPrecio(prod),obj->getCantidad(obj));
    
    destroyObj(prod);
	 return resultado;
}

static int getCodFacturaDetFactura_Impl(void *self)
{ return  *((int *) getValue(self,POS_COD_FACTURA_DET));}
//----------------------------------------------------

static int getRenglonDetFactura_Impl(void *self)
{ return  *((int *) getValue(self,POS_RENGLON_DET));}
//----------------------------------------------------

static int getCodProductoDetFactura_Impl(void *self)
{ return  *((int *) getValue(self,POS_COD_PRODUCTO_DET));}
//----------------------------------------------------

static float getPrecioUnitDetFactura_Impl(void *self)
{ return  *((float *) getValue(self,POS_PRECIO_UNIT_DET));}
//----------------------------------------------------

static int getCantidadDetFactura_Impl(void *self)
{ return  *((int *) getValue(self,POS_CANTIDAD_DET));}
//----------------------------------------------------


static void setCodFacturaDetFactura_Impl(void *self,int val)
{ setValue(self,POS_COD_FACTURA_DET,&val); }
//----------------------------------------------------

static void setRenglonDetFactura_Impl(void *self,int val)
{ setValue(self,POS_RENGLON_DET,&val); }
//----------------------------------------------------

static void setCodProductoDetFactura_Impl(void *self,int val)
{ setValue(self,POS_COD_PRODUCTO_DET,&val); }
//----------------------------------------------------

static void setPrecioUnitDetFactura_Impl(void *self,float val)
{ setValue(self,POS_PRECIO_UNIT_DET,&val); }
//----------------------------------------------------

static void setCantidadDetFactura_Impl(void *self,int val)
{ setValue(self,POS_CANTIDAD_DET,&val); }
//----------------------------------------------------

//----------------------------------------------------
static void destroyInternalDET_Impl(void *self)
{
	obj_DetFactura *obj = this(self);	
	
	if(obj->factura != NULL)
		destroyObj(obj->factura);
  
  	if(obj->producto != NULL)
	  	destroyObj(obj->producto); 
	
	obj->producto = NULL;
	obj->factura = NULL;	
	
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
obj_Factura *getDetFactura_FacturaObj_Impl(void *self)
{
 obj_DetFactura *obj = this(self);        //acceso a la informacion relacionada  
 obj->factura = Factura_new();
 
 if(obj->factura->findbykey(obj->factura,obj->getCodFactura(obj))==NOT_FOUND)
   return NULL;
 return obj->factura;
}

obj_Producto *getDetFactura_ProductoObj_Impl(void *self)
{
 obj_DetFactura *obj = this(self);        //acceso a la informacion relacionada  
 obj->producto = Producto_new();
 
 if(obj->producto->findbykey(obj->producto,obj->getCodProducto(obj))==NOT_FOUND)
   return NULL;
 return obj->producto;
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_DetFactura(void *self)
{
  obj_DetFactura *obj      = this(self);
  obj->ds  			    = &table_DetFactura;
  obj->constructor 	    = DetFactura_new;
  obj->sizeObj 		    = sizeof(obj_DetFactura*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
    obj->factura   = NULL;
  obj->producto   = NULL;

  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_DetFacturaImpl;
  // Inicializar handlers de getters y setters
  /// getters
    
	obj->getCodFactura = getCodFacturaDetFactura_Impl;
  
	obj->getRenglon = getRenglonDetFactura_Impl;
  
	obj->getCodProducto = getCodProductoDetFactura_Impl;
  
	obj->getPrecioUnit = getPrecioUnitDetFactura_Impl;
  
	obj->getCantidad = getCantidadDetFactura_Impl;

  /// setters  
    
	obj->setCodFactura = setCodFacturaDetFactura_Impl;
  
	obj->setRenglon = setRenglonDetFactura_Impl;
  
	obj->setCodProducto = setCodProductoDetFactura_Impl;
  
	obj->setPrecioUnit = setPrecioUnitDetFactura_Impl;
  
	obj->setCantidad = setCantidadDetFactura_Impl;

  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalDET_Impl;
  //---- acceso a relaciones  
    obj->getFacturaObj  = getDetFactura_FacturaObj_Impl;
  obj->getProductoObj  = getDetFactura_ProductoObj_Impl;

  return obj;
}
//----------------------------------------------------
//constructor de DetFactura
obj_DetFactura *DetFactura_new()
{
  return (obj_DetFactura *)init_obj(sizeof(obj_DetFactura), init_DetFactura);
}
//----------------------------------------------------

