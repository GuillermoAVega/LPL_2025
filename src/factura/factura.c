#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "../cliente/cliente.h"
#include "../banco/banco.h"
#include "../medio_pago/medio_pago.h"

#include "factura.h"

THIS(obj_Factura)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
char *toString_FacturaImpl(void *self)
{
     obj_Factura *obj=this(self);
	 obj_Cliente *cliente = obj->getClienteObj(obj);
	 obj_MedioPago *medio = obj->getMedioPagoObj(obj);
     int size = snprintf(NULL, 0, "Cod:%d - Nro:%d - Serie:%d - Letra:%s - Cliente:%s - Medio de pago:%s\n", obj->getCodigo(obj), obj->getNro(obj), obj->getSerie(obj),obj->getLetra(obj),
                                                                  cliente->getUsuario(cliente),medio->getDescripcion(medio));

     char *resultado = malloc(size +1);
     if (resultado == NULL) return NULL;

     sprintf(resultado, "Cod:%d - Nro:%d - Serie:%d - Letra:%s - Cliente:%s - Medio de pago:%s\n", obj->getCodigo(obj), obj->getNro(obj), obj->getSerie(obj),obj->getLetra(obj),
                                                                  cliente->getUsuario(cliente),medio->getDescripcion(medio));
	
	destroyObj(medio);
	destroyObj(cliente);
    return resultado;
}

static int getCodigoFactura_Impl(void *self)
{ return  *((int *) getValue(self,POS_CODIGO_FAC));}
//----------------------------------------------------

static int getNroFactura_Impl(void *self)
{ return  *((int *) getValue(self,POS_NRO_FAC));}
//----------------------------------------------------

static int getSerieFactura_Impl(void *self)
{ return  *((int *) getValue(self,POS_SERIE_FAC));}
//----------------------------------------------------

static char * getLetraFactura_Impl(void *self)
{ return  (char *) getValue(self,POS_LETRA_FAC);}
//----------------------------------------------------

static char * getFechaFactura_Impl(void *self)
{ return  (char *) getValue(self,POS_FECHA_FAC);}
//----------------------------------------------------

static int getCodClienteFactura_Impl(void *self)
{ return  *((int *) getValue(self,POS_COD_CLIENTE_FAC));}
//----------------------------------------------------

static int getCodMpagoFactura_Impl(void *self)
{ return  *((int *) getValue(self,POS_COD_MPAGO_FAC));}
//----------------------------------------------------


static void setCodigoFactura_Impl(void *self,int val)
{ setValue(self,POS_CODIGO_FAC,&val); }
//----------------------------------------------------

static void setNroFactura_Impl(void *self,int val)
{ setValue(self,POS_NRO_FAC,&val); }
//----------------------------------------------------

static void setSerieFactura_Impl(void *self,int val)
{ setValue(self,POS_SERIE_FAC,&val); }
//----------------------------------------------------

static void setLetraFactura_Impl(void *self,char * val)
{ setValue(self,POS_LETRA_FAC,val); }
//----------------------------------------------------

static void setFechaFactura_Impl(void *self,char * val)
{ setValue(self,POS_FECHA_FAC,val); }
//----------------------------------------------------

static void setCodClienteFactura_Impl(void *self,int val)
{ setValue(self,POS_COD_CLIENTE_FAC,&val); }
//----------------------------------------------------

static void setCodMpagoFactura_Impl(void *self,int val)
{ setValue(self,POS_COD_MPAGO_FAC,&val); }
//----------------------------------------------------

//----------------------------------------------------
static void destroyInternalFAC_Impl(void *self)
{
	obj_Factura *obj = this(self);	
	// finalizar cada referencia inicializada - no NULL
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
obj_Cliente *getFactura_ClienteObj_Impl(void *self)
{
 obj_Factura *obj = this(self);        //acceso a la informacion relacionada   
 obj->cliente = Cliente_new();
 
 if(obj->cliente->findbykey(obj->cliente,obj->getCodCliente(obj))==NOT_FOUND)
   return NULL;
 return obj->cliente;
}


obj_MedioPago *getFactura_MedioPagoObj_Impl(void *self)
{
 obj_Factura *obj = this(self);        //acceso a la informacion relacionada  
 obj->medio_pago = MedioPago_new();
 
 if(obj->medio_pago->findbykey(obj->medio_pago,obj->getCodMpago(obj))==NOT_FOUND)
   return NULL;
 return obj->medio_pago; 
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Factura(void *self)
{
  obj_Factura *obj      = this(self);
  obj->ds  			    = &table_Factura;
  obj->constructor 	    = Factura_new;
  obj->sizeObj 		    = sizeof(obj_Factura*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
    obj->cliente   = NULL;
  obj->medio_pago   = NULL;

  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_FacturaImpl;
  // Inicializar handlers de getters y setters
  /// getters
    
	obj->getCodigo = getCodigoFactura_Impl;
  
	obj->getNro = getNroFactura_Impl;
  
	obj->getSerie = getSerieFactura_Impl;
  
	obj->getLetra = getLetraFactura_Impl;
  
	obj->getFecha = getFechaFactura_Impl;
  
	obj->getCodCliente = getCodClienteFactura_Impl;
  
	obj->getCodMpago = getCodMpagoFactura_Impl;

  /// setters  
    
	obj->setCodigo = setCodigoFactura_Impl;
  
	obj->setNro = setNroFactura_Impl;
  
	obj->setSerie = setSerieFactura_Impl;
  
	obj->setLetra = setLetraFactura_Impl;
  
	obj->setFecha = setFechaFactura_Impl;
  
	obj->setCodCliente = setCodClienteFactura_Impl;
  
	obj->setCodMpago = setCodMpagoFactura_Impl;

  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalFAC_Impl;
  //---- acceso a relaciones  
    obj->getClienteObj  = getFactura_ClienteObj_Impl;
  obj->getMedioPagoObj  = getFactura_MedioPagoObj_Impl;

  return obj;
}
//----------------------------------------------------
//constructor de Factura
obj_Factura *Factura_new()
{
  return (obj_Factura *)init_obj(sizeof(obj_Factura), init_Factura);
}
//----------------------------------------------------

