#include "../../includes/includelib.h"
#include "log_audit.h"

THIS(obj_Auditoria) 

char *toString_AuditoriaImpl(void *self)
{
    obj_Auditoria *obj = this(self);

	int size = MAX_SQL;
     
	char *resultado = malloc(size + 1);
	if (resultado == NULL) 
		return NULL;
		
	snprintf(resultado, size ,"Fecha: %s - Objeto: %s - Detalle: %s \n", obj->getFecha(obj), obj->getObjeto(obj), obj->getDetalle(obj));
	
	return resultado;   
}


//Getters
static int getCodigoAuditoria_Impl(void *self){
	return *((int *) getValue(self,POS_CODIGO_AUD));
}


static char *getDetalleAuditoria_Impl(void *self){

    return ((char *) getValue(self, POS_DETALLE_AUD));
}


static char *getObjetoAuditoria_Impl(void *self){

    return ((char *) getValue(self, POS_OBJETO_AUD));
}

static char * getFechaAuditoria_Impl(void *self){
 return  (char *) getValue(self,POS_FECHA_HORA_AUD);
}


//Setters

static void setCodigoAuditoria_Impl(void *self, int val){

	setValue(self,POS_CODIGO_AUD,&val);

}

static void setDetalleAuditoria_Impl(void *self, char *val){
	setValue(self,POS_DETALLE_AUD,val);
}

static void setObjetoAuditoria_Impl(void *self, char *val){

	setValue(self,POS_OBJETO_AUD, val);

}

static void setFechaAuditoria_Impl(void *self, char *val){

	setValue(self,POS_FECHA_HORA_AUD, val);

}



//Destroy Internal
static void destroyInternalBAN_Impl(void *self)
{
	obj_Auditoria *obj = this(self);
}


static void *init_Auditoria(void *self)
{
    obj_Auditoria *obj = this(self);
    obj->ds  			    = &table_Auditoria;
    obj->constructor 	    = Auditoria_new;
    obj->sizeObj 		    = sizeof(obj_Auditoria*);
    obj->toString    		= toString_AuditoriaImpl;

    //Getters
    obj->getCodigo = getCodigoAuditoria_Impl;
    obj->getDetalle = getDetalleAuditoria_Impl;
    obj->getObjeto = getObjetoAuditoria_Impl;
	obj->getFecha = getFechaAuditoria_Impl;

    //Setters
    obj->setCodigo = setCodigoAuditoria_Impl;
    obj->setDetalle = setDetalleAuditoria_Impl;
    obj->setObjeto = setObjetoAuditoria_Impl;
    obj->setFecha = setFechaAuditoria_Impl;
    
    obj->destroyInternal 	= destroyInternalBAN_Impl;

    return obj;
}

obj_Auditoria *Auditoria_new(){
    return (obj_Auditoria *)init_obj(sizeof(obj_Auditoria), init_Auditoria);
}


