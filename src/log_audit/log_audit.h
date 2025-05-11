#ifndef AUDITORIA_INCLUDED
    #define AUDITORIA_INCLUDED
    #define CNT_COL_AUDITORIA 4
    #define POS_CODIGO_AUD 0
    #define POS_DETALLE_AUD 1
    #define POS_OBJETO_AUD 2
    #define POS_FECHA_HORA_AUD 3

	#define MAX560 560

    typedef struct {
        IOBJECT

        //Getters
        getPropertyIntPtr getCodigo;

        getPropertyCharPtr getDetalle;

        getPropertyCharPtr getObjeto;

        getPropertyCharPtr   getFecha;


        //Setters
        setPropertyIntPtr setCodigo;

        setPropertyCharPtr setDetalle;

        setPropertyCharPtr setObjeto;

        setPropertyCharPtr setFecha;

    }obj_Auditoria;

    extern obj_Auditoria *Auditoria_new();
    
    static Column cols_Auditoria[CNT_COL_AUDITORIA] = {

        {"codigo", t_int, sizeof(int), true, true},

        {"detalle", t_varchar, (sizeof(char) * MAX560) + 1, false, false},

        {"objeto", t_varchar, (sizeof(char) * MAX40) + 1, false, false},

        {"fecha_hora", t_varchar, (sizeof(char) * MAX25) + 1, false, false},
    };

    static Table table_Auditoria ={"log_audit", CNT_COL_AUDITORIA, 0, cols_Auditoria, NULL};

    typedef obj_Auditoria *(*getAuditoriaObjPtr)(void *self);

#endif
